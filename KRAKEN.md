# Kraken

You will find some basic instructions about Kraken command lines to use the cluster.

## Prepare the data

Machine learning requires to split your data between ([more information here](https://en.wikipedia.org/wiki/Training,_validation,_and_test_sets)).
- a train set (data to train the data)
- a validation set (data to evaluate each iteration)
- a test set (data to test the final model)

It can be useful to explicitly specify which page goes into which set and create three files (names can be changed):
- `train.txt`
- `eval.txt`
- `test.txt`
in which you give the path to the xml files used (one per line), such as:

```
data/Balzac1624_Lettres_btv1b86262420_corrected_0015.xml
data/Balzac1624_Lettres_btv1b86262420_corrected_0022.xml
data/Balzac1624_Lettres_btv1b86262420_corrected_0023.xml
```

This will allow, for instance, a strict comparison of results, because the test set will be the same for each training (if you change the amount of training data).

We provide a script to distribute randomly the data (written by J.-B. Camps), which can be used the following way:

```bash
python3 split.py PATH/TO/*.xml
```


## `ketos train`

### Basic training

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

### Advanced training

More options are available (`kraken --help` or [here](https://github.com/mittagessen/kraken/blob/master/docs/ketos.rst) for more informations), for instance:
- `-t` + the path of a `.txt` file with a list of `.xml` files in the _train set_
- `-e` + the path of a `.txt` file with a list of `.xml` files in the _evaluation set_
- You can use early stopping with `-q early` (more informations [here](https://en.wikipedia.org/wiki/Early_stopping)).

You can now train a model using sets prepared in advance:

```bash
ketos train -t split/train.txt -e split/eval.txt -f alto PATH/TO/*xml
```

It is recommended to no apply an [Unicode normalization](https://en.wikipedia.org/wiki/Unicode_equivalence) (possible value is `NFD`), using the `--normalization`.

```bash
ketos train -t split/train.txt -e split/eval.txt -f alto --normalization NFD PATH/TO/*xml
```

### Using the cluster

Using the cluster allows to used advanced options to increase the speed or the accuracy:
- `-d cuda` is required to use the GPU
- `--threads` for the number of OpenMP threads (possible value is `20`).
- `--lag` (only used when using early stopping) for the number of epochs to wait before stopping training without improvement (possible value is `20`).
- `-r` for the learning rate (possible value is `0.0001`)


```bash
ketos train -t split/train.txt -e split/eval.txt -f alto -d cuda -r 0.0001 --lag 20 --normalization NFD PATH/TO/*xml
```

### Fine tuning

It is possible to [fine tune](https://en.wikipedia.org/wiki/Fine-tuning) models with `-i`:

```bash
ketos train -i PATH/TO/model.mlmodel PATH/TO/*.xml
```

It is recommended, when fine tuning a model, to use the `--resize add` command in case some characters would not be present in the original training

```bash
ketos train -i PATH/TO/model.mlmodel --resize add PATH/TO/*.xml
```

### Reading results

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

## `ketos test`

Now that you have a model, you can test it on the `test.txt` data if you have prepared such a file with `ketos test`:

```bash
ketos test -m PATH/TO/MODEL.mlmodel -e test.txt>eval_model.txt
```

This command will test the selected model and store the results of the test in a file called `eval_model.txt`.

## `ketos segtrain`

The `ketos segtrain` allows to train a segmentation model: it recognises various zones or regions on the page (images, running titles…). To segment a page, we recommend to use the [_SegmOnto_ controlled vocabulary](https://github.com/SegmOnto/Guidelines/).

The commands are really similar to those of `ketos train`.



