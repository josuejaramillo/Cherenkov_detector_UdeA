
// Geant4 Libraries
//
#include "G4Timer.hh"
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
// #include "G4GenericAnalysisManager.hh"


RunAction::RunAction()
 : G4UserRunAction()
{}


RunAction::~RunAction()
{
  if (outFile.is_open()) {
        outFile.close();
    }
}

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager
     = G4AnalysisManager::Instance();

  // G4String rootFile = "wcdRoot.root";
  // analysisManager->OpenFile("wcdRoot.root");

  // analysisManager->CreateNtuple("Hits", "Hits");
  // analysisManager->CreateNtupleIColumn("fEvent");
  // analysisManager->CreateNtupleDColumn("fX");
  // analysisManager->CreateNtupleDColumn("fY");
  // analysisManager->CreateNtupleDColumn("fZ");
  // analysisManager->CreateNtupleDColumn("n");
  // analysisManager->CreateNtupleDColumn("zFoton");
  // analysisManager->CreateNtupleDColumn("Ef");

  // analysisManager->FinishNtuple(0);


  // Abrir archivo ROOT
    analysisManager->OpenFile("wcdRoot.root");

    // Crear Ntuples para la información de la partícula madre y los fotones
    analysisManager->CreateNtuple("MotherData", "Información de la partícula madre");
    analysisManager->CreateNtupleIColumn("eventId");               // ID del evento
    analysisManager->CreateNtupleIColumn("numCherenkovPhotons");    // Número de fotones Cherenkov
    analysisManager->CreateNtupleDColumn("motherMomentumX");        // Momento px
    analysisManager->CreateNtupleDColumn("motherMomentumY");        // Momento py
    analysisManager->CreateNtupleDColumn("motherMomentumZ");        // Momento pz
    analysisManager->CreateNtupleDColumn("motherEnergy");           // Energía

    analysisManager->CreateNtuple("PhotonData", "Información de los fotones detectados");
    analysisManager->CreateNtupleIColumn("eventId");                // ID del evento
    analysisManager->CreateNtupleIColumn("photonTrackId");          // ID del track del fotón
    analysisManager->CreateNtupleDColumn("photonPx");           // Px
    analysisManager->CreateNtupleDColumn("photonPy");           // Py
    analysisManager->CreateNtupleDColumn("photonPz");           // Pz
    analysisManager->CreateNtupleDColumn("photonEnergy");           // Energía del fotón

    // Finalizar configuración de Ntuples
    analysisManager->FinishNtuple(0);  // Para MotherData
    analysisManager->FinishNtuple(1);  // Para PhotonData

  // Abrir el archivo al inicio de la corrida
  outFile.open("infPhotons.csv");
  if (!outFile.is_open()) {
      G4cerr << "Error al abrir el archivo de salida!" << G4endl;
  } else {
      // Escribir el encabezado una vez
      outFile << "EventID\tTrackID\tnPhotons\tPx\tPy\tPz\tKineticEnergy\tHits\n";
  }

}


void RunAction::EndOfRunAction(const G4Run*)
{
  // G4int nPhotons = PhotonCounter::Instance()->GetPhotonCount();
  // G4cout << "Num photons = " << nPhotons << G4endl;

  G4AnalysisManager* analysisManager
     = G4AnalysisManager::Instance();
  analysisManager->Write(); 
  analysisManager->CloseFile();

  if (outFile.is_open()) {
    outFile.close();
  }

}
