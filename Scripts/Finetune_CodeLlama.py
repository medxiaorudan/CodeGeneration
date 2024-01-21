# -*- coding: utf-8 -*-
"""
Created on Wed Jan 17 11:47:59 2024

@author: rudan XIAO
"""

# Import necessary libraries
from datetime import datetime
import os
import sys
import torch
from peft import (
    LoraConfig,
    get_peft_model,
    get_peft_model_state_dict,
    prepare_model_for_int8_training,
    set_peft_model_state_dict,
)
from transformers import AutoTokenizer, AutoModelForCausalLM, TrainingArguments, DataCollatorForSeq2Seq
from datasets import load_dataset
from trl import SFTTrainer
from peft import PeftModel

def tokenize(prompt):
    result = tokenizer(
        prompt,
        truncation=True,
        max_length=512,
        padding=False,
        return_tensors=None,
    )
    result["labels"] = result["input_ids"].copy()
    return result

def generate_and_tokenize_prompt(data_point):
    full_prompt =f"""
You are a powerful C++ code generation model. You can use the Task below and write the Response, which is a programming code that can solve the Task.

### Task:
{data_point["text"]}

### Response:
{data_point["code"]}
"""
    return tokenize(full_prompt)


# Load the dataset
data = load_dataset("codeparrot/xlcost-text-to-code", "C++-program-level", split="train")
train_dataset = data.train_test_split(test_size=0.1)["train"]
eval_dataset = data.train_test_split(test_size=0.1)["test"]

# Load the base model and tokenizer
base_model = "codellama/CodeLlama-7b-hf"
model = AutoModelForCausalLM.from_pretrained(
    base_model,
    load_in_8bit=True,
    torch_dtype=torch.float16,
    device_map="auto",
)
tokenizer = AutoTokenizer.from_pretrained("codellama/CodeLlama-7b-hf")

# Tokenization settings
tokenizer.add_eos_token = True
tokenizer.pad_token_id = 0
tokenizer.padding_side = "left"

# Tokenize the dataset
tokenized_train_dataset = train_dataset.map(generate_and_tokenize_prompt)
tokenized_val_dataset = eval_dataset.map(generate_and_tokenize_prompt)

# Setup Lora
model.train()
model = prepare_model_for_int8_training(model)

lora_alpha = 16
lora_dropout = 0.05
lora_r = 16

config = LoraConfig(
    lora_alpha=lora_alpha,
    lora_dropout=lora_dropout,
    r=lora_r,
    target_modules=[
    "q_proj",
    "v_proj",
    ],
    bias="none",
    task_type="CAUSAL_LM"
)

model = get_peft_model(model, config)

# Load from checkpoint if available
resume_from_checkpoint = ""
if resume_from_checkpoint and os.path.exists(resume_from_checkpoint):
    print(f"Restarting from {resume_from_checkpoint}")
    adapters_weights = torch.load(resume_from_checkpoint)
    set_peft_model_state_dict(model, adapters_weights)

# Training parameters
batch_size = 128
per_device_train_batch_size = 16
gradient_accumulation_steps = batch_size // per_device_train_batch_size
output_dir = "CodeLlama_CPP_FineTuned_2"

training_args = TrainingArguments(
    per_device_train_batch_size=per_device_train_batch_size,
    gradient_accumulation_steps=gradient_accumulation_steps,
    warmup_steps=100,
    max_steps=400,
    learning_rate=3e-4,
    fp16=True,
    logging_steps=10,
    optim="adamw_torch",
    evaluation_strategy="steps",
    save_strategy="steps",
    eval_steps=20,
    save_steps=20,
    output_dir=output_dir,
    group_by_length=True,
    report_to="wandb",
    run_name=f"codellama-cpp-{datetime.now().strftime('%Y-%m-%d-%H-%M')}",
)

trainer = SFTTrainer(
    model=model,
    train_dataset=tokenized_train_dataset,
    eval_dataset=tokenized_val_dataset,
    args=training_args,
    data_collator=DataCollatorForSeq2Seq(
        tokenizer, pad_to_multiple_of=8, return_tensors="pt", padding=True
    ),
)

# Model optimizations
model.config.use_cache = False
old_state_dict = model.state_dict
model.state_dict = (lambda self, *_, **__: get_peft_model_state_dict(self, old_state_dict())).__get__(
    model, type(model)
)
if torch.__version__ >= "2" and sys.platform != "win32":
    print("compiling the model")
    model = torch.compile(model)

# Start training
trainer.train()

# Load the final checkpoint
model = AutoModelForCausalLM.from_pretrained(
    base_model,
    load_in_8bit=True,
    torch_dtype=torch.float16,
    device_map="auto",
)

# Load the fine-tuned Lora/Qlora adapter
model = PeftModel.from_pretrained(model, "/srv/users/rudxia/Developer_MICCAI/CodeLlama/CodeLlama_CPP_FineTuned_2/checkpoint-400/")

# Test with the same prompts as before
eval_prompt = """
You are a powerful C++ code generation model. You can use the Task below and write the Response, which is a programming code that can solve the Task.
### Task:
Generate a C++ program that accepts numeric input from the user and maintains a record of previous user inputs with timestamps. Ensure the program sorts the user inputs in ascending order based on the provided numeric input. Enhance the program to display timestamps along with the sorted user inputs.
### Response:
"""

model_input = tokenizer(eval_prompt, return_tensors="pt").to("cuda")

model.eval()
with torch.no_grad():
    print(tokenizer.decode(model.generate(**model_input, max_new_tokens=500, do_sample=True, top_p=0.9, temperature=0.5)[0]))

