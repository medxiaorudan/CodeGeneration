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
[🐞 Catch2](https://github.com/catchorg/Catch2) | 
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

### 🚀 Popular dataset for code generation. Ordered by most recent first


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

