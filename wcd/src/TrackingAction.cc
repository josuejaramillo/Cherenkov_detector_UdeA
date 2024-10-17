#include "TrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4EventManager.hh"

// Constructor
TrackingAction::TrackingAction() : G4UserTrackingAction(), fPhotonID(100) {

    for (int i = 0; i < 50; ++i) {
    // Generar fotones aquí y obtener su ID
    G4int newPhotonID = i;/* ID del nuevo fotón */;
    fPhotonIDs.push_back(newPhotonID); // Agregar el ID a la lista
    }

} // Cambia el 1 por el ID deseado

TrackingAction::~TrackingAction() {}

// Método llamado antes de realizar la acción de seguimiento
// void TrackingAction::PreUserTrackingAction(const G4Track* track) {
//     // Verificar si el track es un fotón óptico
//     if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
//         // Comprobar el ID del fotón que quieres visualizar
//         if (track->GetTrackID() == fPhotonID) { // Usa fPhotonID
//             // Almacenar la trayectoria de este fotón
//             G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
//             trackingManager->SetStoreTrajectory(true);
//         } else {
//             G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
//             trackingManager->SetStoreTrajectory(false);
//         }
//     } else {
//         G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
//         trackingManager->SetStoreTrajectory(false);
//     }
// }

void TrackingAction::PreUserTrackingAction(const G4Track* track) {
    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        G4int currentID = track->GetTrackID();

        

        if (std::find(fPhotonIDs.begin(), fPhotonIDs.end(), currentID) != fPhotonIDs.end()) {
            G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
            trackingManager->SetStoreTrajectory(true);
            // G4double energy = track->GetKineticEnergy();
            // G4cout << energy << G4endl;
        } else {
            G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
            trackingManager->SetStoreTrajectory(false);
        }
    } else {
        G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
        trackingManager->SetStoreTrajectory(false);
    }
}
