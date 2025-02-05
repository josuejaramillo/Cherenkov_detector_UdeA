#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"
#include "Randomize.hh"

#include "G4Event.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "PrimaryGeneratorAction_Ascii.hh"
#include "HEPEvtInterface.hh"


PrimaryGeneratorAction_Ascii::PrimaryGeneratorAction_Ascii()
{
//HEPEvt = new G4HEPEvtInterface("FinalFinal-myhepevt.txt"); // all GE11 System FinalFinal-myhepevt.txt
// HEPEvt = new G4HEPEvtInterface("/home/josue/Desktop/simulacion_corsika/12h_flux/analysis/shw/muonFlux_Medellin.txt");  // GE11-Superchamber 10
// HEPEvt = new G4HEPEvtInterface("/home/josue/Desktop/simulacion_corsika/12h_flux/analysis/shw/scripts/detectedMuons.txt", 2);  // GE11-Superchamber 10
HEPEvt = new G4HEPEvtInterface("/home/josue/Desktop/simulacion_corsika/12h_flux/analysis/shw/scripts/movedMuons.txt", 2);  // GE11-Superchamber 10
//Neutrons are green
//Photons are green
}
PrimaryGeneratorAction_Ascii::~PrimaryGeneratorAction_Ascii()
{
 delete HEPEvt;
}
void PrimaryGeneratorAction_Ascii::GeneratePrimaries(G4Event* anEvent)
{
    // HEPEvt->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,20.*cm));
    HEPEvt->GeneratePrimaryVertex(anEvent);
}

