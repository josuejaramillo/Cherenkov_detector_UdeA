// Geant4 Libraries
//
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

    // Obtener el UserEventAction para actualizar el conteo de fotones y la energía
    auto eventAction = const_cast<UserEventAction*>(static_cast<const UserEventAction*>(G4RunManager::GetRunManager()->GetUserEventAction()));
    if (!eventAction) {
        return false; // Si no se obtiene, termina
    }
    // Contar los fotones
    eventAction->AddPhotonCount(); // Aumentar el contador de fotones
	if (eventAction->GetPhotonCount() > 1000) {
	G4cout << "Límite de 1000 fotones alcanzado, pasando al siguiente evento." << G4endl;
        G4RunManager::GetRunManager()->AbortEvent();  // Detiene el evento actual y pasa al siguiente
        return false;
    }
    // Obtener la energía del fotón y agregarla al total
    G4double photonEnergy = step->GetTrack()->GetKineticEnergy();
    eventAction->AddPhotonEnergy(photonEnergy); // Acumular energía depositada

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Obtener información del fotón detectado
    G4Track* track = step->GetTrack();
    int photonTrackId = track->GetTrackID();
    int eventId = UserEventAction::GetEventId();  // Obtener el ID del evento actual
    G4ThreeVector photonMomentum = track->GetMomentum();
    double px = photonMomentum.x();
    double py = photonMomentum.y();
    double pz = photonMomentum.z();

    G4ThreeVector photonPosition = track->GetPosition();
    double x = photonPosition.x();
    double y = photonPosition.y();
    double z = photonPosition.z();

    // Llenar los ntuples con la información del fotón
     // Convertir la energía a longitud de onda
    const G4double h = 4.135667696e-15;  // Constante de Planck en eV·s
    const G4double c = 3.0e8;  // Velocidad de la luz en m/s

    // Fórmula para calcular la longitud de onda (en metros)
    G4double photonWavelength = h * c / (photonEnergy*1e6);  // Longitud de onda en metros
    photonWavelength *= 1e9; //Longitud de onda en nm

    analysisManager->FillNtupleDColumn(0, 0, photonEnergy);     // Energía del fotón
    analysisManager->FillNtupleDColumn(0, 1, photonWavelength);     // Longitud de onda del fotón

    // Escribir los datos al archivo ROOT
    
    analysisManager->AddNtupleRow(0);
    return true; // Hit procesado correctamente
    
}
