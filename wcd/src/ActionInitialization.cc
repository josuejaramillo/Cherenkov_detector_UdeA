//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: ActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.hh"
// #include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
#include "SteppingVerbose.hh"
#include "UserEventAction.hh"

#include "ParticleSource.hh"

#include "TrackingAction.hh"
#include "G4RunManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization(const std::string& nombreArchivo)
 : G4VUserActionInitialization(), fNombreArchivoSalida(nombreArchivo)
{
  // Extraer la semilla del nombre del archivo
   size_t pos = fNombreArchivoSalida.find_last_of("_");
   if (pos != std::string::npos) {
       // Extraer la parte del nombre que contiene la semilla
       std::string seedStr = fNombreArchivoSalida.substr(pos + 1);
       fSeed = std::stoi(seedStr); // Convertir el valor a entero
   } else {
       // Si no se encuentra una semilla, establecer una predeterminada
       fSeed = 12345;  // Semilla predeterminada
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction(fNombreArchivoSalida));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
//  SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(new ParticleSource(fSeed)); //Generate particles from distribution
  SetUserAction(new SteppingAction());
  SetUserAction(new StackingAction());

  auto* runAction = new RunAction(fNombreArchivoSalida);
  SetUserAction(runAction);

  auto* eventAction = new UserEventAction(runAction->outFile);
  SetUserAction(eventAction);

  SetUserAction(new TrackingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose* ActionInitialization::InitializeSteppingVerbose() const
{
  return new SteppingVerbose();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
