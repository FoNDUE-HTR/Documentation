#!/bin/env bash
#SBATCH --partition=shared-gpu
#SBATCH --time=01:00:00
#SBATCH --gpus=1
#SBATCH --output=kraken-%j.out
#SBATCH --mem=24GB
#SBATCH --cpus-per-task=4

module load fosscuda/2020b Python/3.8.6
source ~/kraken-env/bin/activate

OUTPUT_NAME="output_name"
XML_FOLDER="/home/users/g/gabays/Documentation/data"

echo "KETOS training"
srun ketos train -o $OUTPUT_NAME -f alto -d cuda:0 "${XML_FOLDER}/*.xml" --workers 4
