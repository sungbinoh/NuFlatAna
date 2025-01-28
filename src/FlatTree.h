#ifndef FlatTree_h
#define FlatTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

class FlatTree {

public :

   FlatTree();
   virtual ~FlatTree();

   virtual void Init_FlatTree(TChain *ch);

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Mode;
   Char_t          cc;
   Int_t           PDGnu;
   Float_t         Enu_true;
   Int_t           tgt;
   Int_t           tgta;
   Int_t           tgtz;
   Int_t           PDGLep;
   Float_t         ELep;
   Float_t         CosLep;
   Int_t           nfsp;
   Float_t         px[100];   //[nfsp]
   Float_t         py[100];   //[nfsp]
   Float_t         pz[100];   //[nfsp]
   Float_t         E[100];   //[nfsp]
   Int_t           pdg[100];   //[nfsp]
   Float_t         px_init[10];   //[ninitp]
   Float_t         py_init[10];   //[ninitp]
   Float_t         pz_init[10];   //[ninitp]
   Float_t         E_init[10];   //[ninitp]
   Int_t           pdg_init[10];   //[ninitp]
   Int_t           nvertp;
   Float_t         px_vert[100];   //[nvertp]
   Float_t         py_vert[100];   //[nvertp]
   Float_t         pz_vert[100];   //[nvertp]
   Float_t         E_vert[100];   //[nvertp]
   Int_t           pdg_vert[100];   //[nvertp]
   Float_t         Weight;
   Double_t        fScaleFactor;

   // List of branches
   TBranch        *b_Mode;   //!
   TBranch        *b_cc;   //!
   TBranch        *b_PDGnu;   //!
   TBranch        *b_Enu_true;   //!
   TBranch        *b_tgt;   //!
   TBranch        *b_tgta;   //!
   TBranch        *b_tgtz;   //!
   TBranch        *b_PDGLep;   //!
   TBranch        *b_ELep;   //!
   TBranch        *b_CosLep;   //!
   TBranch        *b_nfsp;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_E;   //!
   TBranch        *b_pdg;   //!
   TBranch        *b_ninitp;   //!
   TBranch        *b_px_init;   //!
   TBranch        *b_py_init;   //!
   TBranch        *b_pz_init;   //!
   TBranch        *b_E_init;   //!
   TBranch        *b_pdg_init;   //!
   TBranch        *b_nvertp;   //!
   TBranch        *b_px_vert;   //!
   TBranch        *b_py_vert;   //!
   TBranch        *b_pz_vert;   //!
   TBranch        *b_E_vert;   //!
   TBranch        *b_pdg_vert;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_fScaleFactor;   //!

};

#endif
