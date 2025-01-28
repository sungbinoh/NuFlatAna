#include "src/cohpiana.h"

void run_cohpiana(TString filename, TString samplename){
  //gSystem->Load("./lib/libNuFlatAna.so");

  //TString working_dir = getenv("PLOTTER_WORKING_DIR");

  cohpiana m;
  m.MaxEvent = -1;
  m.LogEvery = 1000;
  m.SampleName = samplename;
  m.SetTreeName();
  m.AddFile("./input/" + filename);
  m.SetOutfilePath("./output/root/hists_" + samplename + ".root");
  m.Init();
  m.initializeAnalyzer();
  m.SwitchToTempDir();
  m.Loop();
  m.WriteHist();
}

int main(int argc, char* argv[]) {
  TString filename = argv[1];
  TString samplename = argv[2];
  run_cohpiana(filename, samplename);
  return 0;
}

