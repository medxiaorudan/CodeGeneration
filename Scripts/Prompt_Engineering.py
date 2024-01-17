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

# Loading CodeLlama model
model = "codellama/CodeLlama-7b-Instruct-hf"
tokenizer = AutoTokenizer.from_pretrained(model)
pipeline = transformers.pipeline(
    "text-generation",
    model=model,
    torch_dtype=torch.float16,
    device_map="auto",
)

# Code Llama sequences generation
system = "Provide answers in C++"
prompt = f"<s>[INST] <<SYS>>\n{system1}\n<</SYS>> \
Generate a C++ program that accepts numeric input from the user and maintains a record of previous user inputs with timestamps.</s>  \
<s>[INST] Ensure the program sorts the user inputs in ascending order based on the provided numeric input. [/INST] </s> \
<s>[INST] Enhance the program to display timestamps along with the sorted user inputs. [/INST] \
"

sequences_7b = pipeline(
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

# Print Code Llama generated sequences
for seq in sequences_7b:
    print(f"Result: {seq['generated_text']}")

# Initializing LangChain and CodeLlama
callback_manager = CallbackManager([StreamingStdOutCallbackHandler()])
llm = LlamaCpp(
    model_path="/srv/users/rudxia/Developer_MICCAI/CodeLlama/model/codellama-13b-instruct.Q3_K_M.gguf",
    n_ctx=100000,
    n_gpu_layers=1,
    n_batch=512,
    f16_kv=False,
    callback_manager=callback_manager,
    verbose=True,
)

# CodeLlama with LangChain
question = "Generate a C++ program that accepts numeric input from the user and maintains a record of previous user inputs with timestamps. Ensure the program sorts the user inputs in ascending order based on the provided numeric input. Enhance the program to display timestamps along with the sorted user inputs."
prompt = PromptTemplate.from_template(question)
default_chain = LLMChain(llm=llm, prompt=prompt, verbose=True)
default_chain.run(prompt=question)

# LangChain with gpt-3.5-turbo
llm_gpt_turbo = ChatOpenAI(temperature=0.3, model_name="gpt-3.5-turbo")
default_chain_gpt_turbo = LLMChain(llm=llm_gpt_turbo, prompt=prompt, verbose=True)
default_chain_gpt_turbo.run(prompt=question)

# SmartChain with gpt-3.5-turbo
chain_gpt_turbo_smart = SmartLLMChain(llm=llm_gpt_turbo, prompt=prompt, n_ideas=3, verbose=True)
chain_gpt_turbo_smart.run({})

# SmartChain with gpt-3.5-turbo and GPT-4
llm_gpt_turbo_ideation = ChatOpenAI(temperature=0.9, model_name="gpt-3.5-turbo")
llm_gpt_4 = ChatOpenAI(temperature=0, model_name="gpt-4")
chain_gpt_turbo_gpt_4_smart = SmartLLMChain(ideation_llm=llm_gpt_turbo_ideation, llm=llm_gpt_4, prompt=prompt, n_ideas=3, verbose=True)
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
chain_gpt_4_smart.run({})
