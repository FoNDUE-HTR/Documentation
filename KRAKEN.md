# _Kraken_

You will find some basic instructions about _Kraken_ command lines to use the cluster.

🚨 Before doing anything: do consider you are using free softwares. Citing them is important for developers.

_Kraken_:
```bibtex
@inproceedings{Z9G2EX_2019,
author = {Kiessling, Benjamin},
publisher = {DataverseNL},
title = {{Kraken - a Universal Text Recognizer for the Humanities}},
booktitle ={Digital Humanities Conference 2019},
year = {2019},
month = Jul,
address = {Utrecht, The Netherlands},
version = {V2},
doi = {10.34894/Z9G2EX},
url = {https://doi.org/10.34894/Z9G2EX}
}
```

The official repo is here: https://github.com/mittagessen/kraken

_YALTAi_:

```bibtex
@article{clerice:hal-03723208,
  TITLE = {{You Actually Look Twice At it (YALTAi): using an object detection approach instead of region segmentation within the Kraken engine}},
  AUTHOR = {Cl{\'e}rice, Thibault},
  URL = {https://enc.hal.science/hal-03723208},
  JOURNAL = {{Journal of Data Mining and Digital Humanities}},
  PUBLISHER = {{INRIA}},
  VOLUME = {Documents historiques et reconnaissance automatique de texte},
  YEAR = {2023},
  MONTH = Dec,
  DOI = {10.46298/jdmdh.9806},
}
```

🚨 If you use models that already exist, please cite them as well.

## On _eScriptorium_ and _Kraken_

You can access our infrastructure at the following adress: https://test.fondue.unige.ch/. It uses [_eScriptorium_](https://gitlab.inria.fr/scripta/escriptorium), an open source initiative of the EPHE and the INRIA. The HTR engine is [_Kraken_](https://github.com/mittagessen/kraken), which is also _open source_.

