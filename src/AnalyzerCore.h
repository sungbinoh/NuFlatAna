#ifndef AnalyzerCore_h
#define AnalyzerCore_h

#include "Math/Vector4D.h"
#include "Math/Vector3D.h"
#include "TString.h"
#include "TMath.h"
#include "TH3.h"
#include "TH2D.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include <sstream>
#include "TRandom.h"
#include "TProfile.h"
#include "TRandom3.h"
#include "TFitResult.h"

#include "FlatTree.h"
#include "FSP.h"

// == particle masses in GeV
#define M_mu 105.65837e-03
#define M_neutron 939.565e-03
#define M_proton 938.272e-03
#define M_pion 139.570e-03
#define M_Kaon 493.677e-03
#define M_e 0.510998e-03
#define M_pizero 134.976e-03

using namespace std;

class AnalyzerCore {

 public:
  AnalyzerCore();
  virtual ~AnalyzerCore();

  double Units = 1E39; // so that the extracted cross-section is in 10^{-39} cm^{2}
  double A = 40.; // so that we can have xsecs per nucleus
  
  FlatTree evt;
  Long64_t MaxEvent, NSkipEvent;
  int LogEvery;
  TString SampleName;
  vector<TString> Userflags;

  bool debug_mode = false;

  virtual void initializeAnalyzer(){

  };

  virtual void executeEvent(){

  };

  //==================
  // Read Tree
  //==================
  virtual void SetTreeName(){
    TString tname = "FlatTree_VARS";
    fChain = new TChain(tname);
  }

  virtual void AddFile(TString filename){
    fChain->Add(filename);
  }

  Int_t GetEntry(Long64_t entry);

  TChain *fChain;

  void Init();
  int CounterEvents = 0;
  int CounterQEEvents = 0;
  int CounterMECEvents = 0;
  int CounterRESEvents = 0;
  int CounterDISEvents = 0;
  int CounterCOHEvents = 0;
  
  int CounterEventsPassedSelection = 0;
  int CounterQEEventsPassedSelection = 0;
  int CounterMECEventsPassedSelection = 0;
  int CounterRESEventsPassedSelection = 0;
  int CounterDISEventsPassedSelection = 0;
  int CounterCOHEventsPassedSelection = 0;
  
  void Init_evt();
  int genie_mode = -1;
  double weight = -1.;
  
  std::string printcurrunttime(){

    std::stringstream out;
    TDatime datime;
    out << datime.GetYear()<<"-"<<AddZeroToTime(datime.GetMonth())<<"-"<<AddZeroToTime(datime.GetDay())<<" "<<AddZeroToTime(datime.GetHour())<<":"<<AddZeroToTime(datime.GetMinute())<<":"<<AddZeroToTime(datime.GetSecond());
    return out.str();

  }

  std::string AddZeroToTime(int twodigit){
    if(twodigit<10){
      return "0"+std::to_string(twodigit);
    }
    else{
      return std::to_string(twodigit);
    }
  }

  void Loop();

  //==================
  // Get Particles
  //================== 
  //Event GetEvent();
  std::vector<FSP> GetAllFSPs();
  std::vector<FSP> GetAllFSMuons(const vector<FSP>& in, double P_cut = 0.1);
  std::vector<FSP> GetAllFSChPions(const vector<FSP>& in, double P_cut = 0.1);
  std::vector<FSP> GetAllFSProtons(const vector<FSP>& in, double P_cut = 0.2);
    
  //================== 
  // Plotting
  //================== 
  std::map< TString, TH1D* > maphist_TH1D;
  std::map< TString, TH2D* > maphist_TH2D;
  std::map< TString, TH3D* > maphist_TH3D;

  TH1D* GetHist1D(TString histname);
  TH2D* GetHist2D(TString histname);
  TH3D* GetHist3D(TString histname);

  void FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  void FillHist(TString histname, double value, double weight, int n_bin, const double *xbins);
  void FillHist(TString histname,
                double value_x, double value_y,
                double weight,
                int n_binx, double x_min, double x_max,
                int n_biny, double y_min, double y_max);
  void FillHist(TString histname,
                double value_x, double value_y,
                double weight,
                int n_binx, double *xbins,
                int n_biny, double *ybins);
  void FillHist(TString histname,
                double value_x, double value_y, double value_z,
                double weight,
                int n_binx, double x_min, double x_max,
                int n_biny, double y_min, double y_max,
                int n_binz, double z_min, double z_max);
  void FillHist(TString histname,
                double value_x, double value_y, double value_z,
                double weight,
                int n_binx, double *xbins,
                int n_biny, double *ybins,
                int n_binz, double *zbins);
  //==== JSFillHist : 1D
  std::map< TString, std::map<TString, TH1D*> > JSmaphist_TH1D;
  TH1D* JSGetHist1D(TString suffix, TString histname);
  void JSFillHist(TString suffix, TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  void JSFillHist(TString suffix, TString histname, double value, double weight, int n_bin, const double *xbins);

  //==== JSFillHist : 2D
  std::map< TString, std::map<TString, TH2D*> > JSmaphist_TH2D;
  TH2D* JSGetHist2D(TString suffix, TString histname);
  void JSFillHist(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx, double x_min, double x_max,
                  int n_biny, double y_min, double y_max);
  void JSFillHist(TString suffix, TString histname,
                  double value_x, double value_y,
                  double weight,
                  int n_binx, double *xbins,
                  int n_biny, double *ybins);

  virtual void WriteHist();

  //==== Output rootfile;
  void SwitchToTempDir();
  TFile *outfile;
  TTree *fEventTree = nullptr;
  void SetOutfilePath(TString outname);
  
};

#endif
