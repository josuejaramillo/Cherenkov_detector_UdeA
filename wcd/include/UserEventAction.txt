#ifndef UserEventAction_h 
#define UserEventAction_h 1


// Geant4 Libraries
//
#include "G4UserEventAction.hh"
#include "G4Event.hh"


// Local Libraries
//


//class G4Event;


class UserEventAction : public G4UserEventAction
{
  public:
    UserEventAction();
    virtual ~UserEventAction();

    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);

};

#endif

