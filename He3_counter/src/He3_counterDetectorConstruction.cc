// -- Detector construction class
// akurilkin 2019

#include "He3_counterDetectorConstruction.hh"
#include "He3_counterParameters.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
//#include "G4Cons.hh"
//#include "G4Torus.hh"
//#include "G4Sphere.hh"

#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4VisAttributes.hh"
#include "G4UserLimits.hh"
//#include "G4PVReplica.hh"
#include "G4IntersectionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Colour.hh"
#include "G4VSolid.hh"
#include "G4VUserDetectorConstruction.hh"
#include <G4UnitsTable.hh>
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
//#include "fstream"
#include "iomanip"
#include <iostream> 
#include <sstream> 


using namespace std;

He3_counterDetectorConstruction::He3_counterDetectorConstruction()

{ }

He3_counterDetectorConstruction::~He3_counterDetectorConstruction()
{ }

G4VPhysicalVolume* He3_counterDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

	//-------------------------World-------------------------//
	// Vacuum
	G4double vac_density = 2.376e-15*g/cm3; 
	G4double vac_temperature= 300*kelvin;
	G4double vac_pressure= 2.0e-7*bar;
	G4Material* Vacuum = new G4Material("Vacuum", vac_density, 1, kStateGas ,vac_temperature ,vac_pressure);
	G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");
	Vacuum->AddMaterial(Air, 1.);
	G4double world_sizeXY =60*m;
	G4double world_sizeZ  = 60*m;
	G4Material* world_mat = Vacuum;

	G4Box* solidWorld =    
	    			new G4Box("World",    			                   //its name
	       			0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);      //its size
	      
	G4LogicalVolume* logicWorld =                         
	    new G4LogicalVolume(solidWorld,          //its solid
		                world_mat,           //its material
		                "World");            //its name
		                           
	G4VPhysicalVolume* physWorld = 
	    				new G4PVPlacement(0,   //no rotation
		              		G4ThreeVector(0,0,0),  //at (0,0,0)
		              		logicWorld,            //its logical volume
		              		"World",               //its name
		              		0,                     //its mother  volume
		              		false,                 //no boolean operation
		              		0,                     //copy number
		              		checkOverlaps);        //overlaps checking


	//-------------------------He3+cover+wire-------------------------//

// akurilkin 05.02.18 wire 
//	G4double wire_rmax = RAD_wire*cm;
//	G4double wire_hz = LENGTH*cm+2*mm;
//	G4double wire_rmin = 0*mm, wire_phimin = 0.*deg, wire_phimax = 360.*deg;
//	G4Material* wire_mat = nist->FindOrBuildMaterial("G4_Au");
// end wire

	// Cover:
	// -> Parameters
//	G4double cover_rmax = RAD*cm+.3*mm;    // 0.3 mm for He18/180-8.0atm
	G4double cover_rmax = RAD*cm+.2*mm;    // 0.2 mm  tasks Andrey
	G4double cover_hz = LENGTH*cm+2*mm;
	G4double cover_rmin = 0*mm, cover_phimin = 0.*deg, cover_phimax = 360.*deg;
	

	G4cout<<2*cover_rmax<<" :  **********!!!!!!!!!!"<<G4endl;

// 14.02.18 position for detectors from 4-th tube
//	G4ThreeVector cover_pos = G4ThreeVector(0,0,POSITION*mm+RAD*cm);
//	G4ThreeVector cover_pos2 = G4ThreeVector(0,4.*RAD*cm-1.*cm,POSITION*mm+RAD*cm);
//	G4ThreeVector cover_pos3 = G4ThreeVector(0,2*RAD*cm-0.5*cm ,POSITION*mm+2.6*RAD*cm);
//	G4ThreeVector cover_pos4 = G4ThreeVector(0,6.*RAD*cm-1.5*cm,POSITION*mm+2.6*RAD*cm);

	G4ThreeVector cover_pos = G4ThreeVector(0,0,POSITION*mm+RAD*cm);


G4cout<< "!!!!!!!!!!!---- 1 --"<<cover_pos<<"--------!!!!!!"<<G4endl;


    G4cout<<" 1 : y = "<<0<<";  z = "<<POSITION*mm+RAD*cm<<G4endl;


