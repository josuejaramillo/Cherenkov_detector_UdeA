#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "Randomize.hh"
#include "ActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include <string>
#include <cstdlib>  // Para std::atoi

int main(int argc, char** argv)
{
  // Valores predeterminados
  int t = 1; // 1 seg
  std::string nombreArchivoBase = "output.root";  // Nombre predeterminado
  long seed = 12345;  // Semilla predeterminada
  bool useVis = false;

  // Analizar argumentos de la línea de comandos
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-time" && i + 1 < argc) {
      t = std::atoi(argv[i + 1]);
      i++;
    } else if (std::string(argv[i]) == "-output" && i + 1 < argc) {
      nombreArchivoBase = argv[i + 1];
      i++;
    } else if (std::string(argv[i]) == "-seed" && i + 1 < argc) {
      seed = std::stol(argv[i + 1]);
      i++;
    } else if (std::string(argv[i]) == "-vis") {
      useVis = true;
    }
  }

  // *********************************************************************************
  std::map<std::string,double> particleRates = {
    {"mu-",     62.374},
    {"mu+",     74.862},
    {"e-",      38.204},
    {"e+",      21.610},
    // {"gamma",  537.494},
    {"proton",   5.018},
    // {"neutron", 31.854}
  };

  // Convert rates into counts for the chosen simulation time window
  std::map<std::string,int> particleCounts;
  double S_det = M_PI*(0.88*0.5)*(0.88*0.5); // Effective surface of the Cherenkov detector
  for (const auto& kv : particleRates) {
      int Ni = static_cast<int>(kv.second * S_det * t);
      particleCounts[kv.first] = Ni;
      G4cout << kv.first << " → " << Ni << G4endl;
  }

  // Total number of particles across all species
  int Ntot = 0;
  for (auto& kv : particleCounts) Ntot += kv.second;
  G4cout << "Number of particles " << Ntot << G4endl;
  // *********************************************************************************

  std::string nombreArchivoSalida = "./rootFiles/" + nombreArchivoBase + "_" + std::to_string(seed);

  // Determina si se está en modo interactivo
  G4UIExecutive* ui = nullptr;
  if (argc == 1 || useVis) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Seed for reproducibility, this might be unnecersary... or problematic
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed(seed);

  // RunManager
  G4RunManager* runManager = new G4RunManager;

  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization(nombreArchivoSalida, particleCounts));
  runManager->Initialize();

  // Visualization manager (solo si es interactivo o -vis)
  G4VisExecutive* visManager = nullptr;
  if (ui) {
    visManager = new G4VisExecutive;
    visManager->Initialize();
  }

  // UI manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (!ui) {
    // --- Modo batch ---
    UImanager->ApplyCommand("/run/beamOn " + std::to_string(Ntot));
    UImanager->ApplyCommand("/run/verbose 2");
    UImanager->ApplyCommand("/run/eventMaxTime 1000 ms");
  } else {
    // --- Modo interactivo con visualización ---
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

  if (visManager) delete visManager;
  delete runManager;
  return 0;
}
