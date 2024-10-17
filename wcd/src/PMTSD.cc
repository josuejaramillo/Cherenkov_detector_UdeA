#include "PMTSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"
#include "UserEventAction.hh"

PMTSD::PMTSD(const G4String& name)
    : G4VSensitiveDetector(name) {}

PMTSD::~PMTSD() {}

G4bool PMTSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    // Verificar si la partícula es un fotón óptico
    if (step->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) {
        return false; // No es un fotón óptico, no lo contamos
    }

    // Si el momento en z es negativo, no lo contamos
    if (step->GetTrack()->GetMomentumDirection().z() < 0) {
        return false;
    }

    // Obtener el UserEventAction para actualizar el conteo de fotones
    auto eventAction = const_cast<UserEventAction*>(static_cast<const UserEventAction*>(G4RunManager::GetRunManager()->GetUserEventAction()));
    if (!eventAction) {
        return false; // Si no se obtiene, termina
    }

    // Contar los fotones
    eventAction->AddPhotonCount(); // Aquí asumimos que has definido AddPhoton() en UserEventAction para aumentar el contador
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Obtener información del fotón detectado
    G4Track* track = step->GetTrack();
    int photonTrackId = track->GetTrackID();
    float photonEnergy = track->GetKineticEnergy();
    int eventId = UserEventAction::GetEventId();  // Obtener el ID del evento actual
    G4ThreeVector photonMomentum = track->GetMomentum();
    double px = photonMomentum.x();
    double py = photonMomentum.y();
    double pz = photonMomentum.z();

    // Llenar los ntuples con la información del fotón
    analysisManager->FillNtupleIColumn(1, 0, eventId);          // ID del evento
    analysisManager->FillNtupleIColumn(1, 1, photonTrackId);    // Track ID del fotón
    analysisManager->FillNtupleDColumn(1, 2, px);     // Px
    analysisManager->FillNtupleDColumn(1, 3, py);     // Py
    analysisManager->FillNtupleDColumn(1, 4, pz);     // Pz
    analysisManager->FillNtupleDColumn(1, 5, photonEnergy);     // Energía del fotón

    // Escribir los datos al archivo ROOT
    analysisManager->AddNtupleRow(1); 

    return true; // Hit procesado correctamente
}
