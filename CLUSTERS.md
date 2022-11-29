# Using the clusters

FoNDUE is an HTR infrastructure for the university of Geneva. More information here: https://www.unige.ch/lettres/humanites-numeriques/recherche/projets-de-la-chaire/fondue

## 1. Using the infrastructure:

You can access our infrastructure at the following adress: https://test2.fondue.unige.ch/. You can find a tutorial in English [here](https://lectaurep.hypotheses.org/documentation/escriptorium-tutorial-en) and in French [here](https://lectaurep.hypotheses.org/documentation/prendre-en-main-escriptorium).

It uses [_eScriptorium_](https://gitlab.inria.fr/scripta/escriptorium), an open source initiative of the EPHE and the INRIA. The HTR engine is [_Kraken_](https://github.com/mittagessen/kraken), which is also _open source_.

Our instance uses the [Baobab and the Yggdrasil clusters](https://www.unige.ch/eresearch/en/services/hpc/) of the university of Geneva. To get an access, [follow the instructions](https://www.unige.ch/eresearch/en/services/hpc/guidelines/).

## 2. Prepare your user account

Our cluster uses [slurm](https://en.wikipedia.org/wiki/Slurm_Workload_Manager) for managing the jobs. You fill find documentation for the Geneva cluster [here](https://doc.eresearch.unige.ch/hpc/slurm#).

⚠️ The DH unit does not own a node yet, so completion of tasks might be slow.

To access the cluster:

```bash
ssh PSEUDO@baobab2.hpc.unige.ch
```

or

```bash
ssh PSEUDO@login1.yggdrasil.hpc.unige.ch
```

Baobab and Yggdrasil are the two supercomputers of the university of Geneva. About their differences, and why use one rather than another, you will have all the details [here](https://doc.eresearch.unige.ch/hpc/hpc_clusters).

⚠️ We recommend using _Yggdrasil_.

At the UniGE, `PSEUDO` should be your surname, sometimes followed by the first letter of your given name (_John Doe_ -> `doe` or `doej`), so:

```bash
ssh doej@login1.yggdrasil.hpc.unige.ch
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

⚠️ Replace `PSEUDO` by _your own_ pseudo.

**Do not forget to change the value of `PSEUDO`**

To save `ctrl+x`, `ctrl+y` and `enter`.

### 2.1 Loading modules

Your environment is empty: for instance, there is not python. You need to load a specific python module to use python. If you already know which one you need, you can load it like this:

```bash
module Python/3.8.6
```

You can control that the modules is loaded with:

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

For instance:

```bash
module spider python
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

We can now install _Kraken_. To begin with, let's load all the required modules:

```bash
module load fosscuda/2020b Python/3.8.6
```

More information about `fosscuda` is available [here](https://doc.eresearch.unige.ch/hpc/applications_and_libraries#fosscuda_toolchain).


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

`(kraken-env)` (or the name of your VENV) should appear at the beginning of the line.

If you need to deactivate the virtual environment, you need to execute:

```bash
deactivate
```

Now you can install a _Kraken_ via pip. First upload pip:

```bash
pip install pip-tools==6.6.2 pip==22.1.2
```

Now you can install _Kraken_. We highly recommend to use a `requirements` list that we have prepared:

```bash
wget https://raw.githubusercontent.com/FoNDUE-HTR/Documentation/master/requirements.txt
pip install -r requirements.txt
```

You can control that it is installed with:

```bash
kraken --version
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
- `public-gpu` is available for 24h max

To have a `shared-gpu` during one hour you should ask for:

```bash
salloc --partition=shared-gpu --time=01:00:00 --gpus=1
```

For a very big dataset:

```bash
salloc --partition=public-gpu --time=40:00:00 --gpus=1
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

⚠️ Some tools need to process data, and several processes dedicated to loading data are created You need to increase the value of `--ntasks` to have them run properly.

⚠️ _Kraken_ (like many computer vision tools) requires more memory than the one allocated with `--ntasks=1`. Rather than increasing the amount of tasks (e.g. `--tasks=4`), we recommend to increase the RAM on the CPU with `--mem` (e.g. `--mem=12GB`). When doing that, make sure the memory allocated to the GPU (e.g. `--gres=gpu:1,VramPerGpu:12GB` for 12 GB) is at least equal to the value of `--mem`.

⚠️ Processing important amount of data requires much more memory, especially if you increase the batch size. If you get a `RuntimeError: DataLoader worker (pid XXXXXX) is killed by signal: Killed.`, it is because your GPU does not have enough RAM: consider increasing it with `salloc` (e.g. `--gres=gpu:1,VramPerGpu:24GB` for 24 GB).

```bash
salloc --partition=shared-gpu --time=01:00:00 --gpus=1 --mem=12GB --cpus-per-task=8 --gres=gpu:1,VramPerGpu:12GB
```

### 3.2 With commmand lines

⚠️ You have to load the requires modules each time you get allocated a GPU. For _Kraken_ users:

```bash
module load fosscuda/2020b Python/3.8.6
```

and then activate your virtual environement:

```bash
source ~/kraken-env/bin/activate
```

You can now train a model for HTR:

```bash
ketos train -f alto -d cuda:0 PATH/TO/*xml
```

For instance:

```bash
ketos train -f alto -d cuda:0 data/*xml
```

- `-f` says which kind of data you have (possible options are `alto` or `page`).
- `-d cuda` is required to use the GPU
- `PATH/TO/*xml` is the path to the folder with all the xml files and the images.

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

Rather than writing everything, you can use a submission script, gathering all the informations in a bash file:

```bash
#!/bin/env bash
#SBATCH --partition=shared-gpu
#SBATCH --time=01:00:00
#SBATCH --gpus=1
#SBATCH --output=kraken-%j.out
#SBATCH --mem=10000
#SBATCH --ntasks=2
#SBATCH --gres=gpu:1,VramPerGpu:10000

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
