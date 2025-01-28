#include "FSP.h"

FSP::FSP(){

  j_IsEmpty = true;
  j_pdg = -9999;
  j_px = -9999;
  j_py = -9999;
  j_pz = -9999;
  j_p = -9999;
  j_E = -9999;
  j_M = -9999;
}

FSP::~FSP(){}

void FSP::Set_IsEmpty(bool i_IsEmpty){ j_IsEmpty = i_IsEmpty; }
void FSP::Set_pdg(int i_pdg){ j_pdg = i_pdg; }
void FSP::Set_px(double i_px){ j_px = i_px; }
void FSP::Set_py(double i_py){ j_py = i_py; }
void FSP::Set_pz(double i_pz){ j_pz = i_pz; }
void FSP::Set_p(double i_p){ j_p = i_p; }
void FSP::Set_E(double i_E){ j_E = i_E; }
void FSP::Set_M(double i_M){ j_M = i_M; }
