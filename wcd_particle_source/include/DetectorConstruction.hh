#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1


// Geant4 Libraries
//
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Cache.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Ellipsoid.hh"
#include "G4Tubs.hh"
#include "G4OpticalSurface.hh"
#include "G4Cons.hh"

// Local Libraries
//
//#include "PMTSD.hh"

class G4LogicalVolume; 


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    
    G4VPhysicalVolume* GetWaterVolume() const 
    {
       return fwaterVolume;
    }

    double getVolume() const {
      const double volume = 3.14159265*h*( R_sup*R_sup + R_inf*R_inf + R_inf*R_sup) / 3.0;
      return volume;
    }


  private:

    void DefineMaterials();

    // ----------------
    // *** Elements ***
    // ----------------
    //G4Element* N;
    G4Element* O;
    G4Element* H;
    G4Element* C;

    // -----------------
    // *** Materials ***
    //------------------
    G4Material* water;
    G4Material* expHall_mat;  
    G4Material* glass;
    G4Material* alum;
    G4Material* vacuum;
    G4Material* tyvek;
    G4Material* PMTglass;

    G4Material* TiDioxide;
    G4Material* TiO2_colloid;

    G4Material* PO4;
    G4Material* OH;
    G4Material* Hydroxyapatite;
    G4Material* Hydroxyapatite_colloid;

    // -----------------
    // *** Detectors ***
    // -----------------

    // *** Geometry ***
    //
    G4Box* expHall_box;
    G4Cons* wcd_tank;
    //G4Box* wcd_tank;
    G4Cons* wcd_thickness;
    //G4Tubs* wcd_thickness;
    G4Tubs* wcd_inferior;
    G4Tubs* wcd_superior;
    //G4Box* wcd_thickness;
    //G4Ellipsoid* Pmt;
    G4Tubs* Pmt;
  
    // *** Logical Volume ***
    //
    G4LogicalVolume* expHall_log;
    G4LogicalVolume* wcd_tank_log;
    G4LogicalVolume* wcd_thickness_log;
    G4LogicalVolume* wcd_inferior_log;
    G4LogicalVolume* wcd_superior_log;
    G4LogicalVolume* Pmt_log;


    G4double fExpHall_x;
    G4double fExpHall_y;
    G4double fExpHall_z;

    G4double fTank_x;
    G4double fTank_y;
    G4double fTank_z;

    // *** Physical Volume ***
    //
    G4VPhysicalVolume* fwaterVolume;
    G4VPhysicalVolume* fPMTVolume;


  // Tank
  
  double R_sup;
  double R_inf;
  double h;

};

#endif