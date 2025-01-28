#include "cohpiana.h"

void cohpiana::initializeAnalyzer(){

  cout << "[[PionAnalyzer::initializeAnalyzer]] Sample name : " << SampleName << endl;
  //debug_mode = true;
}

void cohpiana::executeEvent(){

  count_genie_mode();
  weight = evt.fScaleFactor * evt.Weight * Units * A;
  
  std::vector<FSP> all_fsps = GetAllFSPs();
  std::vector<FSP> fsmuons = GetAllFSMuons(all_fsps, 0.1); // muons with P > 0.1 GeV/c
  std::vector<FSP> fschpions = GetAllFSChPions(all_fsps, 0.1); // ch pions with P > 0.1 GeV/c
  std::vector<FSP> fsprotons = GetAllFSProtons(all_fsps, 0.2); // protons with P > 0.2 GeV/c

  // == exactly 1 mu and 1 ch pi, no proton
  if(fsmuons.size() != 1 || fschpions.size() != 1 || fsprotons.size() > 0) return;
  set_genie_mode();
  CounterEventsPassedSelection++;

  // == 3 and 4vectors
  FSP this_mu = fsmuons.at(0);
  FSP this_pi = fschpions.at(0);
  fillcohvars(this_mu, this_pi);
}

void cohpiana::fillcohvars(FSP mu, FSP pi){

  ROOT::Math::XYZVector mu_3vec(mu.px(), mu.py(), mu.pz());
  ROOT::Math::XYZVector pi_3vec(pi.px(), pi.py(), pi.pz());

  double E_mu = mu.E();
  double E_pi = pi.E();
  double cos_theta_mu = cos(mu_3vec.Theta());
  double cos_theta_pi = cos(pi_3vec.Theta());
  double cos_open = mu_3vec.Dot(pi_3vec) / sqrt(mu_3vec.Mag2() * pi_3vec.Mag2());

  double E_nu = evt.Enu_true;
  double E_nu_approx = E_mu + E_pi;

  ROOT::Math::PxPyPzEVector mu_4vec(mu.px(), mu.py(), mu.pz(), mu.E());
  ROOT::Math::PxPyPzEVector pi_4vec(pi.px(), pi.py(), pi.pz(), pi.E());
  ROOT::Math::PxPyPzEVector nu_4vec(0., 0., E_nu, E_nu);

  double t = (nu_4vec - mu_4vec - pi_4vec).M2();
  double abst = fabs(t);
  double abst_approx = pow(mu.px() + pi.px(), 2.) + pow(mu.py() + pi.py(), 2.) + pow(E_mu + E_pi - mu.pz() - pi.pz(), 2.);

  FillHist("MuE", E_mu, weight, 1000., 0., 10.);
  FillHist("MuCos", cos_theta_mu, weight, 200., -1., 1.);
  FillHist("PiE", E_pi, weight, 1000., 0., 10.);
  FillHist("PiCos", cos_theta_pi, weight, 200., -1., 1.);
  FillHist("MuPiOpenCos", cos_open, weight, 200., -1., 1.);
  FillHist("Abst", abst, weight, 100., 0., 1.);
  FillHist("AbstApprox", abst_approx, weight, 100., 0., 1.);

  FillHist(InteractionLabels[genie_mode] + "MuE", E_mu, weight, 1000., 0., 10.);
  FillHist(InteractionLabels[genie_mode] + "MuCos", cos_theta_mu, weight, 200., -1., 1.);
  FillHist(InteractionLabels[genie_mode] + "PiE", E_pi, weight, 1000., 0., 10.);
  FillHist(InteractionLabels[genie_mode] + "PiCos", cos_theta_pi, weight, 200., -1., 1.);
  FillHist(InteractionLabels[genie_mode] + "MuPiOpenCos", cos_open, weight, 200., -1., 1.);
  FillHist(InteractionLabels[genie_mode] + "Abst", abst, weight, 100., 0., 1.);
  FillHist(InteractionLabels[genie_mode] + "AbstApprox", abst_approx, weight, 100., 0., 1.);
}

void cohpiana::count_genie_mode(){

  int this_mode = evt.Mode;
  if (TMath::Abs(this_mode) == 1) { CounterQEEvents++; } // QE
  else if (TMath::Abs(this_mode) == 2) { CounterMECEvents++; } // MEC
  else if (
           TMath::Abs(this_mode) == 10 ||
           TMath::Abs(this_mode) == 11 || TMath::Abs(this_mode) == 12 || TMath::Abs(this_mode) == 13 ||
           TMath::Abs(this_mode) == 17 || TMath::Abs(this_mode) == 22 || TMath::Abs(this_mode) == 23
           ) { CounterRESEventsPassedSelection++; genie_mode = 3; } // RES
  else if (TMath::Abs(this_mode) == 21 || TMath::Abs(this_mode) == 26) { CounterDISEvents++; } // DIS
  else if (TMath::Abs(this_mode) == 16) { CounterCOHEvents++;} // COH
  else { return; }
}


void cohpiana::set_genie_mode(){

  int this_mode = evt.Mode;
  if (TMath::Abs(this_mode) == 1) { CounterQEEventsPassedSelection++; genie_mode = 1; } // QE
  else if (TMath::Abs(this_mode) == 2) { CounterMECEventsPassedSelection++; genie_mode = 2; } // MEC
  else if (
	   TMath::Abs(this_mode) == 10 ||
	   TMath::Abs(this_mode) == 11 || TMath::Abs(this_mode) == 12 || TMath::Abs(this_mode) == 13 ||
	   TMath::Abs(this_mode) == 17 || TMath::Abs(this_mode) == 22 || TMath::Abs(this_mode) == 23
	   ) { CounterRESEventsPassedSelection++; genie_mode = 3; } // RES
  else if (TMath::Abs(this_mode) == 21 || TMath::Abs(this_mode) == 26) { CounterDISEventsPassedSelection++; genie_mode = 4; } // DIS
  else if (TMath::Abs(this_mode) == 16) { CounterCOHEventsPassedSelection++; genie_mode = 5;} // COH
  else { return; }
}

cohpiana::cohpiana(){

}

cohpiana::~cohpiana(){

}
