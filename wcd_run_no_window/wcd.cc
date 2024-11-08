#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "Randomize.hh"
#include "ActionInitialization.hh"
#include "G4UIExecutive.hh"
#include <string>
#include <cstdlib>  // Para std::atoi

int main(int argc, char** argv)
{
   // Valor predeterminado de N y variables para archivo y semilla
  int N = 1000;
  std::string nombreArchivoBase = "output.root";  // Nombre predeterminado
  long seed = 12345;  // Semilla predeterminada

  // Analizar argumentos de la línea de comandos
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-N" && i + 1 < argc) {
      N = std::atoi(argv[i + 1]);
      i++;  // Saltar al siguiente argumento después de -N
    } else if (std::string(argv[i]) == "-output" && i + 1 < argc) {
      nombreArchivoBase = argv[i + 1];
      i++;  // Saltar al siguiente argumento después de -output
    } else if (std::string(argv[i]) == "-seed" && i + 1 < argc) {
      seed = std::stol(argv[i + 1]);
      i++;  // Saltar al siguiente argumento después de -seed
    }
  }

  std::string nombreArchivoSalida = nombreArchivoBase + "_" + std::to_string(seed);

  // Determina si se está en modo interactivo o batch
  G4UIExecutive* ui = nullptr;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);  // Modo interactivo solo si no hay archivo macro
  }

  // Selecciona el motor de números aleatorios
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construye el RunManager
  G4RunManager* runManager = new G4RunManager;

  // Inicializa las clases necesarias
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization(nombreArchivoSalida));
  // Inicializa el núcleo de Geant4
  runManager->Initialize();

  // Obtiene el puntero al manejador de la interfaz de usuario
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (!ui) {
    // Modo batch (sin interfaz gráfica)
    G4String command = "/run/beamOn " + std::to_string(N);  // Ejecuta N eventos
    UImanager->ApplyCommand(command);
    UImanager->ApplyCommand("/run/verbose 2");
    UImanager->ApplyCommand("/run/eventMaxTime 1000 ms");
    
    
  } else {
    // Modo interactivo (sin visualización)
    UImanager->ApplyCommand("/control/execute init.mac");
    ui->SessionStart();
    delete ui;
  }

  // Termina la simulación
  delete runManager;
  return 0;
}
