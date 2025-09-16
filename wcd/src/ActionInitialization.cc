#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
#include "SteppingVerbose.hh"
#include "UserEventAction.hh"
#include "ParticleSource.hh"
#include "TrackingAction.hh"
#include "G4RunManager.hh"

ActionInitialization::ActionInitialization(const std::string& nombreArchivo,
                                           const std::map<std::string,int>& counts)
 : G4VUserActionInitialization(),
   fNombreArchivoSalida(nombreArchivo),
   fCounts(counts)
{
  // Extraer la semilla del nombre del archivo
  size_t pos = fNombreArchivoSalida.find_last_of("_");
  if (pos != std::string::npos) {
      std::string seedStr = fNombreArchivoSalida.substr(pos + 1);
      fSeed = std::stoi(seedStr);
  } else {
      fSeed = 12345;  // Semilla predeterminada
  }
}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction(fNombreArchivoSalida));
}

void ActionInitialization::Build() const
{
  // NEW: ParticleSource now takes seed + counts
  SetUserAction(new ParticleSource(fSeed, fCounts));

  SetUserAction(new SteppingAction());
  SetUserAction(new StackingAction());

  auto* runAction = new RunAction(fNombreArchivoSalida);
  SetUserAction(runAction);

  auto* eventAction = new UserEventAction(runAction->outFile);
  SetUserAction(eventAction);

  SetUserAction(new TrackingAction());
}

G4VSteppingVerbose* ActionInitialization::InitializeSteppingVerbose() const
{
  return new SteppingVerbose();
}
