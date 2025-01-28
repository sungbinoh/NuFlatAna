#ifndef FSP_h
#define FSP_h

#include <string>
#include <vector>

using namespace std;

class FSP{
public:

  FSP();
  virtual ~FSP();

  // == Empty
  void Set_IsEmpty(bool i_IsEmpty);
  inline bool IsEmpty() const { return j_IsEmpty; }

  // == Variables
  void Set_pdg(int i_pdg);
  void Set_px(double i_px);
  void Set_py(double i_py);
  void Set_pz(double i_pz);
  void Set_p(double i_p);
  void Set_E(double i_E);
  void Set_M(double i_M);

  inline int pdg() const { return j_pdg; }
  inline double	px() const { return j_px; }
  inline double py() const { return j_py; }
  inline double pz() const { return j_pz; }
  inline double p() const { return j_p; }
  inline double E() const { return j_E; }
  inline double M() const { return j_M; }
  
private:
  bool j_IsEmpty;
  int j_pdg;
  double j_px;
  double j_py;
  double j_pz;
  double j_p;
  double j_E;
  double j_M;
};

#endif
