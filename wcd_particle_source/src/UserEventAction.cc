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


UserEventAction::UserEventAction(std::ofstream& output) : outFile(output) {}

UserEventAction::~UserEventAction() {}


void UserEventAction::BeginOfEventAction(const G4Event* event)
{

  
  // G4cout << "Begin Event: " << event->GetPos() << G4endl;
  fPhotonCount = 0; // Resetear el contador al inicio del evento
}

G4int UserEventAction::fEventId = -1;
void UserEventAction::EndOfEventAction(const G4Event* event)
{
  fEventId = event->GetEventID();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4cout << "---- Event Action ----" << G4endl;

  // Asegurarse de que el archivo esté abierto
  if (!outFile.is_open()) {
    G4cerr << "El archivo de salida no está abierto!" << G4endl;
    return;
  }

  for (int i = 0; i < event->GetNumberOfPrimaryVertex(); i++) {
    G4int nPhotons = PhotonCounter::Instance()->GetPhotonCount();

    for (int q = 0; q < event->GetPrimaryVertex(i)->GetNumberOfParticle(); q++) {
      auto primary = event->GetPrimaryVertex(i)->GetPrimary(q);

      // Obtener las componentes del momento Px, Py, Pz
      G4double Px = primary->GetPx();
      G4double Py = primary->GetPy();
      G4double Pz = primary->GetPz();

      // Obtener la energía cinética
      G4double kineticEnergy = primary->GetKineticEnergy();

      // Escribir la información en el archivo en el orden deseado: EventID, TrackID, nPhotons, Px, Py, Pz, KineticEnergy
      outFile << fEventId << "\t"  // EventID
              << primary->GetTrackID() << "\t" // TrackID
              << nPhotons << "\t"  // Número de fotones
              << Px << "\t"  // Componente Px del momento
              << Py << "\t"  // Componente Py del momento
              << Pz << "\t"  // Componente Pz del momento
              << kineticEnergy << "\t"  // Energía cinética
              << fPhotonCount << "\n";

      // Llenar los ntuples con la información de la partícula madre
      analysisManager->FillNtupleIColumn(0, 0, fEventId);
      analysisManager->FillNtupleIColumn(0, 1, nPhotons);
      analysisManager->FillNtupleDColumn(0, 2, Px);  // px
      analysisManager->FillNtupleDColumn(0, 3, Py);  // py
      analysisManager->FillNtupleDColumn(0, 4, Pz);  // pz
      analysisManager->FillNtupleDColumn(0, 5, kineticEnergy);

      // Escribir los datos al archivo ROOT
      analysisManager->AddNtupleRow(0);
      
    }
  }
}
