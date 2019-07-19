#include "He3_counterEventAction.hh"
#include "He3_counterRunAction.hh"
#include "AnalysisROOT.hh"
#include "He3_counterParameters.hh"

//#include <CLHEP/Units/SystemOfUnits.h>

#include "G4SystemOfUnits.hh"
#include "G4Event.hh"

//#include "G4UnitsTable.hh"
//#include "globals.hh"



He3_counterEventAction::He3_counterEventAction(He3_counterRunAction* runAct,AnalysisROOT *histo)
:G4UserEventAction(),
fRunAction(runAct),fAnalysisROOT(histo)
{}

He3_counterEventAction::~He3_counterEventAction()
{}

void He3_counterEventAction::BeginOfEventAction(const G4Event* evt) //Start of each event
{ 


// Initializing variables at the begin of each event
x0 = -1000.;
y0 = -1000;
z0 = -1000;
TotalEnergyDeposit = 0.;
TotalSLProton = 0;
TotalSLTriton = 0;
MeanSLProton = 0;
MeanSLTriton = 0;

G4int Eventnr=evt->GetEventID();

vertex_x = evt->GetPrimaryVertex()->GetX0();
vertex_y = evt->GetPrimaryVertex()->GetY0();
vertex_z = evt->GetPrimaryVertex()->GetZ0();
energy_n = evt->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();
energy_n = energy_n *1000.0 ;


G4cout<<" Event "<<Eventnr<<G4endl; // Print event ID
//G4cout<<" vertex_x  "<<vertex_x<<G4endl; // Print event ID
//G4cout<<" vertex_y "<<vertex_y<<G4endl; // Print event ID
//G4cout<<" vertex_z "<<vertex_z<<G4endl; // Print event ID
//G4cout<<" energy_n "<<energy_n<<G4endl; // Print event ID
}

//End of each event (NOTICE the variables used are declared in He3_counterEventAction.cc and filled at the bottom of this class in the FUNCTIONS section
void He3_counterEventAction::EndOfEventAction(const G4Event* evt) 
{

//runAct->PrintEnergy(TotalEnergyDeposit); // For each event, at the end of it, send the total energy deposited by all of the particles inside the detector to run action (in order to print it to a file). You only need to do this if you are going to creat a .txt file or similar. For printing in a root file see below.

MeanSLProton = pow( pow(xPi-xPf,2) + pow(yPi-yPf,2) + pow(zPi-zPf,2), 0.5); // Calculate mean step length for proton, i.e ((xf-xi)^2 + (yf-yi)^2 + (zf-zi)^2)^1/2
MeanSLTriton = pow( pow(xTi-xTf,2) + pow(yTi-yTf,2) + pow(zTi-zTf,2), 0.5); // same for triton

if (x0!=-1000 || y0!=-1000 || z0!=-1000)  // if reaction n+3He was 
{
  G4int Eventnr=evt->GetEventID(); // Get event ID
  //runAct->printPosition(x0,y0,z0); // This is to print to a file in run action
  fAnalysisROOT->FillNtuple(Eventnr,TotalEnergyDeposit,x0,y0,z0,TotalSLProton,MeanSLProton,TotalSLTriton,MeanSLTriton,vertex_x,vertex_y,vertex_z,energy_n); // Filling a tree (ROOT), see AnalysisROOT.cc

  if(TotalEnergyDeposit>0.){ 
  fAnalysisROOT->FillHisto(TotalEnergyDeposit,MeanSLTriton,MeanSLProton,x0,y0,z0,energy_n);
  }
}
// akurilkin
else{  // if reaction was not, z0= -200 it is need to eff calculation
  G4int Eventnr=evt->GetEventID(); // Get event ID
//  z0=-200;
  //runAct->printPosition(x0,y0,z0); // This is to print to a file in run action
  MeanSLProton = 0;
  MeanSLTriton = 0;
  TotalSLProton = 0;
  TotalSLTriton = 0;
  TotalEnergyDeposit=0;
  fAnalysisROOT->FillNtuple(Eventnr,TotalEnergyDeposit,x0,y0,z0,TotalSLProton,MeanSLProton,TotalSLTriton,MeanSLTriton,vertex_x,vertex_y,vertex_z,energy_n); // Filling a tree (ROOT), see AnalysisROOT.cc
}

}


// ------------------------------------------------------- FUNCTIONS -------------------------------------------------------------------------------------------//
// NOTICE that some variables are called differently (compared to He3_counterSteppingAction.cc) in order to avoid redefinitions, for example: Edep is now EdepStep.

void He3_counterEventAction::GetCreationPosition(G4double x_0,G4double y_0,G4double z_0) // Get reaction position (is the same as the creation position for protons and tritons)
{
  x0=x_0;
  y0=y_0;
  z0=z_0-POSITION*mm;
}




void He3_counterEventAction::AddEdepInStep(G4double Edep) // Adding the energy in each step
{
TotalEnergyDeposit+=Edep;
}



// Functions for protons
void He3_counterEventAction::AddStepLengthProton(G4double StepLengthProton)
{
TotalSLProton += StepLengthProton; // Adding the proton step length in each step
}
void He3_counterEventAction::GetCreationPositionP(G4double xp_i, G4double yp_i, G4double zp_i)
{
xPi = xp_i; yPi = yp_i; zPi = zp_i; // Getting the proton creation position
}
void He3_counterEventAction::GetAbsorptionPositionP(G4double xp_f, G4double yp_f, G4double zp_f)
{
xPf = xp_f; yPf = yp_f; zPf = zp_f;// Getting the proton absorption position
}


// Functions for tritons (same as for protons)
void He3_counterEventAction::AddStepLengthTriton(G4double StepLengthTriton)
{
TotalSLTriton += StepLengthTriton;
}
void He3_counterEventAction::GetCreationPositionT(G4double xt_i, G4double yt_i, G4double zt_i)
{
xTi = xt_i; yTi = yt_i; zTi = zt_i;
}
void He3_counterEventAction::GetAbsorptionPositionT(G4double xt_f, G4double yt_f, G4double zt_f)
{
xTf = xt_f; yTf = yt_f; zTf = zt_f;
}



