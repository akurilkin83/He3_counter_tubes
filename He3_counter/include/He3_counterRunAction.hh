//////////////////////////////////////////////////////////
//							//
//		 He3_counter G4 application		//
//			akurilkin 2019			//
//							//
//////////////////////////////////////////////////////////

#ifndef He3_counterRunAction_h
#define He3_counterRunAction_h 1


#include "He3_counterParameters.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"



class G4Run;
class AnalysisROOT;




class He3_counterRunAction : public G4UserRunAction
{
  public:
  He3_counterRunAction(AnalysisROOT*);
  virtual ~He3_counterRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
  
  
//  void FillPerEvent();

//    void printPosition(G4double X0, G4double Y0, G4double Z0);
//    void PrintEnergy(G4double E);
//    void PrintSL (G4double TotalSLP, G4double MeanSLP, G4double TotalSLT, G4double MeanSLT);

  private:
  AnalysisROOT* fAnalysisROOT;
};

#endif



