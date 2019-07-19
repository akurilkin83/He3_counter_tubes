// akurilkin 2019 
// according to AnaEx02 HistoManager.


/*******************************************************************************
 * This is a singleton class which takes care of the analysis tasks.
 *
 * - It needs access to ROOT headers.
 * - It should be instantiated within RunAction constructor (or similar),
 *   the geometrical (such as SDs, dimensions...) information must be
 *   obtained during BeginOfRunAction() or similar,
 *   histograms updated within a SD::EndOfEventAction() method or similar,
 *   and normalized, closed, etc. in the EndOfRunAction() method.
 * - It should be deleted within RunAction destructor.
 *
 * Created on 2014-08-06, M. A. Cortes-Giraldo (Univ. Sevilla)
 * Cleaned and simplified 2017-02-06 , J. Lerendegui-Marco ("")
 *******************************************************************************
 */


#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TTree.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include "G4UnitsTable.hh"


#include "AnalysisROOT.hh"
#include "He3_counterParameters.hh"

#include "Randomize.hh"

#include <sstream>
#include <iomanip>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
std::ostringstream out;
out << std::setprecision(n) << a_value;
return out.str();
}

// -----------------------------------------------------
AnalysisROOT::AnalysisROOT() // AnalysisROOT inicialization
:fRootFile(0),fNtuple1(0),
//fNtuple2(0),
xpos(0),ypos(0),zpos(0),Energy(0),
TotalSLP(0), MeanSLP(0), TotalSLT(0), MeanSLT(0),EventNr(0),
unitP(0),unitE(0),
vertex_x(0),vertex_y(0),vertex_z(0),energy_n(0)
{


  // histograms
  for (G4int k=0; k<kMaxHisto; k++) fHisto[k] = 0;
  // ntuple
  fNtuple1 = 0;
//  fNtuple2 = 0;

  unitP = CLHEP::mm;
  unitE = CLHEP::keV;  ///   ?
//  unitE = eV; 
}


// ----------------------------------------------------



// ----------------------------------------------------

AnalysisROOT::~AnalysisROOT()
{
  G4cout << "Destructor of AnalysisROOT ..." << G4endl;
 if (fRootFile) delete fRootFile;

}

// ----------------------------------------------------




