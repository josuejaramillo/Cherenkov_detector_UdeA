#include "DetectorConstruction.hh"
#include "PMTSD.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include <algorithm>
#include <vector>

// ===============================================================
// Constructor
// ===============================================================

DetectorConstruction::DetectorConstruction(G4String mediumChoice, G4double TiO2conc)
 : G4VUserDetectorConstruction(),
   fMediumChoice(mediumChoice),
   fTiO2conc(TiO2conc)
{
    G4cout << ">>> Building DetectorConstruction with medium = " << fMediumChoice
           << ", TiO2 concentration = " << fTiO2conc << "%" << G4endl;

    fExpHall_x = fExpHall_y = 200.0*cm; 
    fExpHall_z = 200.0*cm;
    fTank_x = fTank_y = fTank_z = 60.0*cm;
}

DetectorConstruction::~DetectorConstruction() {}

// ===============================================================
// Define Materials
// ===============================================================

void DetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();

    G4Element* H  = nist->FindOrBuildElement("H");
    G4Element* O  = nist->FindOrBuildElement("O");
    G4Element* C  = nist->FindOrBuildElement("C");
    G4Element* Ti = nist->FindOrBuildElement("Ti");

    // -----------------------------------------------------------
    // Base materials
    // -----------------------------------------------------------
    expHall_mat = nist->FindOrBuildMaterial("G4_AIR");
    glass       = nist->FindOrBuildMaterial("G4_Pyrex_Glass");
    alum        = nist->FindOrBuildMaterial("G4_Al");
    TiDioxide   = nist->FindOrBuildMaterial("G4_TITANIUM_DIOXIDE");

    // Water
    water = new G4Material("Water", 1.0*g/cm3, 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);

    // Reflective paint
    whitePaint = new G4Material("WhitePaintMix", 1.5*g/cm3, 3);
    whitePaint->AddElement(Ti, 0.10);
    whitePaint->AddElement(O, 0.20);
    whitePaint->AddElement(C, 0.70);

    // Vacuum
    vacuum = new G4Material("Vacuum", 1., 1.01*g/mole, universe_mean_density,
                            kStateGas, 0.1*kelvin, 1.e-19*pascal);

    // -----------------------------------------------------------
    // Optical properties for water (absorption, Rayleigh scattering, refractive index)
    // -----------------------------------------------------------
    const G4int nEntries = 32;
    G4double photonEnergy[nEntries] =
    {1.127,1.158,1.190,1.224,1.260,1.298,1.339,1.383,
    1.429,1.478,1.531,1.588,1.650,1.716,1.788,1.866,
    1.951,2.044,2.147,2.261,2.387,2.529,2.688,2.868,
    3.075,3.313,3.592,3.922,4.319,4.804,5.413,6.199};
    for (int i=0;i<nEntries;i++) photonEnergy[i]*=eV;

    // --- Absorption length
    G4double absorption[nEntries] = {
    0.014*m, 0.016*m, 0.019*m, 0.024*m, 0.024*m, 0.025*m, 0.063*m, 0.150*m,
    0.190*m, 0.271*m, 0.434*m, 0.437*m, 0.385*m, 0.662*m, 1.795*m, 2.657*m,
    3.375*m, 4.115*m, 10.358*m, 22.652*m, 33.008*m, 40.019*m, 37.455*m, 28.337*m,
    18.017*m, 8.370*m, 3.770*m, 1.998*m, 1.153*m, 0.681*m, 0.393*m, 0.145*m
    };

    // --- Refractive index
    G4double refractiveIndex1[nEntries] = {
    1.32548669,1.32592875,1.32636092,1.32679534,1.32700000,1.32700000,1.32793651,1.32800000,
    1.32827081,1.32900000,1.32900000,1.32974810,1.33000000,1.33007925,1.33100000,1.33100000,
    1.33156278,1.33200000,1.33288495,1.33305041,1.33420904,1.33537643,1.33653720,1.33769595,
    1.33886081,1.34104044,1.34355121,1.34703875,1.35154687,1.35935552,1.37114869,1.39586638
    };

    // --- Rayleigh scattering length
    G4double rayleigh_water[32] = {
    35.*m, 38.*m, 41.*m, 44.*m, 47.*m, 50.*m, 55.*m, 60.*m,
    65.*m, 70.*m, 75.*m, 80.*m, 85.*m, 90.*m, 95.*m, 100.*m,
    110.*m, 120.*m, 130.*m, 140.*m, 160.*m, 180.*m, 200.*m, 220.*m,
    240.*m, 260.*m, 280.*m, 300.*m, 320.*m, 340.*m, 360.*m, 380.*m
    };

    // --- Material Properties Table ---
    G4MaterialPropertiesTable* mptWater = new G4MaterialPropertiesTable();
    mptWater->AddProperty("RINDEX", photonEnergy, refractiveIndex1, nEntries);
    mptWater->AddProperty("ABSLENGTH", photonEnergy, absorption, nEntries);
    mptWater->AddProperty("RAYLEIGH", photonEnergy, rayleigh_water, nEntries);

    water->SetMaterialPropertiesTable(mptWater);

    // -----------------------------------------------------------
    // TiO2 colloid with precise refractive indices + absorption + Mie
    // -----------------------------------------------------------
    G4double wtTiO2  = fTiO2conc * perCent;
    G4double wtWater = 1.0 - wtTiO2;
    const G4double rhoWater = 1.0*g/cm3;
    const G4double rhoTiO2  = 4.23*g/cm3;
    G4double rhoMix = 1.0 / (wtWater/rhoWater + wtTiO2/rhoTiO2);

    TiO2_colloid = new G4Material("TiO2_colloid", rhoMix, 2);
    TiO2_colloid->AddMaterial(water, wtWater);
    TiO2_colloid->AddMaterial(TiDioxide, wtTiO2);

    G4double refractiveIndex_TiO2[nEntries];
    if (fTiO2conc = 5) {
        G4double tmp[] =  {1.36327440,1.36377508,1.36426929,1.36477170,1.36505665,1.36514909,1.36616296,1.36633734, 
        1.36672231,1.36756586,1.36771522,1.36861099,1.36904621,1.36933505,1.37047538,1.37075354, 
        1.37162505,1.37242922,1.37374415,1.37445023,1.37624504,1.37822290,1.38042985,1.38299395, 
        1.38617939,1.39155282,1.39972318,1.40977407,1.41780120,1.42161419,1.42168116,1.43495869};
        std::copy(tmp, tmp+nEntries, refractiveIndex_TiO2);
    } else if (fTiO2conc == 10) {
        G4double tmp[] = {1.401,1.402,1.403,1.403,1.404,1.405,1.406,1.407,
                          1.408,1.409,1.410,1.411,1.412,1.413,1.414,1.415,
                          1.416,1.417,1.418,1.419,1.420,1.422,1.424,1.426,
                          1.428,1.430,1.432,1.434,1.436,1.438,1.440,1.442};
        std::copy(tmp, tmp+nEntries, refractiveIndex_TiO2);
    } else if (fTiO2conc == 20) {
        G4double tmp[] = {1.479,1.480,1.481,1.482,1.483,1.484,1.485,1.486,
                          1.487,1.488,1.489,1.490,1.491,1.492,1.493,1.494,
                          1.495,1.496,1.497,1.498,1.499,1.500,1.501,1.502,
                          1.503,1.504,1.505,1.506,1.507,1.508,1.509,1.510};
        std::copy(tmp, tmp+nEntries, refractiveIndex_TiO2);
    } else if (fTiO2conc == 30) {
        G4double tmp[] = {1.559,1.560,1.561,1.562,1.563,1.564,1.565,1.566,
                          1.567,1.568,1.569,1.570,1.571,1.572,1.573,1.574,
                          1.575,1.576,1.577,1.578,1.579,1.580,1.581,1.582,
                          1.583,1.584,1.585,1.586,1.587,1.588,1.589,1.590};
        std::copy(tmp, tmp+nEntries, refractiveIndex_TiO2);
    } else {
        G4Exception("DetectorConstruction::DefineMaterials()", "InvalidConc", FatalException,
                    "Invalid TiO2 concentration. Use 0.01, 10, 20, or 30 (%).");
    }

    // --- Absorption & Mie arrays (shared across all concentrations)
    G4double absorption_TiO2[32] = {
      50.*m,48.*m,45.*m,40.*m,35.*m,30.*m,20.*m,10.*m,
      5.*m,3.*m,1.*m,0.8*m,0.6*m,0.5*m,0.4*m,0.3*m,
      0.25*m,0.20*m,0.15*m,0.12*m,0.10*m,0.08*m,0.06*m,0.05*m,
      0.04*m,0.03*m,0.025*m,0.020*m,0.015*m,0.010*m,0.008*m,0.005*m
    };

    G4double mie_TiO2[32] = {
      0.5*m,0.45*m,0.40*m,0.35*m,0.30*m,0.28*m,0.25*m,0.20*m,
      0.18*m,0.16*m,0.14*m,0.13*m,0.12*m,0.11*m,0.10*m,0.095*m,
      0.090*m,0.085*m,0.080*m,0.075*m,0.07*m,0.065*m,0.060*m,0.055*m,
      0.050*m,0.045*m,0.042*m,0.038*m,0.035*m,0.030*m,0.028*m,0.025*m
    };

    G4MaterialPropertiesTable* MPT_TiO2 = new G4MaterialPropertiesTable();
    MPT_TiO2->AddProperty("RINDEX", photonEnergy, refractiveIndex_TiO2, nEntries);
    MPT_TiO2->AddProperty("ABSLENGTH", photonEnergy, absorption_TiO2, nEntries);
    MPT_TiO2->AddProperty("MIEHG", photonEnergy, mie_TiO2, nEntries);
    MPT_TiO2->AddConstProperty("MIEHG_FORWARD", 0.9);
    MPT_TiO2->AddConstProperty("MIEHG_BACKWARD", 0.9);
    MPT_TiO2->AddConstProperty("MIEHG_FORWARD_RATIO", 0.8);
    TiO2_colloid->SetMaterialPropertiesTable(MPT_TiO2);

    // -----------------------------------------------------------
    // Glycerine (with Rayleigh scattering instead of Mie)
    // -----------------------------------------------------------
    G4Material* glycerine = new G4Material("Glycerine", 1.26*g/cm3, 3);
    glycerine->AddElement(C, 3);
    glycerine->AddElement(H, 8);
    glycerine->AddElement(O, 3);

    // --- Optical properties ---
    G4double absorption_gly[32] = {
    30.*m,35.*m,40.*m,45.*m,50.*m,55.*m,60.*m,65.*m,
    70.*m,75.*m,80.*m,85.*m,90.*m,95.*m,100.*m,105.*m,
    110.*m,115.*m,120.*m,125.*m,130.*m,135.*m,140.*m,145.*m,
    150.*m,155.*m,160.*m,165.*m,170.*m,175.*m,180.*m,185.*m
    };

    G4double rayleigh_gly[32]; // very long scattering lengths (almost negligible)
    for (int i = 0; i < 32; i++) rayleigh_gly[i] = 2000.*m;  // 2 km constant

    G4double refrGly[32] = {
    1.46,1.4605,1.4610,1.4615,1.4620,1.4625,1.4630,1.4635,
    1.4640,1.4645,1.4650,1.4655,1.4660,1.4665,1.4670,1.4675,
    1.4680,1.4685,1.4690,1.4695,1.4700,1.4705,1.4710,1.4715,
    1.4720,1.4725,1.4730,1.4735,1.4740,1.4745,1.4750,1.4755
    };

    // --- Build Material Properties Table ---
    G4MaterialPropertiesTable* mptGly = new G4MaterialPropertiesTable();
    mptGly->AddProperty("RINDEX", photonEnergy, refrGly, nEntries);
    mptGly->AddProperty("ABSLENGTH", photonEnergy, absorption_gly, nEntries);
    mptGly->AddProperty("RAYLEIGH", photonEnergy, rayleigh_gly, nEntries);

    glycerine->SetMaterialPropertiesTable(mptGly);

    fGlycerine = glycerine;

    // -----------------------------------------------------------
    // Log output
    // -----------------------------------------------------------
    G4cout << ">>> Media defined: Water, TiO2 colloid, and Glycerine." << G4endl;
    G4cout << ">>> Selected medium: " << fMediumChoice;
    if (fMediumChoice == "TiO2" || fMediumChoice == "TiO2_colloid")
        G4cout << " | TiO2 conc: " << fTiO2conc << " %";
    G4cout << G4endl;
}

