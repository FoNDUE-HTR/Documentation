#!/bin/env bash
#SBATCH --partition=shared-gpu
#SBATCH --time=01:00:00
#SBATCH --gpus=pascal:1
#SBATCH --output=kraken-%j.out
#SBATCH --mem=0

module load GCCcore/10.2.0 Python/3.8.6
source ~/kraken-env/bin/activate

OUTPUT_NAME="output_name"
XML_FOLDER="/home/users/g/gabays/Documentation/data"

echo "KETOS training"
srun ketos train -o $OUTPUT_NAME -f alto -d cuda "${XML_FOLDER}/*.xml"
