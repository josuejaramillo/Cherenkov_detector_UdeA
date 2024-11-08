#ifndef UserEventAction_h 
#define UserEventAction_h 1


// Geant4 Libraries
//
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "PhotonCounter.hh"
#include "G4RunManager.hh"
#include "g4root.hh"

// Local Libraries
//


//class G4Event;

// Standard Libraries
//
#include <fstream>
#include <cmath>


class UserEventAction : public G4UserEventAction
{
  public:
    UserEventAction(std::ofstream& output);
    virtual ~UserEventAction();

    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
    void AddPhotonCount() { fPhotonCount++; } //Contador de fotones PMT
    int GetPhotonCount(){return fPhotonCount++;}
    
    void AddPhotonEnergy(G4double energy) {fTotalPhotonEnergy += energy;}
    static G4int GetEventId() { return fEventId; }
  private:
    std::ofstream& outFile;  // Referencia al archivo
    G4int fPhotonCount;
    G4double fTotalPhotonEnergy;
    static G4int fEventId; 
};

#endif

