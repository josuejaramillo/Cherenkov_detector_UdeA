// Geant4 Libraries
//
#include "G4Timer.hh"
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
// #include "G4GenericAnalysisManager.hh"


RunAction::RunAction(const std::string& nombreArchivo)
 : G4UserRunAction(), fNombreArchivoSalida(nombreArchivo)
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
    analysisManager->OpenFile(fNombreArchivoSalida);

    // Crear Ntuples para la información de la partícula madre y los fotones
    analysisManager->CreateNtuple("photonData", "Información de la partícula madre");
    analysisManager->CreateNtupleDColumn("photonEnergy");           // Energía del fotón
    analysisManager->CreateNtupleDColumn("photonWavelength");           // Energía del fotón

    // Finalizar configuración de Ntuples
    analysisManager->FinishNtuple(0); //For photons

  // Abrir el archivo al inicio de la corrida
  outFile.open(fNombreArchivoSalida + "_infPhotons.csv");
  if (!outFile.is_open()) {
      G4cerr << "Error al abrir el archivo de salida!" << G4endl;
  } else {
      // Escribir el encabezado una vez
      outFile << "EventID\tnPhotons\tHits\tDepositedEnergy\n";
      // outFile << "EventID\tTrackID\tnPhotons\tPx\tPy\tPz\tKineticEnergy\tHits\n";
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
