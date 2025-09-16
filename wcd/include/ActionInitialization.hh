#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include <string>
#include <map>

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(const std::string& nombreArchivo,
                         const std::map<std::string,int>& counts);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const override;
    virtual void Build() const override;

    virtual G4VSteppingVerbose* InitializeSteppingVerbose() const override;

  private:
    std::string fNombreArchivoSalida;
    int fSeed;
    std::map<std::string,int> fCounts;  // << NEW
};

#endif
