//////////////////////////////////////////////////////////
//							//
//		 He3_counter G4 application		//
//		     akurilkin 2019 			//
// 		          JINR         			//
//							//
//////////////////////////////////////////////////////////


#include "He3_counterSteppingAction.hh"
#include "He3_counterEventAction.hh"
#include "He3_counterDetectorConstruction.hh"

#include "G4Step.hh"


//#include "G4SteppingManager.hh"
//#include "G4Track.hh"
//#include "G4LogicalVolume.hh"
//#include <fstream> 
//#include <G4SmoothTrajectory.hh>
//#include "He3_counterParameters.hh"
//#include <G4UnitsTable.hh>
//#include "G4ios.hh"
//#include "G4SystemOfUnits.hh"
//#include  "G4TrackStatus.hh"
 
He3_counterSteppingAction::He3_counterSteppingAction(He3_counterDetectorConstruction *detector,
He3_counterEventAction* EvAct) 
:G4UserSteppingAction(),
fDetectorConstruction(detector),fEventAction(EvAct)
{ }

He3_counterSteppingAction::~He3_counterSteppingAction()
{ }
// --------------------------


//------------------
// This function will be runned before every step of every particle 
void He3_counterSteppingAction::UserSteppingAction(const G4Step* aStep) // we define pointer to class G4Step
{
// Initializing variables at every step
sLengthProton = 0.;
sLengthTriton = 0.;
EdepStep = 0.;
//	pr_neutron=0.;

PreStep = aStep->GetPreStepPoint(); //We assign our previously defined PreStep (remember pointer to G4StepPoint )

currentVolumeName = PreStep->GetPhysicalVolume()->GetName(); // Get volume name at this step
particleName =aStep->GetTrack()->GetDefinition()->GetParticleName() ; // Get particle name
stepN = aStep->GetTrack()->GetCurrentStepNumber(); // Get step number
G4TrackStatus status = aStep->GetTrack()->GetTrackStatus(); // Get status of the particle "dead" or "alive"

//	if (currentVolumeName=="Cover"||currentVolumeName=="Cover2"||currentVolumeName=="Cover3"||currentVolumeName=="Cover4"||currentVolumeName=="Cover5") // if the particle is in the detector
//	{
//	if (particleName=="neutron"&&status!=fAlive){
//	pr_neutron =1.;
//	creationPosition = aStep->GetTrack()->GetVertexPosition();
//	G4cout<<"alive neutron in cover"<<G4endl;
//	}
//	}



//if (currentVolumeName=="Detector"||currentVolumeName=="Detector2"||currentVolumeName=="Detector3"||currentVolumeName=="Detector4"||currentVolumeName=="Detector5") // if the particle is in the detector
if (currentVolumeName=="Detector") // if the particle is in the detector
{
EdepStep = aStep->GetTotalEnergyDeposit(); // Get Energy Deposited in step and save in EdepStep variable
//		G4cout<<particleName<<"   "<<EdepStep<<G4endl;
if (EdepStep>0.)	
{
//			G4cout<<particleName<<"   "<<EdepStep<<G4endl;
//			G4cout<<EdepStep<<G4endl;
fEventAction->AddEdepInStep(EdepStep); // If is not 0. send this value to He3_counterEventAction.cc and calculate the total energy deposited per particle (by adding)
}


if (particleName=="triton" )
{
//	G4cout<<"*** triton ***"<<G4endl;
sLengthTriton = aStep->GetStepLength(); // Get step length
fEventAction->AddStepLengthTriton(sLengthTriton); // Add step lenghts
	if (status!=fAlive) // if the particle is alive
	{
	absorptionPositionT = aStep->GetTrack()->GetPosition(); //Get where its absorbed
	fEventAction->GetAbsorptionPositionT(absorptionPositionT.x(),absorptionPositionT.y(),absorptionPositionT.z()); //Send it to  He3_counterEventAction.cc 
	creationPositionT = aStep->GetTrack()->GetVertexPosition(); //Get where its created
	fEventAction->GetCreationPositionT(creationPositionT.x(),creationPositionT.y(),creationPositionT.z());  //Send it to  He3_counterEventAction.cc 
	}
}


if (particleName=="proton") // same as triton
{
//	G4cout<<"*** proton ***"<<G4endl;
sLengthProton = aStep->GetStepLength();
fEventAction->AddStepLengthProton(sLengthProton);
	if (status!=fAlive)
	{
	absorptionPositionP = aStep->GetTrack()->GetPosition();
	fEventAction->GetAbsorptionPositionP(absorptionPositionP.x(),absorptionPositionP.y(),absorptionPositionP.z());
	creationPositionP = aStep->GetTrack()->GetVertexPosition();
	fEventAction->GetCreationPositionP(creationPositionP.x(),creationPositionP.y(),creationPositionP.z());
	}
}

} // end if(currentVolume)



if(particleName=="triton" && stepN==1)
{
creationPosition = aStep->GetTrack()->GetVertexPosition();
fEventAction->GetCreationPosition(creationPosition.x(),creationPosition.y(),creationPosition.z());
}




}
