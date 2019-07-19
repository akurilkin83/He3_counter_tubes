// akurilkin 2019: Created.
// test counter, by using AnaEx02 example.



#ifndef AnalysisROOT_hh
#define AnalysisROOT_hh 1

/*******************************************************************************
 * This is a singleton class which takes care of the analysis histogram tasks.
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
 *
 *******************************************************************************
 */


#include "globals.hh"


//#include "G4ThreeVector.hh"
//#include <fstream>
//#include <map>
//#include <vector>

class TFile;
class TH1D;
class TH2D;
class TH3D;
class TRandom;
class TTree;

class G4Event;
class G4Run;


const G4int kMaxHisto = 5;
const G4int kMaxHisto2D = 2;



//class AnalysisROOTMessenger;

class AnalysisROOT
{
public:
AnalysisROOT();
~AnalysisROOT();


void Book();
void Save();


//void FillHisto(G4int id, G4double bin, G4double weight = 1.0);

void FillHisto(G4double Energy,G4double MeanSLProton, G4double MeanSLTriton, G4double Xpos, G4double Ypos,G4double Zpos, G4double Energy_n);


void FillNtuple(G4int EvNr,G4double EN,G4double Xpos, G4double Ypos, G4double Zpos, G4double TotalSLProton, G4double MeanSLProton, G4double TotalSLTriton, G4double MeanSLTriton,
                 G4double Vertex_x, G4double Vertex_y, G4double Vertex_z, G4double Energy_n);


void Normalize(G4int id,G4double fac);

void PrintStatistic();


private: // DATA MEMBERS


  // The ROOT file
  TFile* fRootFile;

  TH1D* fHisto[kMaxHisto];
  TH2D* fHisto2D[kMaxHisto2D];
  TTree* fNtuple1;
//  TTree* fNtuple2;


  G4double xpos, ypos, zpos, Energy;
  G4double TotalSLP, MeanSLP, TotalSLT, MeanSLT;
  G4int EventNr;
  G4double unitP;
  G4double unitE;
  G4double vertex_x, vertex_y, vertex_z, energy_n;

};

#endif

