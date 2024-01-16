# Use an official Conda runtime as a parent image
FROM nvcr.io/nvidia/pytorch:21.12-py3

# Set the working directory
WORKDIR /CodeGeneration

# Copy the Conda environment specifications to the container
COPY requirements.txt .

# Create a Conda environment based on the specifications
RUN conda create --name my_environment --file requirements.txt

# Activate the Conda environment
RUN echo "source activate my_environment" > ~/.bashrc
ENV PATH /opt/conda/envs/my_environment/bin:$PATH
