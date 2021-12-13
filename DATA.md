# Distributing data and models

We recommend to follow the instructions given by [HTR-united](https://github.com/HTR-United/).

1. The repositories can be hosted directly on HTR-united or self-hosted with the FoNDUE-HTR organisation. In the second case, please make sure to add a `htr-united.yml` file in the repo and to register your repo. More information [here](https://github.com/htr-united/htr-united).
2. Actions (or continuous integration) are not mandatory but are recommended to ensure data consistency and quality. You can find more information about continuous integration [here (in French)](https://www.youtube.com/watch?v=Jk5aSIzIxXE).
3. It is highly recommende to use [HTRUC](https://github.com/HTR-United/htr-united/blob/master/.github/workflows/HTRUC.yaml) to test the validity of the `htr-united.yml` file, and [HUM Generator](https://github.com/HTR-United/htr-united-metadata-generator/blob/main/TUTORIAL.md) (to generate metadata). If you use [SegmOnto](https://github.com/SegmOnto/Guidelines/), it is recommended to use HTRVX.
