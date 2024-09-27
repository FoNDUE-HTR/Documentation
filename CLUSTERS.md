# Using the clusters

FoNDUE is an HTR infrastructure for the university of Geneva. More information here: https://www.unige.ch/lettres/humanites-numeriques/recherche/projets-de-la-chaire/fondue

## 1. Using the infrastructure:

Our instance uses the [Baobab, Yggdrasil and Bamboo clusters](https://www.unige.ch/eresearch/en/services/hpc/) of the university of Geneva. To get an access, [follow the instructions](https://www.unige.ch/eresearch/en/services/hpc/guidelines/).

⚠️ These clusters are shared by all the researchers of the UniGE. You might have to wait in the queue!


## 2. Prepare your user account

### 2.1 Access the cluster

Our cluster uses [slurm](https://en.wikipedia.org/wiki/Slurm_Workload_Manager) for managing the jobs. You fill find documentation for the Geneva cluster [here](https://doc.eresearch.unige.ch/hpc/slurm#).


To access the cluster:

```bash
ssh PSEUDO@login1.baobab.hpc.unige.ch
```

or

```bash
ssh PSEUDO@login1.yggdrasil.hpc.unige.ch
```

Baobab and Yggdrasil are the two supercomputers of the university of Geneva. About their differences, and why use one rather than another, you will have all the details [here](https://doc.eresearch.unige.ch/hpc/hpc_clusters).

⚠️ We recommend using _Baobab_. It has more GPUs than Yggdrasil.

At the UniGE, `PSEUDO` should be your surname, sometimes followed by the first letter of your given name (_John Doe_ -> `doe` or `doej`), so:

```bash
ssh doejlogin1.baobab.hpc.unige.ch
```

To exit the cluster:

```bash
exit
```

You will also need to add the path to the `.bashrc` with:

```bash
nano ~/.bashrc
```

At the end, copy and paste: `export PATH="/home/users/g/PSEUDO/.local/bin:$PATH"` (for instance). You should have:

```
# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
        . /etc/bashrc
fi

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions

export PATH="/home/users/g/PSEUDO/.local/bin:$PATH"
```

⚠️ Replace `PSEUDO` by _your own_ pseudo AND the letter in `/home/users/g` with the first letter of your pseudo (`gabays`->`g`, `doej`->`d`)

**Do not forget to change the value of `PSEUDO`**

To save `ctrl+x`, `ctrl+y` and `enter`.

You can copy files from one cluster (here from Yggdrasil) to another with:

```bash
scp doej@login1.yggdrasil.hpc.unige.ch:/home/users/g/gabays/file.txt .
```

### 2.1 Loading modules

Your environment is empty: for instance, there is not python. You need to load a specific python module to use python. If you already know which one you need, you can load it like this:

```bash
module load GCCcore/11.2.0 Python/3.9.6
```

⚠️ You need [GCC](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection) to use [CPython](https://en.wikipedia.org/wiki/CPython).

You can control that the module is loaded with:

```bash
NAME --version
```

For instance:

```bash
python --version
```

You can have a look at all the modules you have loaded with:

```
module list
```

Note that the version must be chosen according to the "things" you need to install. You can look for all the available modules with:

```bash
module avail
```

Or check all the available versions with:

```bash
module spider NAME
```

⚠️ The name is case sensitive: `Python` and not `python`, `CUDA` and not `cuda`, etc.

For instance:

```bash
module spider Python
```

Or look at the description of specific version:

```bash
module spider NAME/version
```

For instance:

```bash
module spider Python/3.8.6
```

To start anew (and avoid conflicts, etc), it is recommended to purge all modules when submitting a task with:

```bash
module purge
```

### 2.2 Installing _Kraken_

We can now install _Kraken_. To begin with, let's purge the environment (in case there is something else that would create a conflict):

```bash
module purge
```

Now we can load all the required modules:

```bash
module load CUDA/11.8.0 GCCcore/11.2.0 Python/3.9.6
```

⚠️ We need `CUDA` to use the GPUs, on top of Python.

⚠️ Former command `module load fosscuda/2020b Python/3.8.6` is now deprecated.

⚠️ This list of modules might need to be adapted according to your cluster's specifications.

It is highly recommended to work with a virtual environment (henceforth `VENV`), which can be created with:

```bash
python3 -m venv PATH/TO/VENV
```

For instance, if you choose the name `kraken-env`:

```bash
python3 -m venv kraken-env
```

Now that it is created, we can activate the virtual environment:

```bash
source PATH/TO/VENV/bin/activate
```

For instance, if it is in the root directory:

```bash
source ~/kraken-env/bin/activate
```

⚠️ Load the module first, activate the VENV after.


`(kraken-env)` (or the name of your VENV) should appear at the beginning of the line.

```bash
(kraken-env) (baobab)-
```

Now you can install a _Kraken_ via pip. In some cases you might have to upgrade pip before:

```bash
pip install --upgrade pip
```

Now you can install _Kraken_. 

```bash
pip install kraken albumentations
```

⚠️ The `albumentations` package is not compulsory, but is required if you want to do data augmentation during training.

You can control that it is installed with:

```bash
kraken --version
```

Now we need to install torch compatible with our `CUDA` package:

```bash
pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118
```

You can control if torch is properly installed:

`torch==`:
```bash
python -m pip freeze
```

You should fine in the list something like `torch==2.0.1`. Now we need to control if `CUDA` is properly installed. Write:

```bash
python
```

Then:
```bash
import torch
```

And finally:
```bash
print (torch.__version__)
```

The answer should be: `2.0.1+cu117`.

If you need to deactivate the virtual environment, you need to execute:

```bash
deactivate
```

### 2.3 Additionnal commands

Memory is not free and unlimited. Regulary check how much space you are using:

```bash
du -hs * | sort -h
```

You might also need to see how many nodes are available:

```
sinfo
```

## 3. How to train a model?

### 3.1 Asking for a GPU

- Don't forget to activate the virtual environment
- Check if kraken is installed: `kraken --version`
- you can purge all modules with `module purge`

You first need to download the data. If it is on a GitHub/GitLab repo:

```bash
git clone https://github.com/FoNDUE-HTR/REPO.git
cd REPO
```

For instance:

```bash
git clone https://github.com/FoNDUE-HTR/Documentation
cd Documentation
```

**This repo contains sample data that will be used later in this tutorial.**

You need now to ask for a GPU. If you want to test that everyhting is OK, you can first run a test with a `debug-gpu` with:

```bash
salloc --partition=debug-gpu --time=00:10:00 --gpus=1
```

A description of all the partitions is available [online](https://doc.eresearch.unige.ch/hpc/slurm), with the maximum time for each of them.
- `debug-gpu` is available for 15mn max
- `shared-gpu` is available for 12h max
- `public-gpu` is available for 96h max

To have a `shared-gpu` during one hour you should ask for:

```bash
salloc --partition=shared-gpu --time=01:00:00 --gpus=1
```

For a very big dataset you might need several days:

```bash
salloc --partition=public-gpu --time=2-00:00:00 --gpus=1
```

-> **Yes: you need to know in advance for how long you will need the GPU!**

Several paramters can be added:

- `salloc` asks for a GPU
- `--partition` says which kind of GPU you need.
- `--time` says for how long you want it
- `--gpus` says how many GPUs you need. You can specify the model such as `--gpus=titan:1`
- `--ntasks` allows to run parallel distributed jobs, and specifies the number of processes (or tasks) that run simultaneously
- `--cpus-per-task` sets the number of CPU per task, it should be equal to the amount of threads.
- `--mem` sets the minimum amount of CPU RAM (not the GPU!)
- `--gres` allows you to select a GPU with a minimum quantity of RAM

A reasonable `salloc` for training would be:

```bash
salloc --partition=shared-gpu --time=05:00:00 --gpus=1 --mem=12GB --cpus-per-task=4
```

⚠️ _Kraken_ (like many computer vision tools) requires more memory than the one allocated with `--ntasks=1`. Rather than increasing the amount of tasks (e.g. `--tasks=4`), we recommend to increase the RAM on the CPU with `--mem` (e.g. `--mem=12GB`). 

⚠️ If your process is `killed`, it usually means that you do not have enough memory. Either you diminish what you use (e.g. smaller batch size), either you cancel your job and ask for a new one with more memory.

⚠️ Processing important amount of data requires much more memory, especially if you increase the batch size. If you get a `RuntimeError: DataLoader worker (pid XXXXXX) is killed by signal: Killed.`, it is because your GPU does not have enough RAM: consider increasing it with `salloc` (e.g. `--gres=gpu:1,VramPerGpu:24GB` for 24 GB).

⚠️ The more you ask for, the more you wait!

### 3.2 With commmand lines

⚠️ You have to load the requires modules each time you get allocated a GPU. For _Kraken_ users:

```bash
module load CUDA/11.8.0 GCCcore/11.2.0 Python/3.9.6
```

and then activate your virtual environement (in that order):

```bash
source ~/kraken-env/bin/activate
```

You can now train a model for HTR:

```bash
ketos train -f alto -d cuda:0 PATH/TO/*xml
```

- `-f` says which kind of data you have (possible options are `alto` or `page`).
- `-d cuda` is required to use the GPU
- `PATH/TO/*xml` is the path to the folder with all the xml files and the images.

For instance:

```bash
ketos train -f alto -d cuda:0 data/*xml
```

A (very simple) tutorial for Kraken can be found [here](https://github.com/FoNDUE-HTR/Documentation/blob/master/KRAKEN.md).

To train a model for segmentation, the command is:

```bash
ketos segtrain -f alto -d cuda:0 PATH/TO/*xml
```

For instance:

```bash
ketos segtrain -f alto -d cuda:0 data/*xml
```

It is possible to add the arguments presented just above.

### 3.3 Using a submission script

Rather than writing everything and wait (deserately) in front of your computer you get allocated the resources you asked for, you can use a submission script, gathering all the informations in a bash file:

```bash
#!/bin/env bash
#SBATCH --partition=public-gpu
#SBATCH --time=2-00:00:00
#SBATCH --gpus=1
#SBATCH --output=kraken-%j.out
#SBATCH --mem=24GB
#SBATCH --ntasks=12
#SBATCH --gres=gpu:1,VramPerGpu:24GB

module load fosscuda/2020b Python/3.8.6
source ~/kraken-env/bin/activate

OUTPUT_NAME="output_name"
XML_FOLDER="/home/users/g/PSEUDO/Documentation/data"

echo "KETOS training"
srun ketos train -o $OUTPUT_NAME -f alto -d cuda:0 "${XML_FOLDER}/*.xml"
```

The script can be executed with:

```bash
sbatch NAME.sh
```

for instance (to train an HTR model):
```bash
sbatch submission_scripts/submission-rec.sh
```

or (to train a segmentation model):
```bash
sbatch submission_scripts/submission-seg.sh
```

You should be given the job id:
```console
Submitted batch job 0000000
```
You can check the state of the job with the following command:
```bash
squeue -j 0000000
```

`-j` being followed of the job ID.

You can check when the job starts. `PD` (pending) means it has not started yet:

```bash
(baobab)-[doej@login2 ~]$ squeue -j 7637204
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
           7637204 shared-gp submissi   doej PD       0:00      1 (Priority)
```

`R` means the job is running:
```bash
(baobab)-[doej@login2 ~]$ squeue -j 7637204
             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
           7637204 shared-gp submissi   doej  R       3:47      1 gpu014
```

You have access to the log:
```bash
cat kraken-0000000.out 
```

You can open a new tab to see what is happening. First get the name of the machine (in the previous example `gpu014`) and connect yourself to this machine:

```bash
ssh gpu014
```

Two commands can be used to  to monitor the (running) job in real time:

```bash
htop
```

Another command monitors only the GPU:

```bash
watch -n 1 nvidia-smi
```

At the end of the job, you can have a look at what happened (memory use, GPU use, total computation time…)

```bash
seff
```

It will help you tailor your `salloc` to your needs!