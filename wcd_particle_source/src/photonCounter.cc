#include "PhotonCounter.hh"

PhotonCounter* PhotonCounter::fInstance = nullptr;

PhotonCounter* PhotonCounter::Instance() {
    if (!fInstance) {
        fInstance = new PhotonCounter();
    }
    return fInstance;
}
