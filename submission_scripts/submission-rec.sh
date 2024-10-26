#!/bin/env bash
#SBATCH --partition=shared-gpu
#SBATCH --time=01:00:00
#SBATCH --gpus=1
#SBATCH --output=kraken-%j.out
#SBATCH --mem=24GB
#SBATCH --cpus-per-task=4
#SBATCH --gres=gpu:1,VramPerGpu:12GB

module load cuDNN/8.9.2.26-CUDA-12.1.1 GCCcore/13.2.0 Python/3.11.5
source ~/kraken-env/bin/activate

echo "I: CUDA_VISIBLE_DEVICES: ${CUDA_VISIBLE_DEVICES}"

echo "====="

srun nvidia-smi

echo "====="

OUTPUT_NAME="output_name"
XML_FOLDER="/home/users/g/gabays/Documentation/data"

echo "=============DATETIME=========="

srun date

echo "KETOS training"
srun ketos train -o $OUTPUT_NAME -f alto -d cuda:0 "${XML_FOLDER}/*.xml" --workers 4

echo "=============DATETIME=========="

srun date