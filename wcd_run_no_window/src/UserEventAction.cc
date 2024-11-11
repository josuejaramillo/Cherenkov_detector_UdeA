// Geant4 Libraries
//
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

// Local Libraries
//
#include "UserEventAction.hh"
#include "PhotonCounter.hh"
// Standard Libraries
//
#include <fstream>
#include <cmath>

UserEventAction::UserEventAction(std::ofstream& output)
    : outFile(output), fTotalPhotonEnergy(0.0) {}

UserEventAction::~UserEventAction() {}

void UserEventAction::BeginOfEventAction(const G4Event* event)
{
    fPhotonCount = 0; // Resetear el contador al inicio del evento
    fTotalPhotonEnergy = 0.0; // Resetear la energía total al inicio del evento
}

G4int UserEventAction::fEventId = -1;

void UserEventAction::EndOfEventAction(const G4Event* event)
{
    fEventId = event->GetEventID();
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4cout << "=======Event " << fEventId << G4endl;
    // if (!outFile.is_open()) {
    //     G4cerr << "El archivo de salida no está abierto!" << G4endl;
    //     return;
    // }

    for (int i = 0; i < event->GetNumberOfPrimaryVertex(); i++) {
        G4int nPhotons = PhotonCounter::Instance()->GetPhotonCount();

        for (int q = 0; q < event->GetPrimaryVertex(i)->GetNumberOfParticle(); q++) {
            auto primary = event->GetPrimaryVertex(i)->GetPrimary(q);

            // Obtener las componentes del momento Px, Py, Pz
            G4double Px = primary->GetPx();
            G4double Py = primary->GetPy();
            G4double Pz = primary->GetPz();

            G4double x = event->GetPrimaryVertex(i)->GetX0();
            G4double y = event->GetPrimaryVertex(i)->GetY0();
            G4double z = event->GetPrimaryVertex(i)->GetZ0();

            // Obtener la energía cinética
            G4double totalEnergy = primary->GetTotalEnergy() / 1000;

            // // Escribir la información en el archivo
            // outFile << fEventId << "\t"  // EventID
            //         // << primary->GetTrackID() << "\t" // TrackID
            //         << nPhotons << "\t"  // Número de fotones
            //         // << Px << "\t"  // Componente Px del momento
            //         // << Py << "\t"  // Componente Py del momento
            //         // << Pz << "\t"  // Componente Pz del momento
            //         // << kineticEnergy << "\t"  // Energía cinética
            //         << fPhotonCount << "\t" // Número de fotones detectados
            //         << fTotalPhotonEnergy << "\n"; // Energía total de fotones

            analysisManager->FillNtupleIColumn(1, 0, fEventId);
            analysisManager->FillNtupleIColumn(1, 1, nPhotons);
            analysisManager->FillNtupleIColumn(1, 2, fPhotonCount);
            analysisManager->FillNtupleDColumn(1, 3, fTotalPhotonEnergy);
            analysisManager->FillNtupleDColumn(1, 4, totalEnergy);

            analysisManager->FillNtupleDColumn(1, 5, Px);
            analysisManager->FillNtupleDColumn(1, 6, Py);
            analysisManager->FillNtupleDColumn(1, 7, Pz);

            analysisManager->FillNtupleDColumn(1, 8, x);
            analysisManager->FillNtupleDColumn(1, 9, y);
            analysisManager->FillNtupleDColumn(1, 10, z);

            analysisManager->AddNtupleRow(1);
        }
    }
}



