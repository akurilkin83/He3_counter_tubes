//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "He3_counterDetectorConstruction.hh"
#include "He3_counterPrimaryGeneratorAction.hh"
#include "He3_counterRunAction.hh"
#include "He3_counterEventAction.hh"
#include "He3_counterSteppingAction.hh"
#include "He3_counterParameters.hh"
#include "AnalysisROOT.hh"
#include "QGSP_BERT_HP.hh"
//#include "QGSP_BERT.hh"
//#include "QGSP_BIC_HP.hh"
//#include "QGSP_BIC_AllHP.hh"
//#include "QGSP_BIC.hh"
//#include "QGSP_INCLXX.hh"
//#include "QGSP_INCLXX_HP.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)

{ // Choose the Random engine
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
     
  // Construct the default run manager
//#ifdef G4MULTITHREADED
  //G4MTRunManager* runManager = new G4MTRunManager;
//#else
  G4RunManager* runManager = new G4RunManager;
//#endif

// set mandatory initialization classes

  He3_counterDetectorConstruction* detector = new He3_counterDetectorConstruction();
  runManager->SetUserInitialization(detector);

//Here is where you change the PhyscisLists. This one includes all of the processes that you might be interested in
  G4VUserPhysicsList* physicsList;
  physicsList = new QGSP_BERT_HP; 
  runManager->SetUserInitialization(physicsList) ;





// ----------- analysis
  AnalysisROOT * histo =  new AnalysisROOT();

// set mandatory user action class
  He3_counterPrimaryGeneratorAction * He3_counterPrimaryGenerator = new He3_counterPrimaryGeneratorAction; 
  runManager->SetUserAction(He3_counterPrimaryGenerator);

  // set aditional user action classes
  He3_counterRunAction* He3_counterrun = new He3_counterRunAction(histo);
  runManager->SetUserAction(He3_counterrun);

  He3_counterEventAction* He3_counterevent = new He3_counterEventAction(He3_counterrun,histo);
  runManager->SetUserAction(He3_counterevent);


  runManager->SetUserAction(new He3_counterSteppingAction(detector,He3_counterevent));

  runManager->Initialize();



  G4VisManager* visManager = new G4VisExecutive;

  visManager->Initialize();



 G4UImanager* UImanager = G4UImanager::GetUIpointer();


//  runManager->BeamOn(NUMBEROFEVENTS);
 if ( ! ui ) { 
  // batch mode
  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
}

  
  delete visManager;
  delete runManager;

return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