Several online resources can be used:
- A [15' video](https://datascience.unige.ch/forall/capsules-video/fondue-linfrastructure-htr-de-lunige) offering an overview of _eScriptorium_. Access restricted to UniGE members. In French.
- A [10' video](https://datascience.unige.ch/forall/capsules-video/exploiter-des-donn%C3%A9es-analogiques) on OCR. Access restricted to UniGE members. In French.
- A [series of videos](https://www.youtube.com/watch?v=N0hSNC3YvD4) on eScriptorium. In English.
- The [OCR seminar](https://mediaserver.unige.ch/play/VN3-4929-2022-2023) of the UniGE. In French.
- A [written tutorial](https://lectaurep.hypotheses.org/documentation/escriptorium-tutorial-en) on eScriptorium. In English.
- A [written tutorial](https://lectaurep.hypotheses.org/documentation/prendre-en-main-escriptorium) on eScriptorium. In French.

The [documentation of YALTAi](https://github.com/PonteIneptique/YALTAi) provides basic information on its use.

## 1. Use _Kraken_

To process a page, you will need to use

```bash
kraken -i image.png out.txt binarize segment -bl -i segment.mlmodel ocr -m recognize.mlmodel
```
where

- `-i image.png` gives the path to the image you want to process. You can add many images (`image1.png image2.png image3.png`) or indicate a directory (`images/*png`);
- `out.txt` the name of the file in which the text will be saved. The options `-a` (for ALTO) or `-x` (for PAGE XML) can be added to have an ALTO or a PAGE XML file (then, preferably use `out.xml`);
- `segment` indicates that we now pass subcommands regarding the segmentation;
	- `-bl` indicates that we switch to a new segmenter
	- `-i segment.mlmodel` gives the path to the segmentation model you want to use
- `segment` indicates that we now pass subcommands regarding the OCRisation
	- `-m recognize.mlmodel` gives the path to the OCR model you want to use


Several models are available. To check if one fulfills your needs:
```bash
kraken list
```

Get the Zenodo code of the model and download it.
```bash
kraken get 10.5281/zenodo.10602357
```

You will find the same list on [Zenodo](https://zenodo.org/communities/ocr_models) if you need to do it manually.


An example of command would be

```bash
kraken -i data/Balzac1624_Lettres_btv1b86262420_corrected_0011.png results.txt segment -bl ocr -m catmus-print-fondue-tiny-2024-01-31.mlmodel
```

To process multiple pages, you will need to point to the directory (`data`) and select only the images (`*png`):

```bash
kraken -I 'data/*png' -o out.txt segment -bl -i segment.mlmodel ocr -m recognize.mlmodel
```

An example would be:

```bash
kraken -I 'data/*png' -o results.txt segment -bl ocr -m catmus-print-fondue-tiny-2024-01-31.mlmodel
```

If you want the result in ALTO you can use `--alto`:

```bash
kraken -I 'data/*png' --alto segment -bl ocr -m catmus-print-fondue-tiny-2024-01-31.mlmodel
```

## 2. Prepare the data

Machine learning requires to split your data between ([more information here](https://en.wikipedia.org/wiki/Training,_validation,_and_test_sets)).
- a train set (data to train the data)
- a validation set (data to evaluate each iteration)
- a test set (data to test the final model)

It can be useful to explicitly specify which page goes into which set and create three files (names can be changed):
- `train.txt`
- `eval.txt`
- `test.txt`

in which you give the path to the xml files used (one per line), such as (an example can be found [here](https://github.com/FoNDUE-HTR/Documentation/tree/master/split)):

```
data/Balzac1624_Lettres_btv1b86262420_corrected_0015.xml
data/Balzac1624_Lettres_btv1b86262420_corrected_0022.xml
data/Balzac1624_Lettres_btv1b86262420_corrected_0023.xml
```

This will allow, for instance, a strict comparison of results, because the test set will be the same for each training (if you change the amount of training data).

We provide [a script to distribute randomly the data](https://github.com/FoNDUE-HTR/Documentation/blob/master/split/split.py) (90% in train, 10% in validation and 10% for testing), which can be used the following way:

```bash
python3 split.py PATH/TO/*.xml
```

It can also be done manually. First create a manifest (e.g. a list with all the files you want to use):
```bash
find data/ -type f -name "*.xml" > output.txt
```

And now select the files you need for `train`, `val` and `test`.

## 3. `ketos train`

### 3.1 Basic training

to train a model:

```bash
ketos train -f alto PATH/TO/*xml
```

For instance:

```bash
ketos train -f alto data/*xml
```

- `-f` says which kind of data you have (possible options are `alto` or `page`).
- `PATH/TO/*xml` is the path to the folder with all the xml files and the images.

### 3.2 Using splits

More options are available (`kraken --help` or [here](https://github.com/mittagessen/kraken/blob/master/docs/ketos.rst) for more informations), for instance:
- `-t` + the path of a `.txt` file with a list of `.xml` files in the _train set_
- `-e` + the path of a `.txt` file with a list of `.xml` files in the _evaluation set_
- You can use early stopping with `-q early` (more informations [here](https://en.wikipedia.org/wiki/Early_stopping)).

You can now train a model using sets prepared in advance:

```bash
ketos train -t split/train.txt -e split/eval.txt -f alto
```

It is recommended to apply an [Unicode normalization](https://en.wikipedia.org/wiki/Unicode_equivalence) (possible value is `NFD`, `NFKD`, `NFC` or `NFKC`), using the `--normalization` flag, or just `-u`.

```bash
ketos train -t split/train.txt -e split/eval.txt -f alto --normalization NFD
```

⚠️ These normalisations can have an impact on the accuracy of the model.

### 3.3 Compiling data

You can compile data before training:

```bash
ketos compile -F train.txt -f alto --workers 2
ketos compile -F eval.txt -f alto --workers 2
```

And now just point to the `train.arrow` and `eval.arrow` and change the format to `binary` for training:

```bash
ketos train -t train.arrow -e eval.arrow -f binary -u NFD
```

You might have the following error:

```bash
UnicodeDecodeError: 'utf-8' codec can't decode byte 0xff in position 8: invalid start byte
```

Then try:

```bash
ls train.arrow eval.arrow | xargs ketos train -f binary -u NFD
```

### 3.4 Additional option

Several additional options are available:
- `--augment` will add [data augmentation](https://en.wikipedia.org/wiki/Data_augmentation) while training.
- `--precision 16` will enable [automatic mixed precision](https://pytorch.org/tutorials/recipes/recipes/amp_recipe.html). It speedsup the training and reduce the memory consumption.
- `-B` followd by an integer (possible values: 64, 32, 16, 8…) will set the batch size, i.e. the number of examples seen before the model's parameter are updated.

⚠️ `--augment` requires the package `albumentations`.

```bash
ketos train -t train.arrow -e eval.arrow -f binary -u NFD  -B 8 --precision 16 --augment
```

### 3.3 Using the cluster

Using the cluster allows to used advanced options to increase the speed or the accuracy:
- `-d cuda:0` is required to use the GPU
- `--workers` for the number of OpenMP threads (possible values: `1`, `3`, `8`… max `12` on UniGE cluster's).
- `--lag` (only used when using [early stopping](https://en.wikipedia.org/wiki/Early_stopping)) for the number of epochs to wait before stopping training without improvement (possible values: `5`, `20`…).
- `-r` for the [learning rate](https://en.wikipedia.org/wiki/Learning_rate) (possible values: `0.001`/`1e-3`, `0.0001`/`1e-4`): it determines the step size at each iteration while moving toward a minimum of a loss function.

⚠️ It is recommended to scale the learning rate by the square root of the batch size (`1e-3 * sqrt(batch_size)` or `1e-4 * sqrt(batch_size)`).


```bash
ketos train -t train.arrow -e eval.arrow -f binary -u NFD -B 8 --precision 16 --augment -d cuda:0 -r 0.0003 --lag 5 --workers 8
```

⚠️ A value of `8` for `-B` should be OK for any GPU available on the cluster, even older one that will guarantee a quick access to the machines.

⚠️ The number of threads should be equal to the amount CPUs allocated per task. In other words `--workers 8` during training requires `--cpus-per-task=8` when doing the `salloc`. 

⚠️ Processing important amount of data requires much more memory, especially if you increase the batch size. If you get a `RuntimeError: DataLoader worker (pid XXXXXX) is killed by signal: Killed.`, it is because your GPU does not have enough RAM: consider increasing with `salloc` (e.g. `--gres=gpu:1,VramPerGpu:24G` for 24 GB).


### 3.4 Fine tuning

It is possible to [fine tune](https://en.wikipedia.org/wiki/Fine-tuning) an existing model with `-i` + the model to fine tune:

```bash
ketos train -i PATH/TO/model.mlmodel -t PATH/TO/*.xml
```

It is recommended, when fine tuning a model, to use the `--resize union` command in case some characters would not be present in the original training. Do not forget to specify the format

```bash
ketos train -f alto -i PATH/TO/model.mlmodel --resize union -t PATH/TO/*.xml
```

### 3.5 Reading results

Each iteration of the training will generate a model such as:

```
MODEL_NAME_1.mlmodel
MODEL_NAME_2.mlmodel
MODEL_NAME_3.mlmodel
MODEL_NAME_4.mlmodel
MODEL_NAME_5.mlmodel
…
```

The best model will be automatically selected and will be labelled:

```
MODEL_NAME_best.mlmodel
```

## 4. `ketos test`

Now that you have a model, you can test it on the `test.txt` data if you have prepared such a file with `ketos test`:

```bash
ketos test -f alto -m PATH/TO/MODEL.mlmodel -e test.txt>eval_model.txt
```

(Do not forget to change the value of the `-f` flag if you have data in another format such as `PAGExml`.)

This command will test the selected model and store the results of the test in a file called `eval_model.txt`.

## 5. `ketos segtrain`

The `ketos segtrain` allows to train a segmentation model: it recognises various zones or regions on the page (images, running titles…). To segment a page, we recommend to use the [_SegmOnto_ controlled vocabulary](https://github.com/SegmOnto/Guidelines/).

The commands are really similar to those of `ketos train`.

## 6. `ketos segtrain`: the _YALTAi_ alternative

```bash
pip install YALTAi
```

⚠️ If you install YALTAi, you install also Kraken.

### 6.1 Convert the data

Convert (and split optionally) your data:

```bash
# Keeps .1 data in the validation set and convert all alto into YOLOv5 format
yaltai alto-to-yolo PATH/TO/ALTOorPAGE/*.xml my-dataset --shuffle .1
```

If the data uses the [SegmOnto](https://segmonto.github.io/) controlled vocabulary you can use the `--segmonto` flag.

```bash
# Keeps .1 data in the validation set and convert all alto into YOLOv5 format
yaltai alto-to-yolo PATH/TO/ALTOorPAGE/*.xml my-dataset --shuffle .1 --segmonto region
```

Possible values are :
- `region` if you do not use subtypes
- `subtype` if you use subtypes

This step will create a `my-dataset/config.yml` file in the directory where the command is launched.

### 6.2 Train the model

You can now train a model using the _Yolo_ algorithm.

```bash
yolo task=detect mode=train model=yolov8n.pt data=my-dataset/config.yml epochs=100 plots=True device=0 batch=8 imgsz=960
```

Possible modifications are:
- `--workers 6` (value may vary) to use many worker threads to train the model (to speed up training with multicore machines).
- You can use large images with `--img 1280`. If you do, do use a P6 model configuration adapted for larger image size by using `--weights yolov5x6.pt`

For instance:

```bash
python train.py --data "../my-dataset/config.yml" --batch-size 4 --img 1280 --weights yolov5x6.pt --epochs 50 --workers 6
```

⚠️ Enlarging the size of the image (640->1280) requires much more memory, and you may have to reduce the size of the batch to 2.

### 6.3 Prediction

You need first to check in the `yolov5` directory the name of the directory in which the weights are:

```bash
yaltai kraken --device cuda:0 -I "*.jpg" --suffix ".xml" segment --yolo runs/train/exp5/weights/best.pt
```

⚠️ There might be different directoy named `exp1`, `exp2`, `exp3`… Depending on how many models have been trained. Adapt accordingly the path below:

```bash
# Retrieve the best.pt after the training
# It should be in runs/train/exp[NUMBER]/weights/best.pt
# And then annotate your new data with the same CLI API as _Kraken_ !
yaltai kraken --device cuda:0 -I "*.jpg" --suffix ".xml" segment --yolo runs/train/ADAPT HERE/weights/best.pt
```

If you do not have a GPU, you can use a CPU with `--device cpu`. An optional `--deskew` optin is available to straighten skewed pages. 
