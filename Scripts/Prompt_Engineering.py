# -*- coding: utf-8 -*-
"""
Created on Wed Jan 17 12:10:12 2024

@author: rudan XIAO
"""

# Importing necessary libraries
from transformers import AutoTokenizer
import transformers
import torch
from langchain import PromptTemplate
from langchain.llms import LlamaCpp
from langchain.chains import LLMChain
from langchain.callbacks.manager import CallbackManager
from langchain.callbacks.streaming_stdout import StreamingStdOutCallbackHandler
from langchain.chat_models import ChatOpenAI
from langchain_experimental.smart_llm import SmartLLMChain
import os

# Setting environment variable for OpenAI API key
with open("/content/drive/MyDrive/Key.txt", "r") as f:
    os.environ["OPENAI_API_KEY"] = f.read()

def generate_sequences(model_name, prompt):
    tokenizer = AutoTokenizer.from_pretrained(model_name)
    pipeline = transformers.pipeline(
        "text-generation",
        model=model_name,
        torch_dtype=torch.float16,
        device_map="auto",
    )

    sequences = pipeline(
        prompt,
        do_sample=True,
        top_k=10,
        temperature=0.1,
        top_p=0.95,
        num_return_sequences=1,
        eos_token_id=tokenizer.eos_token_id,
        max_length=2000,
        add_special_tokens=False
    )

    return sequences

def print_sequences(model_name, prompt_name, sequences):
    for seq in sequences:
        print(f"{model_name} - {prompt_name} Result: {seq['generated_text']}")


# Example usage with different models and prompts
model_names = ["codellama/CodeLlama-7b-Instruct-hf", "codellama/CodeLlama-13b-Instruct-hf", "codellama/CodeLlama-34b-Instruct-hf"]

# Code Llama sequences generation

prompt1 = f"<s>[INST] <<SYS>>\nProvide answers in C++\n<</SYS>> \
Generate a C++ program that accepts numeric input from the user and maintains a record of previous user inputs with timestamps. </s> \
<s>[INST] Ensure the program sorts the user inputs in ascending order based on the provided numeric input. </s> \
<s>[INST] Enhance the program to display timestamps along with the sorted user inputs. [/INST] \
"

prompt2 = f"<s>[INST] <<SYS>>\nProvide answers in C++\n<</SYS>> \
Generate a C++ program that accepts numeric input from the user and maintains a record of previous user inputs with timestamps.</s>  \
<s>[INST] Ensure the program sorts the user inputs in ascending order based on the provided numeric input. \
Include error handling to handle non-numeric inputs and provide a message to the user when exiting the program. \
Use a suitable data structure (e.g., std::vector or std::list) to efficiently store and manage the user input records. \
Implement a function to display the sorted user input records with timestamps. \
</s> \
<s>[INST] Enhance the program to display timestamps along with the sorted user inputs. \
Use the C++ standard library (e.g., td::chrono::system_clock) for handling timestamps. \
Ensure that the timestamp is updated each time a new user input is added. \
Provide proper formatting for the timestamp in the output. [/INST]"
 
prompt3 = f"<s><<SYS>>\nProvide answers in C++\n<</SYS>> \
Create a basic program in C++ that accepts numeric input from the user and maintains a record of previous user input together with time stamps. \
The record should be sorted in ascending order based on the provided input."

for model_name in model_names:
    sequences_prompt1 = generate_sequences(model_name, prompt1)
    sequences_prompt2 = generate_sequences(model_name, prompt2)
    sequences_prompt3 = generate_sequences(model_name, prompt3)

    print_sequences(model_name, "prompt1", sequences_prompt1)
    print_sequences(model_name, "prompt2", sequences_prompt2)
    print_sequences(model_name, "prompt3", sequences_prompt3)


# CodeLlama with LangChain
question = "Generate a C++ program that accepts numeric input from the user and maintains a record of previous user inputs with timestamps. Ensure the program sorts the user inputs in ascending order based on the provided numeric input. Enhance the program to display timestamps along with the sorted user inputs."
prompt = PromptTemplate.from_template(question)

callback_manager = CallbackManager([StreamingStdOutCallbackHandler()])
llm = LlamaCpp(
    model_path="/srv/users/rudxia/Developer_MICCAI/CodeLlama/model/codellama-13b-instruct.Q3_K_M.gguf",
    n_ctx=100000,
    n_gpu_layers=1,
    n_batch=512,
    f16_kv=False,  # MUST set to True, otherwise you will run into problem after a couple of calls
    callback_manager=callback_manager,
    verbose=True,
)

default_chain = LLMChain(llm=llm, prompt=prompt, verbose=True)
print("CodeLlama with LangChain Result:")
default_chain.run(prompt=question)

# LangChain with gpt-3.5-turbo
llm_gpt_turbo = ChatOpenAI(temperature=0.3, model_name="gpt-3.5-turbo")
default_chain_gpt_turbo = LLMChain(llm=llm_gpt_turbo, prompt=prompt, verbose=True)
print("LangChain with gpt-3.5-turbo Result:")
default_chain_gpt_turbo.run(prompt=question)

# SmartChain with gpt-3.5-turbo
chain_gpt_turbo_smart = SmartLLMChain(llm=llm_gpt_turbo, prompt=prompt, n_ideas=3, verbose=True)
print("SmartChain with gpt-3.5-turbo Result:")
chain_gpt_turbo_smart.run({})

# SmartChain with gpt-3.5-turbo and GPT-4
llm_gpt_turbo_ideation = ChatOpenAI(temperature=0.9, model_name="gpt-3.5-turbo")
llm_gpt_4 = ChatOpenAI(temperature=0, model_name="gpt-4")
chain_gpt_turbo_gpt_4_smart = SmartLLMChain(ideation_llm=llm_gpt_turbo_ideation, llm=llm_gpt_4, prompt=prompt, n_ideas=3, verbose=True)
print("SmartChain with gpt-3.5-turbo and GPT-4 Result:")
chain_gpt_turbo_gpt_4_smart.run({})

# SmartChain with GPT-4
llm_gpt_4_ideation = ChatOpenAI(temperature=0.9, model_name="gpt-4")
llm_gpt_4_critique = ChatOpenAI(temperature=0.5, model_name="gpt-4")
llm_gpt_4_resolver = ChatOpenAI(temperature=0, model_name="gpt-4")
chain_gpt_4_smart = SmartLLMChain(
    ideation_llm=llm_gpt_4_ideation,
    critique_llm=llm_gpt_4_critique,
    resolver_llm=llm_gpt_4_resolver,
    prompt=prompt,
    n_ideas=3,
    verbose=True
)
print("SmartChain with GPT-4 Result:")
chain_gpt_4_smart.run({})

