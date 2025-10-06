#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Material.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction(G4String mediumChoice = "Water", G4double TiO2conc = 0.0);
    virtual ~DetectorConstruction();
    inline G4VPhysicalVolume* GetWaterVolume() const { return fwaterVolume; }
    virtual G4VPhysicalVolume* Construct();
    void SetMedium(G4String medium);

private:
    void DefineMaterials();

    // --- user-selectable parameters ---
    G4String fMediumChoice;   // "Water" or "TiO2"
    G4double fTiO2conc;       // 0.01, 10, 20, 30 %

    // --- geometry and materials ---
    G4Material* water;
    G4Material* TiO2_colloid;
    G4Material* TiDioxide;
    G4Material* whitePaint;
    G4Material* fWater;
    G4Material* fColloid;
    G4Material* fGlycerine;
    G4Material* glass;
    G4Material* alum;
    G4Material* expHall_mat;
    G4Material* vacuum;

    G4LogicalVolume* expHall_log;
    G4LogicalVolume* wcd_tank_log;
    G4LogicalVolume* wcd_thickness_log;
    G4LogicalVolume* wcd_inferior_log;
    G4LogicalVolume* wcd_superior_log;
    G4LogicalVolume* Pmt_log;

    G4VPhysicalVolume* fwaterVolume;

    // geometry dimensions
    G4double fExpHall_x, fExpHall_y, fExpHall_z;
    G4double fTank_x, fTank_y, fTank_z;
    G4double R_sup, R_inf, h;
};

#endif
