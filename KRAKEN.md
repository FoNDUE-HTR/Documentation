# Kraken

You will find some basic instructions about Kraken command lines to use the cluster.

## 1. Use Kraken

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

An example of command would be

```bash
kraken -i OCR17plus/Data/Balzac1624_Lettres_btv1b86262420_corrected/png/Balzac1624_Lettres_btv1b86262420_corrected_0042.png results.txt segment -bl -i OCR17plus/Model/Segment/appenzeller.mlmodel ocr -m OCR17plus/Model/HTR/dentduchat.mlmodel
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

We provide [a script to distribute randomly the data](https://github.com/FoNDUE-HTR/Documentation/blob/master/split/split.py) (written by J.-B. Camps), which can be used the following way:

```bash
python3 split.py PATH/TO/*.xml
```

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

### 3.2 Advanced training

More options are available (`kraken --help` or [here](https://github.com/mittagessen/kraken/blob/master/docs/ketos.rst) for more informations), for instance:
- `-t` + the path of a `.txt` file with a list of `.xml` files in the _train set_
- `-e` + the path of a `.txt` file with a list of `.xml` files in the _evaluation set_
- You can use early stopping with `-q early` (more informations [here](https://en.wikipedia.org/wiki/Early_stopping)).

You can now train a model using sets prepared in advance:

```bash
ketos train -t split/train.txt -e split/eval.txt -f alto
```

It is recommended to no apply an [Unicode normalization](https://en.wikipedia.org/wiki/Unicode_equivalence) (possible value is `NFD`), using the `--normalization`.

```bash
ketos train -t split/train.txt -e split/eval.txt -f alto --normalization NFD
```

### 3.3 Using the cluster

Using the cluster allows to used advanced options to increase the speed or the accuracy:
- `-d cuda:0` is required to use the GPU
- `--workers` for the number of OpenMP threads (possible value is `20`).
- `--lag` (only used when using early stopping) for the number of epochs to wait before stopping training without improvement (possible value is `20`).
- `-r` for the learning rate (possible value is `0.0001`)
- `--augment` Enables data augmentation.


```bash
ketos train -t split/train.txt -e split/eval.txt -f alto -d cuda:0 -r 0.0001 --lag 10 --normalization
```

### 3.4 Fine tuning

It is possible to [fine tune](https://en.wikipedia.org/wiki/Fine-tuning) an existing model with `-i` + the model to fine tune:

```bash
ketos train -i PATH/TO/model.mlmodel PATH/TO/*.xml
```

It is recommended, when fine tuning a model, to use the `--resize add` command in case some characters would not be present in the original training.

```bash
ketos train -i PATH/TO/model.mlmodel --resize add PATH/TO/*.xml
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

## 5. `ketos segtrain`: the YALTAi alternative

More info on the official repo: https://github.com/PonteIneptique/YALTAi

```bash
pip install YALTAi
```

### 5.1 Convert the data

Convert (and split optionally) your data:

```bash
# Keeps .1 data in the validation set and convert all alto into YOLOv5 format
yaltai alto-to-yolo PATH/TO/ALTOorPAGE/*.xml my-dataset --shuffle .1
```

If the data uses the SegmOnto format you can use the `--segmonto` flag.

```bash
# Keeps .1 data in the validation set and convert all alto into YOLOv5 format
yaltai alto-to-yolo PATH/TO/ALTOorPAGE/*.xml my-dataset --shuffle .1 --segmonto region
```

Possible values are :
- `region` if you do not use subtypes
- `subtype` if you use subtypes

This step will create a `my-dataset/config.yml` file in the directory where the grountruth is.

### 5.2 Train the model

You need to download YOLOv5

```bash
# Download YOLOv5
git clone https://github.com/ultralytics/yolov5  # clone
cd yolov5
git checkout v6.2
pip install -r requirements.txt  # install
```

You can now train a model:

```bash
# Train your YOLOv5 data (YOLOv5 is installed with YALTAi)
python train.py --data "../my-dataset/config.yml" --batch-size 4 --img 640 --weights yolov5x.pt --epochs 50
```

Possible modifications are:
- `--workers 6` (value may vary) to use many worker threads to train the model (to speed up training with multicore machines).
-- You can use large images with `--img 1280`. If you do, do use a P6 model configuration adapted for larger image size by using `--weights yolov5x6.pt`

For instance:

```bash
python train.py --data "../my-dataset/config.yml" --batch-size 4 --img 1280 --weights yolov5x6.pt --epochs 50 --workers 6
```

### 5.3 Prediction

You need first to check in the `yolov5` diretory the name of the directory in which the weights are:

```bash
yolov5/runs/train
```

There might be different directoy named `exp1`, `exp2`, `exp3`… Depending on how many models have been trained. Adapt accordingly the path below:

```bash
# Retrieve the best.pt after the training
# It should be in runs/train/exp[NUMBER]/weights/best.pt
# And then annotate your new data with the same CLI API as Kraken !
yaltai kraken --device cuda:0 -I "*.jpg" --suffix ".xml" segment --yolo runs/train/ADAPT HERE/weights/best.pt
```

If you do not have a GPU, you can use a CPU with `--device cpu`.