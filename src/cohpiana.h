#ifndef cohpiana_h
#define cohpiana_h

#include "AnalyzerCore.h"

class cohpiana : public AnalyzerCore {

 public:

  void initializeAnalyzer();
  void executeEvent();
  void fillcohvars(FSP mu, FSP pi);

  void count_genie_mode();
  void set_genie_mode();
  int NInte = 6;
  std::vector<TString> InteractionLabels = {"","QE","MEC","RES","DIS","COH"};

  cohpiana();
  ~cohpiana();
};

#endif