// for several tubes it is need addition cover_pos 
// 19.02. 3 tubes 25   if 
//	G4ThreeVector cover_pos = G4ThreeVector(0,0,POSITION*mm+RAD*cm);
//	G4ThreeVector cover_pos2 = G4ThreeVector(0,2.*RAD*cm+.9*cm,POSITION*mm+RAD*cm);
//	G4ThreeVector cover_pos3 = G4ThreeVector(0,1.*RAD*cm+0.45*cm,POSITION*mm+2.7*RAD*cm);

	G4RotationMatrix* myRotation = new G4RotationMatrix();
// true
	myRotation->rotateX(0.*deg);  //good
	myRotation->rotateY(90.*deg);
	myRotation->rotateZ(0.*deg);


// Material 
	G4Material* cover_mat = nist->FindOrBuildMaterial("G4_Fe");

	G4Tubs* solidCover =new G4Tubs("Cover", 
                		    cover_rmin, cover_rmax, 0.5*cover_hz,
               			    cover_phimin, cover_phimax);
                      
	G4LogicalVolume* logicCover = new G4LogicalVolume(solidCover,           //its solid
                                  	  cover_mat,			        //its material
                                  	  "Cover");				//its name
     

	new G4PVPlacement(myRotation,              //rotation
                         cover_pos,                //at position
                         logicCover,               //its logical volume
                         "Cover",                  //its name
                         logicWorld,               //its mother  volume
                         false,                    //no boolean operation
                         0,                        //copy number
                         checkOverlaps);           //overlaps checking

	G4VisAttributes* CoverVisAttributes = new G4VisAttributes(G4Colour(0.478, 0.486, 0.474));    
//        logicCover->SetVisAttributes(CoverVisAttributes);         	// change the cover's color of detector


// 15.01.18

// 2-th tube example
/*
	G4Tubs* solidCover2 = new G4Tubs("Cover2", 
                		    cover_rmin, cover_rmax, 0.5*cover_hz,
               			    cover_phimin, cover_phimax);
                      
	G4LogicalVolume* logicCover2 = new G4LogicalVolume(solidCover2,           //its solid
                                  	  cover_mat,			        //its material
                                  	  "Cover2");				//its name
     
	new G4PVPlacement(myRotation,              //rotation
                         cover_pos2,                //at position
                         logicCover2,               //its logical volume
                         "Cover2",                  //its name
                         logicWorld,               //its mother  volume
                         false,                    //no boolean operation
                         0,                        //copy number
                         checkOverlaps);           //overlaps checking
*/





	// -> Parameters
	G4double detector_rmax = RAD*cm;
	G4double detector_hz = LENGTH*cm;
//	G4double detector_rmin = RAD_wire*cm, detector_phimin = 0.*deg, detector_phimax = 360.*deg; // ??? 
	G4double detector_rmin = 0*cm, detector_phimin = 0.*deg, detector_phimax = 360.*deg;
	G4ThreeVector detector_pos = G4ThreeVector(0,0,0);
//	G4ThreeVector detector_pos2 = G4ThreeVector(0,0,0);
  

// -> Material (assuming ideal gas)
// components of gas mixture, change if it is needed    
	G4double volume = 3.14159265359*RAD*RAD*LENGTH; //volume in cm^3
	G4double R = 83.14472; // ideal gas constant in cm^3*bar/(K*mol)
	G4double T = 293.15; //20ºC temperature
	G4double P = (pAr + pCO2 + pHe3 +pCF4); // total gas mix pressure in bar
	G4double nmolMix = P*volume/(R*T);      //number of moles in the mix
	G4double mmAr = 39.948, mmCO2 = 44.009, mmHe3 = 3.016, mmCF4= 88.043;  // molar mass of each gas in g/mole
	G4double mmMix = pAr/P*mmAr + pCO2/P*mmCO2 + pHe3/P*mmHe3 +pCF4/P*mmCF4; // average molar mass of the whole gas mix
	G4double mixDensity = nmolMix*mmMix/volume; //number of moles * grams per mole/ volume = density in g/cm^3  	

	G4double mfAr = pAr/P*mmAr/mmMix*100, mfCO2 = pCO2/P*mmCO2/mmMix*100, mfHe3 = pHe3/P*mmHe3/mmMix*100, mfCF4 = pCF4/P*mmCF4/mmMix*100; // mass fraction (fraction mass) of each gas in %
 
	G4int ncomp, z, A, natoms, ncomponents;		//number of components, atomic number, number of nucleons, number of atoms, number of components
	G4double density;	//density
	G4double mat;		//atomic mass

