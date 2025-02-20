#include "TrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4EventManager.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
// Constructor
TrackingAction::TrackingAction() : G4UserTrackingAction(), fPhotonID(100) {

    for (int i = 0; i < 100; ++i) {
    // Generar fotones aquí y obtener su ID
    G4int newPhotonID = i;/* ID del nuevo fotón */;
    fPhotonIDs.push_back(newPhotonID); // Agregar el ID a la lista
    }

} // Cambia el 1 por el ID deseado

TrackingAction::~TrackingAction() {}

void TrackingAction::PreUserTrackingAction(const G4Track* track) {
    // // Almacenar trayectorias para fotones ópticos
    // G4int currentEventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    // G4int stopEventID = 64;
    // if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()& currentEventID == stopEventID) {
    //     G4int currentID = track->GetTrackID();

    //     if (std::find(fPhotonIDs.begin(), fPhotonIDs.end(), currentID) != fPhotonIDs.end() ) {
    //         G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
    //         trackingManager->SetStoreTrajectory(true);
    //     } else {
    //         G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
    //         trackingManager->SetStoreTrajectory(false);
    //     }
        
    // }
    // // Almacenar trayectorias para muones
    // else if (track->GetDefinition() == G4MuonPlus::MuonPlusDefinition() ||
    //          track->GetDefinition() == G4MuonMinus::MuonMinusDefinition()) {
    //     G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
    //     trackingManager->SetStoreTrajectory(false); // Guardar la trayectoria del muón
    // } else {
    //     G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
    //     trackingManager->SetStoreTrajectory(false); // No guardar trayectorias para otras partículas
    // }
}
