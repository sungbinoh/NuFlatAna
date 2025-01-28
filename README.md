# A simple root macros for analyzing flat Ntuples from the NUISANCE

## Based on

Afro's repo: https://github.com/afropapp13/myNEUTAnalysis

## Install

```
$ git clone git@github.com:sungbinoh/NuFlatAna.git
$ cd NuFlatAna
$ source setup.sh
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

Please check ".src/cohpiana.C".\
In "cohpiana::executeEvent()" function, final state particles are collected using FSP class.\
Then, histograms of various kinematic variables are filled with a correct weights for producing cross-section histograms.

If you updated the analyzer, area should be build again using "cmake".

## Run Many input flat Ntuples

Please check "run_flats.sh".\
This is a simple bash script that runs multiple input flat Ntuples.\
To run,
```
$ source run_flats.sh
```

## Plotting

Please check "./plotter/cohpixsec/draw_xsecs.C".\
This macro reads the output file from the "cohpiana" analyzer.\
You can modify options in the macro
```
int N_samples = 3;
TString sample_names[] = {"GENIE_G21_11a", "GENIE_G18_01a", "GENIE_G18_02a"};
TString sample_names_for_leg[] = {"GENIE (G21_11a)", "GENIE (G18_01a)", "GENIE (G18_012)"};
Int_t color_array[] = {632, 800, 867, 600, 416, 901, 432, 400, 920};
Int_t line_sty_array[] = {1, 1, 7};

int N_vars = 7;
TString hist_names[] = {"PiCos", "MuCos", "MuPiOpenCos",
                        "PiE", "MuE",
                        "Abst", "AbstApprox",
};
TString var_names[] = {"cos#theta_{#pi^{+}}", "cos#theta_{#mu^{-}}", "cos#theta(#mu^{-}, #pi^{+})",
                       "E_{#pi^{+}}", "E_{#mu^{-}}",
                       "|t|", "|t_{Appr.}|",
};
TString var_units[] = {"", "", "",
                       "[GeV]", "[GeV]",
                       "[GeV/c]^2", "[GeV/c]^2",
};
int rebins[] = {5, 5, 5,
                5, 5,
                1, 1,
};
double x_mins[] = {0., 0., -1.,
                   0., 0.,
                   0., 0.,
};
double x_maxs[] = {1., 1., 1.,
                   3., 3.,
                   0.2, 0.2,
};
```

To run,
```
$ root -l -b -q plotter/cohpixsec/draw_xsecs.C
```
