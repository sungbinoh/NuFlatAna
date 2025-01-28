# A simple root macros for analyzing flat Ntuples from the NUISANCE

## Based on

Afro's repo: https://github.com/afropapp13/myNEUTAnalysis

## Install

```
$ git clone git@github.com:sungbinoh/NuFlatAna.git
$ cd NuFlatAna
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build . -- install
$ cd ..
```

There should be an executable file "run_cohpiana" generated in the main directory.

## Run

You should copy input flat root files in ./input directory.
Then, in the main directory,
```
$ ./run_cohpiana <filename>.root <sample_name>
```
Then, "hists_<sample_name>.root" file will be generated in "./output/root" directory.

## Modifying the analyzer

Please check ".src/cohpiana.C".
In "cohpiana::executeEvent()" function, final state particles are collected using FSP class.
Then, histograms of various kinematic variables are filled with a correct weights for producing cross-section histograms.

If you updated the analyzer, area should be build again using "cmake".
