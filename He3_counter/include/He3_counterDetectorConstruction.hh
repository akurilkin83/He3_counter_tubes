//////////////////////////////////////////////////////////
//							//
//		 He3_counter G4 application		//
//		     akurilkin 2019			//
//							//
//////////////////////////////////////////////////////////

#ifndef He3_counterDetectorConstruction_h
#define He3_counterDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class He3_counterDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    He3_counterDetectorConstruction();
    ~He3_counterDetectorConstruction();

  public:
     G4VPhysicalVolume* Construct();


   private:
     G4bool fCheckOverlaps;

};



#endif




