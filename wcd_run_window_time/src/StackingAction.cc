
// Geant4 Libraries
//
#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"


// Local Libraries
//
#include "StackingAction.hh"


StackingAction::StackingAction()
  : G4UserStackingAction(),
    fScintillationCounter(0),
    fCerenkovCounter(0),
    lengthMax(0.)
{
   G4cout << "...StackingAction..." << G4endl;
}


StackingAction::~StackingAction()
{}


G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{ 
  if(aTrack->GetParentID()==0)
    lengthMax = aTrack->GetTrackLength();
    
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        fScintillationCounter++;
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
         if(aTrack->GetTotalEnergy() > 1.6e-06//2.13e-6//1.6e-06
             && aTrack->GetTotalEnergy() < 3.1e-6)//4.13e-6)//3.1e-6)
                 fCerenkovCounter++;
    }
  }


  return fUrgent;

}


void StackingAction::NewStage()
{
/*  G4cout << "Number of Scintillation photons produced in this event : "
         << fScintillationCounter << G4endl;
  G4cout << "Number of Cerenkov photons produced in this event : "
         << fCerenkovCounter << G4endl;*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingAction::PrepareNewEvent()
{
  fScintillationCounter = 0;
  fCerenkovCounter = 0;
}
