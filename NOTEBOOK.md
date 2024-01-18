# _Notebook_

You can use the complete pipeline with [this notebook](https://github.com/FoNDUE-HTR/Documentation/blob/master/notebook_pipeline.ipynb).

This notebook is adapted for the [OpenOnDemand](https://ondemand.baobab.hpc.unige.ch) service of the UniGE. If you want to use OpenOnDemand, you need to [ask first for an HPC account](https://catalogue-si.unige.ch/hpc).

When you are connected to OpenOnDemand:
- Go to `Jupyter Lab`
- select:
	- Partition: `shared-gpu`
	- The number of hours you will need the service (one book, c. 2h)
	- Cpu: `3` should be fine
	- Memory: `6` should be fine
	- Gpu: `1` is enough
- click on `Launch` and wait that you are allocated a GPU
- click on `Connect to Jupyter`
- When on Jupyter, select `File/Open from URL`, paste this url: `https://raw.githubusercontent.com/FoNDUE-HTR/Documentation/master/notebook_pipeline.ipynb`
- You're good to go! Bravo!

This notebook **should be** compatible with colab. Specific sections for colab are noted with the colab (<img width="25px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/Google_Colaboratory_SVG_Logo.svg/320px-Google_Colaboratory_SVG_Logo.svg.png"/>) logo. You can open the notebook directly on colab with the following link:

[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/FoNDUE-HTR/Documentation/blob/master/notebook_pipeline.ipynb)