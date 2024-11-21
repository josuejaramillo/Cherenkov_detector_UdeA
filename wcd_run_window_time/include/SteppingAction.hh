#ifndef SteppingAction_h
#define SteppingAction_h 1


// Geant4 Libraries
//
#include "G4UserSteppingAction.hh"
#include "globals.hh"


// Local Libraries
//
#include "DetectorConstruction.hh"
#include "PMTSD.hh"
#include "PhotonCounter.hh"

/// Stepping action class
/// 

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction();
    virtual ~SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    const DetectorConstruction *detectorConstruction;
    G4VPhysicalVolume* fwaterVolume;
    G4int fScintillationCounter;
    G4int fCerenkovCounter;
    G4int lengthMaxOk;
    G4double priEner;
    G4int fEventNumber;
    // PMTSD *pmtSD;
    G4int phoOnPmt;
    G4double colSP;
    G4double radSP;
    G4int alpmt;
    G4double water_in;
    G4double water_out;
    G4double water_died;
    G4int alsuelo;
    G4int generadas;
    G4int generadas1;
    G4double ener_e;
    G4double ener_g;
    G4double ener_n;
    G4double ener_p;
    G4int detect_g;
    G4int detect_e;
    G4double ener_e_det;
    G4double ener_g_det;
    //G4int termina;
    //G4double tiempo;
};

#endif
