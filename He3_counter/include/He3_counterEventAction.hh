//////////////////////////////////////////////////////////
//							//
//			akurilkin 2019			//
//							//
//////////////////////////////////////////////////////////

#ifndef He3_counterEventAction_h
#define He3_counterEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

//class G4Event;

class He3_counterRunAction;
class AnalysisROOT;



class He3_counterEventAction : public G4UserEventAction
{
public:
  He3_counterEventAction(He3_counterRunAction*,AnalysisROOT*);
  virtual ~He3_counterEventAction();




  G4double x0;
  G4double y0;
  G4double z0;
  G4double xPi,yPi,zPi,xPf,yPf,zPf; // xPi = Initial x coordinate for Proton ; xPf = Final x coordinate for Proton
  G4double xTi,yTi,zTi,xTf,yTf,zTf; // xTi = Initial x coordinate for Triton ; xTf = Final x coordinate for Triton
  G4double TotalSLProton; // Total Step Length Proton
  G4double TotalSLTriton; // Total Step Length Triton
  G4double MeanSLProton; // Mean Step Length Proton (it is going to be calculated using the initial creation position and the final, i.e. |creationPositionP - absorptionPositionP|)
  G4double MeanSLTriton; // Mean Step Length Triton (it is going to be calculated using the initial creation position and the final, i.e. |creationPositionT - absorptionPositionT|)
  G4double vertex_x, vertex_y, vertex_z, energy_n;

    
public://Declaration of functions (explanition to be seen in He3_counterEventAction.cc)
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

  void GetCreationPosition(G4double x_0, G4double y_0, G4double z_0); 
  void AddEdepInStep(G4double Edep);
  void AddStepLengthProton(G4double StepLengthProton);
  void AddStepLengthTriton(G4double StepLengthTriton);
  void GetCreationPositionP(G4double xp_i, G4double yp_i, G4double zp_i);
  void GetCreationPositionT(G4double xt_i, G4double yt_i, G4double zt_i);
  void GetAbsorptionPositionP(G4double xp_f, G4double yp_f, G4double zp_f);
  void GetAbsorptionPositionT(G4double xt_f, G4double yt_f, G4double zt_f);

private:
  He3_counterRunAction*     fRunAction;
  AnalysisROOT * fAnalysisROOT;
  G4double TotalEnergyDeposit;
  G4int fPrintModulo;
};

#endif
