#ifndef PMTSD_h
#define PMTSD_h 1


// Geant4 Libraries
//
//#include "G4DataVector.hh"
//#include "G4VSensitiveDetector.hh"


// Local Libraries
//
#include "PMTHit.hh"


// C++ Libraries
//
//#include <vector>

class G4Step;
class G4HCofThisEvent;


class PMTSD //: public G4VSensitiveDetector
{

  public:
    PMTSD();//G4String name);
    virtual ~PMTSD();
    virtual G4int ProcessHits(const G4Step* aStep);
    void resetPMTSD();
    G4double getPhoDetected()
    { 
      return phoDetec;
    }

  private:
   PMTHit *phoHit;
   G4int phoDetec;
   G4double kinEnergy;
};
#endif
