//////////////////////////////////////////////////////////
//							//
//		 akurilkin 2019	                	//
//		 base is AnaEx02        		//
// 		                			//
//							//
//////////////////////////////////////////////////////////

#ifndef He3_counterSteppingAction_h
#define He3_counterSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include "G4Track.hh"

class He3_counterEventAction;
class He3_counterDetectorConstruction;


class He3_counterSteppingAction : public G4UserSteppingAction
{
// Declaration of the variables to be used in He3_counterSteppingAction.hh
public:
    He3_counterSteppingAction(He3_counterDetectorConstruction*,He3_counterEventAction*);

    virtual ~He3_counterSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

    G4double EdepStep;			//Energy deposited by particle (primary or secondary) in a Step
    G4ThreeVector creationPosition;		//Creation position of proton and triton through the He3(n,p)H3 reaction, i.e. position in which the reaction occurs
    G4ThreeVector absorptionPositionP;	//Proton absortion position
    G4ThreeVector absorptionPositionT;	//Triton absortion position
    G4ThreeVector creationPositionP;	//Proton creation position (same as creationPosition). Is not obligatory to use a different value, but I believe the code is easier to understand like this.
    G4ThreeVector creationPositionT;	//Triton creation position (same as creationPosition). Is not obligatory to use a different value, but I believe the code is easier to understand like this.
    G4int stepN;				//Step number of particle (primary or secondary)
private:
    He3_counterEventAction* fEventAction;    //Pointer to class G4EventAction
    He3_counterDetectorConstruction* fDetectorConstruction;
    G4Track *aTrack;  			//Define object for class G4Track (this will be used in order to use some of G4Tracks.hh functions)
    G4StepPoint *PreStep;			//Pointer to class G4StepPoint
    G4String currentVolumeName;		//String variable definition 
    G4String particleName;			//String variable definition
    G4double sLengthProton;			//Double float variable definition
    G4double sLengthTriton;			//Double float variable definition

};

#endif




