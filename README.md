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

1. finetune wandb 实时观测
2. 微调后的模型建hugging face
3. 模型和数据集
4. 
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
### 🚀 Models relevant for code generation. Ordered by most recent first

| Name                        | Size             | Languages                                       | Organization                | ⭐/ ❤️  | Released  | Open Source |
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

### 🤖 Popular dataset for code generation. Ordered by most recent first
| Name         | Examples                                                | Languages                                                  | ⭐   | Released   |
|--------------|---------------------------------------------------------|------------------------------------------------------------|-----|------------|
| HumanEval-X  | 820                                                     | Python, C++, Java, JavaScript, and Go                      | 53  | 2023-8-27  |
| CoderEval    | 328                                                     | Python, Java                                               | 13  | 2023-2-1   |
| DS-1000      | 1000                                                    | Python                                                     | 146 | 2022-11-18 |
| MultiPL-E     | "HumanEval" and "MBPP" Python benchmarks, and their translations into other 18 languages. | 19 (include C++ and C)                                   | 108 | 2022-8-17  |
| XLCoST       | 11198 C++, 11028 Java, 10622 Python, 10735 C#, 9951 JS, 3553 PHP, 574 C | C++, Java, Python, C#, Javascript, PHP, C                | 48  | 2022-6-16  |
| MBPP         | 974                                                     | Python                                                     | 62  | 2021-8-16  |
| HumanEval    | 164                                                     | Python                                                     | 1624| 2021-7-17  |
| APPS         | 10000                                                   | Python                                                     | 316 | 2021-5-20  |
| CodeXGLUE    | 124K                                                    | Java, C#                                                   | 1315| 2021-2-9   |
| SPoC         | 18356 Pseudocode to Code                                | C++                                                        | 10  | 2019       |

### Run the code

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
### Evaluation results

The overall performance of BERT and XLNET on **dev** (The more detailed results about validation and visualization can be found in [Notebooks](https://github.com/medxiaorudan/LLM_NER_MultiNERD/tree/main/Notebooks):

|              | Accuracy (entity)  | Recall (entity)    | Precision (entity)  | F1 score (entity)  |
| ------------ | ------------------ | ------------------ | ------------------ |------------------ |
| BERT+SystemA | 0.9861     | 0.9685     | 0.8699    | 0.9165   |
| BERT+SystemB     | 0.9922 | 0.9740 | 0.9206 | **0.9466**   |
| XLNET+SystemA    | 0.9759 | 0.9548 | 0.7967 | 0.8687   |
| XLNET+SystemB    | 0.9915 | 0.9741 | 0.9145 | 0.9434   |