// ===============================================================
// Construct Geometry
// ===============================================================

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    DefineMaterials();
    G4bool checkOverlaps = true;

    expHall_log = new G4LogicalVolume(new G4Box("expHall", fExpHall_x, fExpHall_y, fExpHall_z),
                                      expHall_mat, "expHall");
    G4VPhysicalVolume* expHall_phys =
        new G4PVPlacement(0, {}, expHall_log, "expHall", 0, false, 0, checkOverlaps);

    R_sup = 25.8*0.5;
    R_inf = 25.8*0.5;
    h     = 39.4;

    // --- Select medium ---
    G4Material* innerMaterial = nullptr;
    if (fMediumChoice == "Water") {
        innerMaterial = water;
    } else if (fMediumChoice == "TiO2") {
        innerMaterial = TiO2_colloid;
    } else if (fMediumChoice == "Glycerine") {
        innerMaterial = fGlycerine;
    } else {
        G4Exception("DetectorConstruction::Construct()", "InvalidMedium", FatalException,
                    "Unknown medium choice. Use 'Water', 'TiO2', or 'Glycerine'.");
    }

    // --- Tank with selected medium ---
    auto wcd_tank = new G4Cons("Tank", 0., R_inf*cm, 0., R_sup*cm, 0.5*h*cm, 0., 360.*deg);
    wcd_tank_log = new G4LogicalVolume(wcd_tank, innerMaterial, "Tank");
    auto wcd_tank_phys = new G4PVPlacement(0, {}, wcd_tank_log, "Tank", expHall_log, false, 0, checkOverlaps);

    // --- Reflective paint surfaces ---
    auto wcd_thickness = new G4Cons("wcdThickness", R_inf*cm-0.1*cm, R_inf*cm,
                                    R_sup*cm-0.1*cm, R_sup*cm, 0.5*h*cm, 0., 360.*deg);
    wcd_thickness_log = new G4LogicalVolume(wcd_thickness, whitePaint, "wcdThickness");
    new G4PVPlacement(0, {}, wcd_thickness_log, "wcdThickness", wcd_tank_log, false, 0, checkOverlaps);

    auto wcd_inferior = new G4Tubs("wcdinferior", 0., R_inf*cm, 0.1*cm, 0., 360.*deg);
    wcd_inferior_log = new G4LogicalVolume(wcd_inferior, whitePaint, "wcdinferior");
    new G4PVPlacement(0, G4ThreeVector(0,0,-0.5*h*cm), wcd_inferior_log, "wcdinferior", wcd_tank_log, false, 0, checkOverlaps);

    auto wcd_superior = new G4Tubs("wcdsuperior", 0., R_sup*cm, 0.1*cm, 0., 360.*deg);
    wcd_superior_log = new G4LogicalVolume(wcd_superior, whitePaint, "wcdsuperior");
    new G4PVPlacement(0, G4ThreeVector(0,0,0.5*h*cm), wcd_superior_log, "wcdsuperior", wcd_tank_log, false, 0, checkOverlaps);

    // --- Reflective optical skin ---
    G4OpticalSurface* opWaterSurface = new G4OpticalSurface("WaterSurface");
    opWaterSurface->SetType(dielectric_metal);
    opWaterSurface->SetFinish(groundfrontpainted);
    opWaterSurface->SetModel(unified);

    const G4int num = 32;
    G4double ephoton[num];
    for (int i=0;i<num;i++) ephoton[i]=1.127*eV + i*(5.072/31)*eV;

    G4double reflectivity[num]; std::fill_n(reflectivity, num, 0.95);
    G4double refractiveIndex[num]; std::fill_n(refractiveIndex, num, 2.5);
    G4MaterialPropertiesTable* mptWhitePaint = new G4MaterialPropertiesTable();
    mptWhitePaint->AddProperty("REFLECTIVITY", ephoton, reflectivity, num);
    mptWhitePaint->AddProperty("RINDEX", ephoton, refractiveIndex, num);
    opWaterSurface->SetMaterialPropertiesTable(mptWhitePaint);

    new G4LogicalSkinSurface("WhitePaintSkin_Thick", wcd_thickness_log, opWaterSurface);
    new G4LogicalSkinSurface("WhitePaintSkin_Bottom", wcd_inferior_log, opWaterSurface);
    new G4LogicalSkinSurface("WhitePaintSkin_Top", wcd_superior_log, opWaterSurface);

    // --- Photon detection modules ---
    G4Material* moduleMat = glass;
    G4MaterialPropertiesTable* mptModule = new G4MaterialPropertiesTable();
    G4double energies[2] = {1.5*eV, 6.2*eV};
    G4double RI_module[2] = {1.49, 1.49};
    mptModule->AddProperty("RINDEX", energies, RI_module, 2);
    moduleMat->SetMaterialPropertiesTable(mptModule);

    G4double module_side = 6.5*mm, module_thickness = 1.0*mm, spacing = 18.5*mm;
    auto moduleSolid = new G4Box("Module", module_side/2., module_side/2., module_thickness/2.);
    auto moduleLog = new G4LogicalVolume(moduleSolid, moduleMat, "Module");

    G4double zPos = 0.5*h*cm - module_thickness/2.;
    for (int i=0;i<2;i++)
        for (int j=0;j<2;j++)
            new G4PVPlacement(0, G4ThreeVector((i-0.5)*spacing, (j-0.5)*spacing, zPos),
                              moduleLog, "Module", wcd_tank_log, false, i*2+j, checkOverlaps);

    // --- Sensitive detector ---
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    auto* moduleSD = new PMTSD("ModuleSD");
    sdManager->AddNewDetector(moduleSD);
    moduleLog->SetSensitiveDetector(moduleSD);

    return expHall_phys;
}
