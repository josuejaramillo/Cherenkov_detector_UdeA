#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "Randomize.hh"
#include "ActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include <string>
#include <cstdlib>
#include <map>

int main(int argc, char** argv)
{
  // Valores predeterminados
  int t = 1; // 1 seg
  std::string nombreArchivoBase = "output.root";
  long seed = 12345;
  bool useVis = false;

  // --- Nuevos parámetros ---
  std::string medium = "Water";  // "Water" o "TiO2"
  double conc = 0.0;             // 0.01, 10, 20, 30

  // Analizar argumentos de la línea de comandos
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-time" && i + 1 < argc) {
      t = std::atoi(argv[++i]);
    } else if (arg == "-output" && i + 1 < argc) {
      nombreArchivoBase = argv[++i];
    } else if (arg == "-seed" && i + 1 < argc) {
      seed = std::stol(argv[++i]);
    } else if (arg == "-vis") {
      useVis = true;
    } else if (arg == "-medium" && i + 1 < argc) {
      medium = argv[++i]; // e.g., Water or TiO2
    } else if (arg == "-conc" && i + 1 < argc) {
      conc = std::stod(argv[++i]); // e.g., 0.01, 10, 20, 30
    }
  }

  G4cout << "----------------------------------------" << G4endl;
  G4cout << " Selected Medium: " << medium << G4endl;

  if (medium == "TiO2" || medium == "TiO2_colloid") {
      G4cout << " TiO2 Concentration: " << conc << " %" << G4endl;
  }

  G4cout << "----------------------------------------" << G4endl;

  // *********************************************************************************
  std::map<std::string,double> particleRates = {
    {"mu-",     62.374},
    {"mu+",     74.862},
    {"e-",      38.204},
    {"e+",      21.610},
    {"proton",   5.018}
  };

  std::map<std::string,int> particleCounts;
  double S_det = M_PI*(0.268*0.5)*(0.268*0.5);
  for (const auto& kv : particleRates) {
      int Ni = static_cast<int>(kv.second * S_det * t);
      particleCounts[kv.first] = Ni;
      G4cout << kv.first << " → " << Ni << G4endl;
  }

  int Ntot = 0;
  for (auto& kv : particleCounts) Ntot += kv.second;
  G4cout << "Number of particles " << Ntot << G4endl;
  // *********************************************************************************

  std::string nombreArchivoSalida = "./rootFiles/" + nombreArchivoBase + "_" + std::to_string(seed);

  G4UIExecutive* ui = nullptr;
  if (argc == 1 || useVis) ui = new G4UIExecutive(argc, argv);

  // Seed
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed(seed);

  // RunManager
  G4RunManager* runManager = new G4RunManager;

  // *** DetectorConstruction with selectable medium and concentration ***
  runManager->SetUserInitialization(new DetectorConstruction(medium, conc));

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