// ----------------------------------------------------
void AnalysisROOT::Book()
{
// Creating a tree container to handle histograms and ntuples.
// This tree is associated to an output file.
//

  std::setprecision(1);

  G4String fileName = "../results/He3_counter_";
  fileName = fileName + "D_"+to_string_with_precision((RAD*2+0.04),2) + "_pHe3_" +to_string_with_precision(pHe3,2) +"_"
  + "pAr_" +to_string_with_precision(pAr,2) +"_"+ "pCO2_" +to_string_with_precision(pCO2,2) +"_"+ "pCF4_" +to_string_with_precision(pCF4,2)+".root";

  fRootFile = new TFile(fileName,"RECREATE");

  if (! fRootFile)
   {
    G4cout << " HistoManager::Book :" 
           << " problem creating the ROOT TFile "
           << G4endl;
    return;
  }


  // id = 0
//  fHisto[0] = new TH1D("EDep_3H", "Edep in absorber for 3H (keV)", 400, 0., 1000*CLHEP::keV);
  // id = 1
//  fHisto[1] = new TH1D("EDep_p", "Edep in absorber for proton (keV)", 400, 0., 1000*CLHEP::keV);
/*
  // id = 0
  fHisto[0] = new TH1D("EDep_total", "Edep in absorber : total (keV)", 2000, 0., 1000);
  // id = 1
  fHisto[1] = new TH1D("LTrack_3H", "trackL in absorber : 3H (mm)", 5000000, 0., 50);
  // id = 2
  fHisto[2] = new TH1D("LTrack_proton", "trackL in absorber : proton (mm)", 5000000, 0., 50);
  // id = 3
  fHisto[3] = new TH1D("LTrack_sum", "trackL in absorber : proton + 3H (mm)", 5000000, 0., 50);
  // id = 4
  fHisto[4] = new TH1D("Ebeam_n", "initial neutron energy (eV)", 200, 0., 0.2);
*/

  // id = 0
  fHisto[0] = new TH1D("EDep_total", "Edep in absorber : total (keV)", 2000, 0., 1000);
  fHisto[0]->GetXaxis()->SetTitle("Edep, keV");
  fHisto[0]->GetYaxis()->SetTitle("Counts");
  // id = 1
  fHisto[1] = new TH1D("LTrack_3H", "trackL in absorber : 3H (mm)", 5000, 0., 50);
  fHisto[1]->GetXaxis()->SetTitle("track length, mm");
  fHisto[1]->GetYaxis()->SetTitle("Counts");
  // id = 2
  fHisto[2] = new TH1D("LTrack_proton", "trackL in absorber : proton (mm)", 5000, 0., 50);
  fHisto[2]->GetXaxis()->SetTitle("track length, mm");
  fHisto[2]->GetYaxis()->SetTitle("Counts");
  // id = 3
  fHisto[3] = new TH1D("LTrack_sum", "trackL in absorber : proton + 3H (mm)", 5000, 0., 50);
  fHisto[3]->GetXaxis()->SetTitle("track length, mm");
  fHisto[3]->GetYaxis()->SetTitle("Counts");
  // id = 4
  fHisto[4] = new TH1D("Ebeam_n", "initial neutron energy (eV)", 200, 0., 0.2);
  fHisto[4]->GetXaxis()->SetTitle("En, eV");
  fHisto[4]->GetYaxis()->SetTitle("Counts");

  // id = 5
  fHisto2D[0] = new TH2D("z_y", "reaction coordinates", 200, -10., 30., 200,-20,20.);
  fHisto2D[0]->GetXaxis()->SetTitle("Z coordinate, mm");
  fHisto2D[0]->GetYaxis()->SetTitle("Y coordinate, mm");

  // id = 5
  fHisto2D[1] = new TH2D("x_y", "reaction coordinates", 200, -20., 20., 200,-20,20.);
  fHisto2D[1]->GetXaxis()->SetTitle("X coordinate, mm");
  fHisto2D[1]->GetYaxis()->SetTitle("Y coordinate, mm");



  for ( G4int i=0; i<kMaxHisto; ++i ) {
    if (! fHisto[i]) G4cout << "\n can't create histo " << i << G4endl;
  }  


  // create the ntuple to store value of variables 

  fNtuple1 = new TTree("Ntuple1","T_Var");

/// Define branches ////

 fNtuple1->Branch("EventNr",&EventNr,"EventNr/I");
 fNtuple1->Branch("Energy",&Energy,"Energy/D");
 fNtuple1->Branch("xpos",&xpos,"xpos/D");
 fNtuple1->Branch("ypos",&ypos,"ypos/D");
 fNtuple1->Branch("zpos",&zpos,"zpos/D");
 fNtuple1->Branch("TotalSLP",&TotalSLP,"TotalSLP/D");
 fNtuple1->Branch("MeanSLP",&MeanSLP,"MeanSLP/D");
 fNtuple1->Branch("TotalSLT",&TotalSLT,"TotalSLT/D");
 fNtuple1->Branch("MeanSLT",&MeanSLT,"MeanSLT/D");

 fNtuple1->Branch("vertex_x",&vertex_x,"vertex_x/D");
 fNtuple1->Branch("vertex_y",&vertex_y,"vertex_y/D");
 fNtuple1->Branch("vertex_z",&vertex_z,"vertex_z/D");
 fNtuple1->Branch("energy_n",&energy_n,"energy_n/D");

 G4cout << "\n----> Output file is open in " << fileName << G4endl;
}
// ----------------------------------------------------



