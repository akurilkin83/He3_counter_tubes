//////////////////////////////////////////////////////////
//							//
//		 He3_counter G4 application		//
//		     akurilkin 2019			//
// 		  			//
//							//
//////////////////////////////////////////////////////////

#ifndef He3_counterPrimaryGeneratorAction_h
#define He3_counterPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"


#include <cstring>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

class G4ParticleGun;
class G4SPSPosDistribution;
class G4Event;

class G4ParticleTable;
class G4ParticleDefinition;


class He3_counterPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  He3_counterPrimaryGeneratorAction();
  ~He3_counterPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event* anEvent);

  
private:
  G4ParticleGun*  fParticleGun; 
  G4ParticleTable* particleTable;
  G4ParticleDefinition* particle;
  G4String particleName;
  G4double x,y,z;
  G4double e0;

};

#endif






