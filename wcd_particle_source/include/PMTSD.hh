#ifndef PMTSD_h
#define PMTSD_h 1

#include "G4VSensitiveDetector.hh"
#include <vector>
class PMTSD : public G4VSensitiveDetector {
public:
    PMTSD(const G4String& name);
    virtual ~PMTSD();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
};

#endif