// ----------------------------------------------------
void AnalysisROOT::Save()
{ 
  if (!fRootFile) return;
  
  fRootFile->Write();       // Writing the histograms to the file
  fRootFile->Close();       // and closing the tree (and the file)
  
  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
}

// ----------------------------------------------------

//  normalization is not needed in present analysis
void AnalysisROOT::Normalize(G4int ih, G4double fac)
{
  if (ih >= kMaxHisto) {
    G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
           << " does not exist. (fac=" << fac << ")" << G4endl;
    return;
  }
  if (fHisto[ih]) fHisto[ih]->Scale(fac);
}
// ----------------------------------------------------


// ----------------------------------------------------
void AnalysisROOT::FillNtuple(G4int EvNr,G4double EN,G4double Xpos,G4double Ypos, G4double Zpos, G4double TotalSLProton, G4double MeanSLProton, G4double TotalSLTriton, G4double MeanSLTriton,
                             G4double Vertex_x,G4double Vertex_y,G4double Vertex_z,G4double Energy_n)  // This is invoked at EndOfEventAction() method
{
//  Energy = G4RandGauss::shoot(EN/unitE,0.003*EN/unitE);  // parameters according to He-18/200-8.0 haracteristic
  Energy = G4RandGauss::shoot(EN/unitE,0.035*EN/unitE);  // sigma in Gauss = FWHM/2  ; 0.035 correspond to the 7% resolution
  //Energy = EN/unitE;
  xpos = Xpos/unitP;
  ypos = Ypos/unitP;
  zpos = Zpos/unitP;
  EventNr= EvNr;
  TotalSLP = TotalSLProton/unitP;
  MeanSLP = MeanSLProton/unitP;
  TotalSLT = TotalSLTriton/unitP;
  MeanSLT = MeanSLTriton/unitP;
  vertex_x = Vertex_x/unitP;
  vertex_y = Vertex_y/unitP;
  vertex_z = Vertex_z/unitP;
  energy_n = Energy_n/unitE;

  // fill the ntuple
  if (fNtuple1) fNtuple1->Fill();

}
// ----------------------------------------------------

//void AnalysisROOT::FillHisto(G4double Energy,G4double MeanSLProton, G4double MeanSLTriton,G4double Energy_n)
void AnalysisROOT::FillHisto(G4double Energy,G4double MeanSLProton, G4double MeanSLTriton, G4double Xpos, G4double Ypos,G4double Zpos, G4double Energy_n)
{
Energy = G4RandGauss::shoot(Energy/unitE,0.035*Energy/unitE);  // sigma in Gauss = FWHM/2  ; 0.035 correspond to the 7% resolution
MeanSLP = MeanSLProton/unitP;
MeanSLT = MeanSLTriton/unitP;
energy_n = Energy_n/unitE;
xpos = Xpos/unitP;
ypos = Ypos/unitP;
zpos = Zpos/unitP;


fHisto[0]->Fill(Energy);
fHisto[1]->Fill(MeanSLT);
fHisto[2]->Fill(MeanSLP);
fHisto[3]->Fill(MeanSLT+MeanSLP);
fHisto[4]->Fill(energy_n);
fHisto2D[0]->Fill(zpos,ypos);
fHisto2D[1]->Fill(xpos,ypos);
}



// ----------------------------------------------------
void AnalysisROOT::PrintStatistic()
{
  G4cout << "\n ----> print histograms statistic \n" << G4endl;
  for ( G4int i=0; i<kMaxHisto; ++i ) {
    TH1D* h1 = fHisto[i];
    const G4String name = h1->GetName();  

    G4String unitCategory;
    if (name[0] == 'E' ) unitCategory = "Energy"; 
    if (name[0] == 'L' ) unitCategory = "Length";

    G4cout << name
           << ": mean = " << G4BestUnit(h1->GetMean(), unitCategory) 
           << " rms = " << G4BestUnit(h1->GetRMS(), unitCategory ) 
           << G4endl;
  }
}
// ----------------------------------------------------







