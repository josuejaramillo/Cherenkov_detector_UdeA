#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "G4Types.hh" 
#include <vector>

class TrackingAction : public G4UserTrackingAction 
{
public:
    // Constructor
    TrackingAction();
    virtual ~TrackingAction();
    // Método llamado antes de realizar la acción de seguimiento
    virtual void PreUserTrackingAction(const G4Track* track) override;


private:
    // Puedes agregar variables privadas si es necesario, como el ID del fotón que deseas visualizar
    G4int fPhotonID; // ID del fotón a visualizar
    std::vector<G4int> fPhotonIDs;
};

#endif // MyTrackingAction_h