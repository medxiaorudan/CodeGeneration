<div align="center">
<h1>
CodeGeneration
</h1>

<center>
<img src="https://github.com/medxiaorudan/CodeGeneration/blob/main/images/CPP.gif" width="700" > 
</center>

[🤗 Hugging Face](https://huggingface.co/) |
[🦜️🔗 langchain](https://huggingface.co/bert-base-cased) |
[🦙 CodeLlama](https://github.com/facebookresearch/codellama) |
[🛠️ XLCoST Dataset](https://github.com/reddy-lab-code-research/XLCoST/tree/main) | 
[🔥 PyTorch](https://github.com/pytorch/pytorch) | 
[🐞 Catch2](https://github.com/catchorg/Catch2) 
</div>

## 🎨 Instructions:
C++ code generation using a pre-trained model. Create a basic program in C++ that accepts numeric input from the user and maintains a record of previous user input together with time stamps. The record should be sorted in ascending order based on the provided input. Leverage a pre-trained code model to generate the C++ code based on specific prompts.

## ✨ Setting up the Docker environment and installing the dependencies
Go to folder ```docker/```.
```
docker build -f Dockerfile -t CodeGeneration \
--build-arg username=$(username) .
```
```
docker run -it --shm-size 60G --gpus all \
-v /path/to/dir/:/home/username/CodeGeneration/ \
-v /path/to/storage/:/storage/ CodeGeneration
```
You can install the following dependencies to run tasks in the environment:
```bash
pip install -r requirements.txt
```
### 🚀 Models relevant for code generation (ordered by most recent first). 

| Name                        | Size             | Languages                                       | Organization                | ⭐/❤️  | Released  | Open Source |
|-----------------------------|------------------|-------------------------------------------------|-----------------------------|--------|-----------|-------------|
| [Phind CodeLlama v2](https://huggingface.co/Phind/Phind-CodeLlama-34B-v2)         | 34B              | Many                                            | Phind                       | 502    | 2023-8-27 | Yes         |
| [WizardCoder-Python](https://huggingface.co/WizardLM/WizardCoder-Python-34B-V1.0)           | 7/13/34B         | Python                                          | WizardLM                    | 658    | 2023-8    | Yes         |
| [CodeLlama](https://github.com/facebookresearch/codellama)                    | 7/13/34B         | Many                                            | Meta AI                     | 11092  | 2023-8    | Yes         |
| [WizardCoder](https://huggingface.co/WizardLM/WizardCoder-15B-V1.0)                  | 15B              | 80+                                             | WizardLM                    | 661    | 2023-6    | Yes         |
| [replit-glaive](https://huggingface.co/sahil2801/replit-code-instruct-glaive)                | 3B               | Python                                          | Replit                      | 85     | 2023-7    | Yes         |
| [CodeGeeX](https://github.com/THUDM/CodeGeeX)                     | 13B              | Python, C++, Java, JavaScript, Go                | THUDM                       | 7419   | 2023-5-16 | Yes         |
| [Starcoder](https://github.com/bigcode-project/starcoder)                    | 15B              | 80+                                             | Hugging Face and ServiceNow | 6595   | 2023-5    | Yes         |
| [replit-v1-3b](https://huggingface.co/replit/replit-code-v1-3b)                 | 3B               | 20+                                             | Replit                      | 698    | 2023-5    | Yes         |
| [CodeT5+](https://github.com/salesforce/CodeT5)                      | 220M, 770M, 2B, 6B, 16B | Ruby, JavaScript, Go, Python, Java, PHP      | Salesforce                  | 2436   | 2023-5    | Yes         |
| [IBM Watson Code Assistant](https://www.ibm.com/products/watsonx-code-assistant)    | 350M             | Many                                            | IBM                         |         | 2023-5    | No          |
| [SantaCoder](https://huggingface.co/bigcode/santacoder)                   | 1.1B             | Python, Java, JavaScript                         | Bigcode                     | 305    | 2023-4    | Yes         |
| [InCoder](https://github.com/dpfried/incoder)                      | 1.3B, 6B         | 20                                              | Facebook                    | 280    | 2023-4    | Yes         |
| [GPT4](https://openai.com/gpt-4)                         | 700B (not sure)  | Many                                            | OpenAI                      |         | 2023-3    | No          |

### 🤖 Popular datasets for code generation (ordered by most recent first). 
| Name         | Examples                                                | Languages                                               | ⭐/❤️  | Released   |
|--------------|---------------------------------------------------------|------------------------------------------------------------|-----|------------|
| [HumanEval-X](https://huggingface.co/datasets/THUDM/humaneval-x)  | 820                                                     | Python, C++, Java, JavaScript, and Go                      | 53  | 2023-8-27  |
| [CoderEval](https://github.com/CodeArtsSnap/CoderEval)    | 328                                                     | Python, Java                                               | 13  | 2023-2-1   |
| [DS-1000](https://github.com/xlang-ai/DS-1000)      | 1000                                                    | Python                                                     | 146 | 2022-11-18 |
| [MultiPL-E](https://huggingface.co/datasets/nuprl/MultiPL-E)     | "HumanEval" and "MBPP" Python benchmarks, and their translations into other 18 languages. | 19 (include C++ and C)                                   | 108 | 2022-8-17  |
| [XLCoST](https://github.com/reddy-lab-code-research/XLCoST)       | 11198 C++, 11028 Java, 10622 Python, 10735 C#, 9951 JS, 3553 PHP, 574 C | C++, Java, Python, C#, Javascript, PHP, C                | 48  | 2022-6-16  |
| [MBPP](https://huggingface.co/datasets/mbpp)         | 974                                                     | Python                                                     | 62  | 2021-8-16  |
| [HumanEval](https://github.com/openai/human-eval)    | 164                                                     | Python                                                     | 1624| 2021-7-17  |
| [APPS](https://github.com/hendrycks/apps)         | 10000                                                   | Python                                                     | 316 | 2021-5-20  |
| [CodeXGLUE](https://github.com/microsoft/CodeXGLUE)    | 124K                                                    | Java, C#                                                   | 1315| 2021-2-9   |
| [SPoC](https://github.com/Sumith1896/spoc)         | 18356 Pseudocode to Code                                | C++                                                        | 10  | 2019       |

### 🎉 Run the code

The fine-tune BERT for System A:
```bash
python main_A.py --MODEL_CKPT bert-base-cased
```
The fine-tune BERT for System B:
```bash
python main_B.py --MODEL_CKPT bert-base-cased
```
The fine-tune XLNET for System A:
```bash
python main_A.py --MODEL_CKPT xlnet-base-cased
```
The fine-tune XLNET for System B:
```bash
python main_B.py --MODEL_CKPT xlnet-base-cased
```
I used [Weights & Biases](https://wandb.ai/site/research?utm_source=github&utm_medium=code&utm_campaign=wandb&utm_content=readme) to record the entire fine-tuning training process. The tracking and visualization report can be viewed [here](https://wandb.ai/medxiaorudan/CodeLlama_finetune_CPP_2?workspace=user-medxiaorudan).

The fine-tuned CodeLlama model [CodeLlama_CPP_FineTuned](https://huggingface.co/medxiaorudan/CodeLlama_CPP_FineTuned) can be interacted with in Hugging Face 🤗

### 🔐 Evaluation results

|       generated code       | can compile  | can exit    | have record of time stamps  | input number in ascending order  |
| ------------ | ------------------ | ------------------ | ------------------ |------------------ |
| CodeLlama-7b-Instruct.cpp | -    | -     | -    | -   |
| Langchain_CodeLlama.cpp     |  -    | -     | -    | -   |
| CodeLlama-13b-Instruct.cpp    | + | -     | -    | -   |
| CodeLlama-34b-Instruct.cpp | + | + | -    | -   |
| CodeLlama-7b-finetuned.cpp | + | + | + | + |
| Langchain_GPT3.5_turbo.cpp | + | + | + | + |
|Langchain_GPT4.cpp | + | + | + | + |
