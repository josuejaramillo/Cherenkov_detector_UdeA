#ifndef PrimaryGeneratorAction_Ascii_h
#define PrimaryGeneratorAction_Ascii_h 1
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4HEPEvtInterface.hh"
class G4Event;
class G4VPrimaryGenerator;
//class G4HEPEvtInterface;
class PrimaryGeneratorAction_Ascii : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction_Ascii();
  ~PrimaryGeneratorAction_Ascii();
  void GeneratePrimaries(G4Event* anEvent);

private:
G4VPrimaryGenerator* HEPEvt;

};

#endif
