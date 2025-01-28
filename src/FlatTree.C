#define FlatTree_cxx
#include "FlatTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

FlatTree::FlatTree(){
}

FlatTree::~FlatTree(){
}

void FlatTree::Init_FlatTree(TChain *ch)
{
   ch->SetMakeClass(0);

   ch->SetBranchAddress("Mode", &Mode, &b_Mode);
   ch->SetBranchAddress("cc", &cc, &b_cc);
   ch->SetBranchAddress("PDGnu", &PDGnu, &b_PDGnu);
   ch->SetBranchAddress("Enu_true", &Enu_true, &b_Enu_true);
   ch->SetBranchAddress("tgt", &tgt, &b_tgt);
   ch->SetBranchAddress("tgta", &tgta, &b_tgta);
   ch->SetBranchAddress("tgtz", &tgtz, &b_tgtz);
   ch->SetBranchAddress("PDGLep", &PDGLep, &b_PDGLep);
   ch->SetBranchAddress("ELep", &ELep, &b_ELep);
   ch->SetBranchAddress("CosLep", &CosLep, &b_CosLep);
   ch->SetBranchAddress("nfsp", &nfsp, &b_nfsp);
   ch->SetBranchAddress("px", px, &b_px);
   ch->SetBranchAddress("py", py, &b_py);
   ch->SetBranchAddress("pz", pz, &b_pz);
   ch->SetBranchAddress("E", E, &b_E);
   ch->SetBranchAddress("pdg", pdg, &b_pdg);
   ch->SetBranchAddress("px_init", px_init, &b_px_init);
   ch->SetBranchAddress("py_init", py_init, &b_py_init);
   ch->SetBranchAddress("pz_init", pz_init, &b_pz_init);
   ch->SetBranchAddress("E_init", E_init, &b_E_init);
   ch->SetBranchAddress("pdg_init", pdg_init, &b_pdg_init);
   ch->SetBranchAddress("nvertp", &nvertp, &b_nvertp);
   ch->SetBranchAddress("px_vert", px_vert, &b_px_vert);
   ch->SetBranchAddress("py_vert", py_vert, &b_py_vert);
   ch->SetBranchAddress("pz_vert", pz_vert, &b_pz_vert);
   ch->SetBranchAddress("E_vert", E_vert, &b_E_vert);
   ch->SetBranchAddress("pdg_vert", pdg_vert, &b_pdg_vert);
   ch->SetBranchAddress("Weight", &Weight, &b_Weight);
   ch->SetBranchAddress("fScaleFactor", &fScaleFactor, &b_fScaleFactor);
}

