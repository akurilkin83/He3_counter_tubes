#include "He3_counterRunAction.hh"
#include "AnalysisROOT.hh"
#include "He3_counterParameters.hh"


#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//#include <math.h>
//#include <fstream> 
//#include "G4ios.hh"
//#include "iomanip"
//#include <iostream> 
//#include <sstream> 
//#include <stdio.h>




using namespace std;

He3_counterRunAction::He3_counterRunAction(AnalysisROOT * histo)
: G4UserRunAction(),
  fAnalysisROOT(histo)
{ 
}

He3_counterRunAction::~He3_counterRunAction()
{ 
}


void He3_counterRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
 G4cout<< "### Run "<<aRun->GetRunID() << "  start."<< G4endl;

// histograms
 fAnalysisROOT->Book();
}




void He3_counterRunAction::EndOfRunAction(const G4Run* aRun)
{ 

  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;

  //save histograms
  //
  fAnalysisROOT->PrintStatistic();
  fAnalysisROOT->Save();   

} 