// 01.07.19
	G4Isotope* isoHe3 = new G4Isotope ("isoHe3", z=2., A=3., mat = 3.016*g/mole); 
	G4Element* elHe3  = new G4Element("elHe3", "He3", ncomponents=1);
	elHe3->AddIsotope(isoHe3, 100.*perCent);
	G4Material* He3 =  new G4Material("He3",density = 0.135e-3*g/cm3,ncomp=1); 
	He3->AddElement(elHe3, natoms=1);


 	G4Element* elAr  = new G4Element("elArgon","Ar",z=18.,mat = 39.948*g/mole);
	G4Material* Ar =  new G4Material("Argon",density = 1.784-3*g/cm3,ncomp=1); 
	Ar->AddElement(elAr, natoms=1);


	G4Element* elO  = new G4Element("elOxygen","O",z=8.,mat = 15.999*g/mole);
 	G4Element* elC  = new G4Element("elCarbon","C",z=6.,mat = 12.011*g/mole);
	G4Material* CO2 =  new G4Material("CO2",density = 1.98e-3*g/cm3 ,ncomp=2); 
	CO2->AddElement(elC, natoms=1);
	CO2->AddElement(elO, natoms=2);

        G4Element* elF = new G4Element("elFtor","F",z=9.,mat = 18.9984*g/mole);
	G4Material* CF4 =  new G4Material("CF4",density = 3.72e-3*g/cm3 ,ncomp=2); // density at 15 deg C
	CF4->AddElement(elC, natoms=1);
	CF4->AddElement(elF, natoms=4);
        

	G4Material* GasMix = new G4Material("GasMix",mixDensity*g/cm3,ncomponents=4); 
	GasMix->AddMaterial(He3,mfHe3*perCent); 
	GasMix->AddMaterial(CO2,mfCO2*perCent); 
	GasMix->AddMaterial(Ar,mfAr*perCent); 
	GasMix->AddMaterial(CF4,mfCF4*perCent); 
	




//   detector definition
	G4Tubs* solidDetector =    
        		            new G4Tubs("Detector", 
                		    detector_rmin, detector_rmax, 0.5*detector_hz,
               			    detector_phimin, detector_phimax);
                      
	G4LogicalVolume* logicDetector =                         
                           		  new G4LogicalVolume(solidDetector,           //its solid
                                  	  GasMix,			        //its material
                                  	  "Detector");					//its name
     
	new G4PVPlacement(0,                       //no rotation
                         detector_pos,             //at position
                         logicDetector,            //its logical volume
                         "Detector",               //its name
                         logicCover,               //its mother  volume
                         false,                    //no boolean operation
                         0,                        //copy number
                         checkOverlaps);           //overlaps checking 

	G4VisAttributes* DetectorVisAttributes = new G4VisAttributes(G4Colour(0.509, 0.352, 0.929));    
        logicDetector->SetVisAttributes(DetectorVisAttributes);


// add 12.01.18
// 2-th tube
/*
	G4Tubs* solidDetector2 =    
        		            new G4Tubs("Detector2", 
                		    detector_rmin, detector_rmax, 0.5*detector_hz,
               			    detector_phimin, detector_phimax);
                      
	G4LogicalVolume* logicDetector2 =                         
                           		  new G4LogicalVolume(solidDetector2,           //its solid
                                  	  GasMix,			        //its material
                                  	  "Detector2");					//its name



	new G4PVPlacement(0,                       //no rotation
                         detector_pos2,             //at position
                         logicDetector2,            //its logical volume
                         "Detector2",               //its name
                         logicCover2,               //its mother  volume
                         false,                    //no boolean operation
                         0,                        //copy number
                         checkOverlaps);           //overlaps checking 

	G4VisAttributes* DetectorVisAttributes2 = new G4VisAttributes(G4Colour(0.509, 0.352, 0.929));    
        logicDetector2->SetVisAttributes(DetectorVisAttributes2);
*/



// end 12.01.18


cout<<" ------------------------>  DETECTOR DENSITY <-----------------------------"<<endl;
cout<<" P = "<<P<<" RAD ="<<RAD<<"  LENGTH "<<LENGTH<<"  V = "<<volume<<"  T "<<T<<endl;
cout<<"nmolMix  ="<< nmolMix<<" mmMix = "<<mmMix<<"  ngrams = "<<nmolMix*mmMix<<endl;
cout<<mixDensity<<endl;       
G4cout<<" CHECK OVERLAPS "<<checkOverlaps<<G4endl;
return physWorld;
}






