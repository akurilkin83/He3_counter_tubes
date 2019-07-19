#include "He3_counterPrimaryGeneratorAction.hh"
#include "He3_counterParameters.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

He3_counterPrimaryGeneratorAction::He3_counterPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{

  G4int n_particle = 1;

  fParticleGun  = new G4ParticleGun(n_particle);
   
  particleTable = G4ParticleTable::GetParticleTable();
  particle = particleTable->FindParticle("neutron");
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.)); 

fParticleGun->SetParticleEnergy(0.025*eV); // mean energy 
//fParticleGun->SetParticleEnergy(0.005*eV); // thermal neutron energy 0.005<->0.5eV
//fParticleGun->SetParticleEnergy(0.00465*eV); // energy HERA 5 meV
}

He3_counterPrimaryGeneratorAction::~He3_counterPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void He3_counterPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
// for one tube, parallel beam
x = (G4UniformRand()-0.5)*LENGTH*cm;
y = (2*G4UniformRand()-1)*RAD*cm;  // for one tube
z = 0.*cm;
// G4UniformRand() output range [0,1]


//x = (2*G4UniformRand()-1)*LENGTH*cm+0.5*LENGTH*cm;
//y = (G4UniformRand())*3.5*cm; // beam size along y axis is 3.5 cm
//y = (3.555555556)*(2*G4UniformRand()-1)*RAD*cm-1.*RAD*cm + 3.2*cm; //for n tubes D-18 test 64mm
// 3.5555556 - scale factor = 64/18


// akurilkin 18.12.2019
// INITIAL BEAM ENERGY
// NERA
//e0=G4RandGauss::shoot(0.00465*eV,.0003575*eV); //  energy of initial neutron
e0 = 0.0253*eV; // mean
//e0 = 0.005*eV;   // lowest energy of thermal neutron
//e0 = 0.5*eV;   // highest energy of thermal neutron
//e0 = 0.00465*eV;   // energy of neutron for NERA

fParticleGun->SetParticleEnergy(e0);
//std::cout<<e0<<std::endl;


// Set initial beam position
fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));


// Set momentum direction
//fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,-0.5,1));
fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));


fParticleGun->GeneratePrimaryVertex(anEvent);

}





