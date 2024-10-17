#ifndef PHOTON_COUNTER_HH
#define PHOTON_COUNTER_HH

#include "globals.hh"

class PhotonCounter {
public:
    static PhotonCounter* Instance();
    
    void AddPhoton() { fPhotonCount++; }
    G4int GetPhotonCount() const { return fPhotonCount; }

    void Reset() { fPhotonCount = 0; }

private:
    PhotonCounter() : fPhotonCount(0) {} // Constructor privado
    ~PhotonCounter() {}

    PhotonCounter(const PhotonCounter&) = delete;
    PhotonCounter& operator=(const PhotonCounter&) = delete;

    static PhotonCounter* fInstance;
    G4int fPhotonCount;
};

#endif
