
// Geant4 Libraries
//
#include "G4Material.hh"
#include "G4Element.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"

#include "G4Cons.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

// Local Libraries
//
//#include "PMTSD.hh"
#include "DetectorConstruction.hh"
#include "PMTSD.hh"
#include "G4SDManager.hh"



DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{
  G4cout << "...DetectorConstruction..." << G4endl;
  
  fExpHall_x = fExpHall_y = fExpHall_z = 200.0*cm;
  fTank_x    = fTank_y    = fTank_z    =  60.0*cm;
  
  O = H = C = NULL;
  water = glass = alum = NULL;
//    expHall_mat = glass = alum = NULL;

 // expHall_box = NULL;
  wcd_inferior = NULL;
  wcd_tank = wcd_thickness = NULL;
  Pmt = NULL;

  wcd_tank_log = Pmt_log = NULL;  
}


DetectorConstruction::~DetectorConstruction()
{}


// ****************************
// Doing Elements and Materials
// ****************************

void DetectorConstruction::DefineMaterials()
{

  // ----------------
  // *** Elements ***
  // ----------------
  G4double a, z, density;

  //N = new G4Element("Nitrogen", "N", z = 7 , a = 14.01*g/mole);
  C = new G4Element("Carbon"  , "C", z = 6 , a = 12.01*g/mole);
  O = new G4Element("Oxygen"  , "O", z = 8 , a = 16.00*g/mole);
  H = new G4Element("Hydrogen", "H", z=1 , a = 1.01*g/mole);


  // -----------------
  // *** Materials ***
  // -----------------
  G4NistManager* nist = G4NistManager::Instance();
  

  // *** Experimental Hall ***
  //  
  expHall_mat
    = nist->FindOrBuildMaterial("G4_AIR");

  // *** Water ***
  // 
  water 
    = new G4Material("Water", density= 1.0*g/cm3, 2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);

  // *** Tyvek ***
  //
  tyvek
    = new G4Material("Tyvek", density= 0.3571*g/cm3, 2); //Este material como tal es POLIETILENO
  tyvek->AddElement(H, 4);
  tyvek->AddElement(C, 2);
  
  // *** Glass ***
  //
  glass 
    = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

  // *** Aluminum ***
  //
  alum
    = nist->FindOrBuildMaterial("G4_Al");

  // *** Vacuum ***
  //
  vacuum 
    = new G4Material("vacuum", 
        z=1., 
        a=1.01*g/mole, 
        universe_mean_density,
        kStateGas,
        0.1*kelvin,
        1.e-19*pascal
        );

  
  // *** Hydroxyapatite Colloid ***
  //

  /*
  PO4 = 
    new G4Material("PO4", density = 1.000*g/cm3, 2);
  PO4->AddElement(nist->FindOrBuildMaterial("G4_P", 1));
  PO4->AddElement(nist->FindOrBuildMaterial("G4_O", 4));

  OH = 
    new G4Material("OH", density = 1.000*g/cm3, 2);
  OH->AddElement(nist->FindOrBuildMaterial("G4_O", 1));
  OH->AddElement(nist->FindOrBuildMaterial("G4_H", 1));

  Hydroxyapatite
    = new G4Material("Hydroxyapatite_colloid", density= 1.000*g/cm3, 3);
  Hydroxyapatite->AddElement(nist->FindOrBuildMaterial("G4_Ca", 10), 39.68*perCent);
  Hydroxyapatite->AddMaterial(PO4, 18*perCent);
  Hydroxyapatite->AddMaterial(OH, 42.32*perCent);

  Hydroxyapatite_colloid
    = new G4Material("Hydroxyapatite_colloid ", density = 1.000*g/cm3, 2);
  Hydroxyapatite_colloid->AddMaterial(water, 99.*perCent);
  Hydroxyapatite_colloid->AddMaterial(Hydroxyapatite, 0.1*perCent);
  */

 //PMT material
 PMTglass = nist->FindOrBuildMaterial("G4_Pyrex_Glass");


  // -------------------------
  // *** Water Propierties ***
  // -------------------------
  G4double photonEnergy[] =
  { 
    1.127*eV, 1.158*eV, 1.190*eV, 1.224*eV, 
    1.260*eV, 1.298*eV, 1.339*eV, 1.383*eV, 
    1.429*eV, 1.478*eV, 1.531*eV, 1.588*eV, 
    1.650*eV, 1.716*eV, 1.788*eV, 1.866*eV, 
    1.951*eV, 2.044*eV, 2.147*eV, 2.261*eV, 
    2.387*eV, 2.529*eV, 2.688*eV, 2.868*eV, 
    3.075*eV, 3.313*eV, 3.592*eV, 3.922*eV, 
    4.319*eV, 4.804*eV, 5.413*eV, 6.199*eV
  };
  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);


  G4double refractiveIndex1[] =
  { 
    1.32461554, 1.32506502, 1.32550999, 1.32595216,
    1.32639344, 1.32683587, 1.32728177, 1.32773371, 
    1.32819464, 1.32866791, 1.32915745, 1.32966784, 
    1.33020452, 1.330774, 1.33138419, 1.33204473, 
    1.33276761, 1.33356786, 1.33446457, 1.3354824,
    1.33665365, 1.33802145, 1.33964455, 1.34160493, 
    1.3440201,  1.3470643, 1.35100647, 1.35628372, 
    1.36365569, 1.37457069, 1.39219362, 1.42517179
  };
  assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));

  G4double absorption[] =
  {
    3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
    15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
    45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
    52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
    30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
    17.500*m, 14.500*m 
  };
  assert(sizeof(absorption) == sizeof(photonEnergy));


  G4MaterialPropertiesTable* myMPT1 
    = new G4MaterialPropertiesTable();

  myMPT1
    ->AddProperty("RINDEX", 
        photonEnergy, refractiveIndex1, nEntries)
    ->SetSpline(true);

  myMPT1
    ->AddProperty("ABSLENGTH", photonEnergy, 
        absorption, nEntries)
    ->SetSpline(true);


  G4double energy_water[] = 
  {
    1.56962*eV, 1.58974*eV, 1.61039*eV, 1.63157*eV,
    1.65333*eV, 1.67567*eV, 1.69863*eV, 1.72222*eV,
    1.74647*eV, 1.77142*eV, 1.7971 *eV, 1.82352*eV,
    1.85074*eV, 1.87878*eV, 1.90769*eV, 1.93749*eV,
    1.96825*eV, 1.99999*eV, 2.03278*eV, 2.06666*eV,
    2.10169*eV, 2.13793*eV, 2.17543*eV, 2.21428*eV,
    2.25454*eV, 2.29629*eV, 2.33962*eV, 2.38461*eV,
    2.43137*eV, 2.47999*eV, 2.53061*eV, 2.58333*eV,
    2.63829*eV, 2.69565*eV, 2.75555*eV, 2.81817*eV,
    2.88371*eV, 2.95237*eV, 3.02438*eV, 3.09999*eV,
    3.17948*eV, 3.26315*eV, 3.35134*eV, 3.44444*eV,
    3.54285*eV, 3.64705*eV, 3.75757*eV, 3.87499*eV,
    3.99999*eV, 4.13332*eV, 4.27585*eV, 4.42856*eV,
    4.59258*eV, 4.76922*eV, 4.95999*eV, 5.16665*eV,
    5.39129*eV, 5.63635*eV, 5.90475*eV, 6.19998*eV
  };
  const G4int numentries_water 
    = sizeof(energy_water)/sizeof(G4double);

  //assume 100 times larger than the rayleigh scattering for now.
  G4double mie_water[] = 
  {
     167024.4*m, 158726.7*m, 150742  *m,
     143062.5*m, 135680.2*m, 128587.4*m,
     121776.3*m, 115239.5*m, 108969.5*m,
     102958.8*m, 97200.35*m, 91686.86*m,
     86411.33*m, 81366.79*m, 76546.42*m,
     71943.46*m, 67551.29*m, 63363.36*m,
     59373.25*m, 55574.61*m, 51961.24*m,
     48527.00*m, 45265.87*m, 42171.94*m,
     39239.39*m, 36462.50*m, 33835.68*m,
     31353.41*m, 29010.30*m, 26801.03*m,
     24720.42*m, 22763.36*m, 20924.88*m,
     19200.07*m, 17584.16*m, 16072.45*m,
     14660.38*m, 13343.46*m, 12117.33*m,
     10977.70*m, 9920.416*m, 8941.407*m,
     8036.711*m, 7202.470*m, 6434.927*m,
     5730.429*m, 5085.425*m, 4496.467*m,
     3960.210*m, 3473.413*m, 3032.937*m,
     2635.746*m, 2278.907*m, 1959.588*m,
     1675.064*m, 1422.710*m, 1200.004*m,
     1004.528*m, 833.9666*m, 686.1063*m
  };
  assert(sizeof(mie_water) == sizeof(energy_water));

  // gforward, gbackward, forward backward ratio
  G4double mie_water_const[3]={0.99,0.99,0.8};

  myMPT1
    ->AddProperty("MIEHG",energy_water,mie_water,numentries_water)
    ->SetSpline(true);
  myMPT1
    ->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
  myMPT1
    ->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
  myMPT1
    ->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);

  G4cout << "Water G4MaterialPropertiesTable" << G4endl;
  myMPT1->DumpTable();

  water->SetMaterialPropertiesTable(myMPT1);

  // *** TiO2 Colloid ***
  //

  TiDioxide 
    = nist->FindOrBuildMaterial("G4_TITANIUM_DIOXIDE");
  
  TiO2_colloid
    = new G4Material("TiO2_colloid ", density = 1.002*g/cm3, 2);
  TiO2_colloid->AddMaterial(water, 95*perCent);
  TiO2_colloid->AddMaterial(TiDioxide, 5*perCent);

  // TiO2_colloid->AddMaterial(water, 99.93*perCent);
  // TiO2_colloid->AddMaterial(TiDioxide, 0.07*perCent);
  // -------------------------
  // *** TiO2 colloid Propierties ***
  // -------------------------
G4double photonEnergy_colloid[] =
{ 
  1.127*eV, 1.158*eV, 1.190*eV, 1.224*eV, 
  1.260*eV, 1.298*eV, 1.339*eV, 1.383*eV, 
  1.429*eV, 1.478*eV, 1.531*eV, 1.588*eV, 
  1.650*eV, 1.716*eV, 1.788*eV, 1.866*eV, 
  1.951*eV, 2.044*eV, 2.147*eV, 2.261*eV, 
  2.387*eV, 2.529*eV, 2.688*eV, 2.868*eV, 
  3.075*eV, 3.313*eV, 3.592*eV, 3.922*eV, 
  4.319*eV, 4.804*eV, 5.413*eV, 6.1*eV
};

const G4int nEntriesColloid = sizeof(photonEnergy_colloid)/sizeof(G4double);

G4double refractiveIndex_TiO2[] = 
{ 
    2.41659165, 2.41850779, 2.42054665, 2.42278136, 
    2.42522514, 2.42789224, 2.43087196, 2.43418914, 
    2.43779122, 2.44178145, 2.44627849, 2.45132907, 
    2.45708021, 2.46350448, 2.47087792, 2.47930913, 
    2.48904049, 2.50036329, 2.51376563, 2.52971256, 
    2.54878481, 2.57223532, 2.60117285, 2.63771768, 
    2.68537603, 2.74886801, 2.83772959, 2.96888536, 
    3.18003168, 3.57122366, 4.56502253, 12.32455899
};

 
  G4MaterialPropertiesTable* MPT_TiO2 
    = new G4MaterialPropertiesTable();

  MPT_TiO2
    ->AddProperty("RINDEX", 
        photonEnergy_colloid, refractiveIndex_TiO2, nEntriesColloid)
    ->SetSpline(true);

  MPT_TiO2->DumpTable();

  TiO2_colloid->SetMaterialPropertiesTable(MPT_TiO2);
}
  

// *************************
// Doing Mechanical Detector
// ************************* 

G4VPhysicalVolume* DetectorConstruction::Construct()
{                        

  

  // ----------------------
  // *** Make Materials ***
  // ----------------------
  DefineMaterials();

  // -------------------------
  // *** Experimental Hall ***
  // -------------------------
  G4bool checkOverlaps = true;

  expHall_box 
    = new G4Box("expHall",
        fExpHall_x,
        fExpHall_y,
        fExpHall_z
        );

  expHall_log
    = new G4LogicalVolume(expHall_box,
        expHall_mat,
        "expHall",
        0,
        0,
        0
        );

  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,
        G4ThreeVector(),
        expHall_log,
        "expHall",
        0,
        false,
        0,
        checkOverlaps
        );


  // --------------------
  // *** WCD Detector ***
  // --------------------

  // Tanque 250L
  R_sup = 88*0.5;
  R_inf = 58*0.5;
  h = 74;

  // R_sup = 88*0.5;
  // R_inf = 58*0.5;
  // h = 74;

  // Tanque 500L
  // R_sup = 108*0.5;
  // R_inf = 70*0.5;
  // h = 96;

  // Tanque 1000L
  // R_sup = 137*0.5;
  // R_inf = 90*0.5;
  // h = 125;



  // WCD Tank
  //

  wcd_thickness 
    = new G4Cons("wcdThickness",
    R_inf*cm - 0.1*cm, //Radio interno a
    R_inf*cm, //Radio externo a
    R_sup*cm - 0.1*cm, //Radio interno b
    R_sup*cm, //Radio externo b
    0.5*h*cm, //altura(mitad de la altura xq ya que asi es la manera como construye geant4)
    0.*deg, //inicio del angulo de barrio
    360.*deg); //angulo q barre
 

  // Crea una tabla de propiedades ópticas
  G4MaterialPropertiesTable* tyvekProperties = new G4MaterialPropertiesTable();
  // Define el rango de energías para las propiedades ópticas
  G4double energies_tyvek[2] = {1.5*eV, 6.2*eV};  // Rango de energía de los fotones ópticos
  // Índice de refracción del Tyvek
  G4double RI_Tyvek[2] = {1.5, 1.5};
  // G4double reflecitivty_tyvek[2]  = {0.8, 0.8};  // 80% de reflexión
  // Añade el índice de refracción a la tabla de propiedades
  tyvekProperties->AddProperty("RINDEX", energies_tyvek, RI_Tyvek, 2);
  // tyvekProperties->AddProperty("REFLECTIVITY", energies_tyvek, reflecitivty_tyvek, 2);
  // Asigna la tabla de propiedades ópticas al material de vidrio
  tyvek->SetMaterialPropertiesTable(tyvekProperties);

  wcd_thickness_log
    = new G4LogicalVolume(wcd_thickness,
        tyvek,
        "wcdThickness",
        0,
        0,
        0
        );

  G4VisAttributes* visAttributes_thick = new G4VisAttributes(G4Colour(0.0,1.0,0.0, 0.5));  // Azul para el agua
  visAttributes_thick->SetVisibility(true);
  visAttributes_thick->SetForceSolid(true); 
  wcd_thickness_log->SetVisAttributes(visAttributes_thick);
  
  G4VPhysicalVolume* wcd_thickness_phys
    = new G4PVPlacement(0,
        G4ThreeVector(),
        wcd_thickness_log,
        "wcdThickness",
        expHall_log,
        false,
        0,
        checkOverlaps
        );  
  
  wcd_inferior
    = new G4Tubs("wcdinferior",
        0.*cm,
        R_inf*cm,
        0.1*cm,
        0.*deg,
        360.*deg
        );
 
  wcd_inferior_log
    = new G4LogicalVolume(wcd_inferior,
        tyvek,//tyvek, 
        "wcdinferior",
        0,
        0,
        0
        ); 
  
  G4VPhysicalVolume* wcd_inferior_phys
    = new G4PVPlacement(0,
        G4ThreeVector(0.*m,0.*m, -0.5*h*cm),
        wcd_inferior_log,
        "wcdinferior",
        expHall_log,
        false,
        0,
        checkOverlaps
        );
        
  wcd_superior
    = new G4Tubs("wcdsuperior",
        0.*cm,
        R_sup*cm,
        0.1*cm,
        0.*deg,
        360.*deg
        );
 
  wcd_superior_log
    = new G4LogicalVolume(wcd_superior,
        tyvek,//expHall_mat,  //ESTE MATERIAL ES AIRE HAY QUE CAMBIARLO AL TYVEK
        "wcdsuperior",
        0,
        0,
        0
        ); 
  
  G4VPhysicalVolume* wcd_superior_phys
    = new G4PVPlacement(0,
        G4ThreeVector(0.*m,0.*m, 0.5*h*cm),
        wcd_superior_log,
        "wcdsuperior",
        expHall_log,
        false,
        0,
        checkOverlaps
        );

  wcd_tank 
    = new G4Cons("Tank",
    0.*cm, //Radio interno a
    R_inf*cm, //Radio externo a
    0.*cm, //Radio interno b
    R_sup*cm, //Radio externo b
    0.5*h*cm, //altura(mitad de la altura xq ya que asi es la manera como construye geant4)
    0.*deg, //inicio del angulo de barrio
    360.*deg); //angulo q barre

  wcd_tank_log //esta es el agua
    = new G4LogicalVolume(wcd_tank,
        TiO2_colloid, //TiO2_colloid, water
        "Tank",
        0,
        0,
        0
        ); 

  G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.0,0.0,1.0, 0.2));  // Azul para el agua
  visAttributes->SetVisibility(true);
  visAttributes->SetForceSolid(true); 
  wcd_tank_log->SetVisAttributes(visAttributes);

  G4VPhysicalVolume* wcd_tank_phys
    = new G4PVPlacement(0,
        G4ThreeVector(),
        wcd_tank_log,
        "Tank",
        expHall_log, //expHall_log,
        false,
        0,
        checkOverlaps
        );  

  fwaterVolume = wcd_tank_phys;

  // -------------------------- 
  // *** Optical Surfaces ***
  // --------------------------

  // *** For WCD ***
  //
  G4OpticalSurface* opWaterSurface 
    = new G4OpticalSurface("WaterSurface");

  opWaterSurface->SetType(dielectric_LUT);
  opWaterSurface->SetFinish(groundtyvekair);
  opWaterSurface->SetModel(LUT);

  // new G4LogicalBorderSurface("WaterSurface",
  //     wcd_tank_phys,
  //     wcd_thickness_phys, //expHall_phys, //wcd_thickness_phys,
  //     opWaterSurface
  //     );
   
  // // ----------------------------------------
  // // Generate & Add Material Properties Table 
  // // attached to the optical surfaces
  // // ----------------------------------------
  // const G4int num = 2;
  // G4double ephoton[num] = {2.034*eV, 4.136*eV};

  // // *** OpticalWaterSurface ***
  // //
  // G4double refractiveIndex[num] = {1.35, 1.40};
  // G4double specularLobe[num]    = {0.3, 0.3};
  // G4double specularSpike[num]   = {0.2, 0.2};
  // G4double backScatter[num]     = {0.2, 0.2};

const G4int num = 10;  // Aumentar el número de puntos de energía
G4double ephoton[num] = {1.0*eV, 2.0*eV, 2.5*eV, 3.0*eV, 3.5*eV, 4.0*eV, 4.5*eV, 5.0*eV, 5.5*eV, 6.0*eV};

// Coeficientes de reflexión
G4double ref = 0.8;
G4double abs = 1-ref;
G4double reflectivity[num]  = {ref, ref, ref, ref, ref, ref, ref, ref, ref, ref};  // 80% de reflexión
G4double absorption[num] = {abs, abs, abs, abs, abs, abs, abs, abs, abs, abs}; // 20% de absorción
G4double specularLobe[num]  = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05}; // Reflexión especular baja
G4double specularSpike[num] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Sin especularidad
G4double backScatter[num]   = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05}; // Backscatter leve
G4double refractiveIndex[num]  = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5}; // refractive index tyvek?


  G4MaterialPropertiesTable* myST1 
    = new G4MaterialPropertiesTable();

  myST1->AddProperty("RINDEX", ephoton, refractiveIndex, num);
  myST1->AddProperty("REFLECTIVITY", ephoton, reflectivity, num);
  myST1->AddProperty("SPECULARLOBECONSTANT", ephoton, specularLobe, num);
  myST1->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike, num);
  myST1->AddProperty("BACKSCATTERCONSTANT", ephoton, backScatter, num);

  G4cout << "Water Surface G4MaterialPropertiesTable" << G4endl;
  myST1->DumpTable();

  opWaterSurface->SetMaterialPropertiesTable(myST1);

  new G4LogicalBorderSurface("ReflectivePaintSurface", 
                           wcd_tank_phys, 
                           wcd_thickness_phys, 
                           opWaterSurface);

  new G4LogicalBorderSurface("ReflectivePaintSurface", 
                           wcd_tank_phys, 
                           wcd_inferior_phys, 
                           opWaterSurface);


  // Define una nueva superficie óptica para la pintura reflectiva
// G4OpticalSurface* opReflectivePaintSurface 
//     = new G4OpticalSurface("ReflectivePaintSurface");

// // Configura el tipo de superficie y su acabado difuso
// opReflectivePaintSurface->SetType(dielectric_dielectric);  // Para una interfaz entre dieléctricos
// opReflectivePaintSurface->SetFinish(ground);               // Superficie rugosa, difusa
// opReflectivePaintSurface->SetModel(unified);               // Modelo óptico general

// // Define las propiedades ópticas
// const G4int num = 10;  // Aumentar el número de puntos de energía
// G4double ephoton[num] = {1.0*eV, 2.0*eV, 2.5*eV, 3.0*eV, 3.5*eV, 4.0*eV, 4.5*eV, 5.0*eV, 5.5*eV, 6.0*eV};

// // Coeficientes de reflexión
// G4double reflectivity[num]  = {0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8};  // 80% de reflexión
// G4double specularLobe[num]  = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05}; // Reflexión especular baja
// G4double specularSpike[num] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Sin especularidad
// G4double backScatter[num]   = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05}; // Backscatter leve
// G4double refractiveIndex[num]  = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};  // 80% de reflexión

// // Crear tabla de propiedades para la superficie
// G4MaterialPropertiesTable* reflectivePaintMPT = new G4MaterialPropertiesTable();
// reflectivePaintMPT->AddProperty("REFLECTIVITY", ephoton, reflectivity, num);
// reflectivePaintMPT->AddProperty("SPECULARLOBECONSTANT", ephoton, specularLobe, num);
// reflectivePaintMPT->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike, num);
// reflectivePaintMPT->AddProperty("BACKSCATTERCONSTANT", ephoton, backScatter, num);
// reflectivePaintMPT->AddProperty("RINDEX", ephoton, refractiveIndex, num);
// // Asigna la tabla de propiedades a la superficie óptica
// opReflectivePaintSurface->SetMaterialPropertiesTable(reflectivePaintMPT);
// reflectivePaintMPT->DumpTable();

// new G4LogicalBorderSurface("ReflectivePaintSurface", 
//                            wcd_tank_phys, 
//                            wcd_thickness_phys, 
//                            opReflectivePaintSurface);

// new G4LogicalSkinSurface("ReflectiveSkinSurface",wcd_tank_log, opReflectivePaintSurface);
  // -----------
  // *** PMT ***
  // -----------


  //PMT material
  //
  
  // Crea una tabla de propiedades ópticas
  G4MaterialPropertiesTable* mptGlass = new G4MaterialPropertiesTable();
  // Define el rango de energías para las propiedades ópticas
  G4double energies[2] = {1.5*eV, 6.2*eV};  // Rango de energía de los fotones ópticos
  // Índice de refracción del vidrio (Pyrex ~1.49)
  G4double RI_PMTglass[2] = {1.49, 1.49};
  // Añade el índice de refracción a la tabla de propiedades
  mptGlass->AddProperty("RINDEX", energies, RI_PMTglass, 2);
  // Asigna la tabla de propiedades ópticas al material de vidrio
  PMTglass->SetMaterialPropertiesTable(mptGlass);

  G4double innerRadius_pmt = 0.*cm;
  G4double outerRadius_pmt = 0.5*5.1*cm;
  G4double height_pmt = 0.6*cm;//0.0635/2.*cm; 
  G4double startAngle_pmt = 0.*deg;
  G4double spanningAngle_pmt = 360.*deg;

  // G4double pxSemiAxis = 10.1*cm;
  // G4double pySemiAxis = 10.1*cm;
  // G4double pzSemiAxis = 6.5*cm;
  // G4double pzBottomCut = -pzSemiAxis;
  // G4double pzTopCut = 0.*cm;

  Pmt
    = new G4Tubs("pmt_tube",
        innerRadius_pmt,
        outerRadius_pmt,
        height_pmt,
        startAngle_pmt,
        spanningAngle_pmt
        );

  // Pmt 
  //   = new G4Ellipsoid("pmt_tube",
  //   pxSemiAxis,
  //   pySemiAxis,
  //   pzSemiAxis,
  //   pzBottomCut,
  //   pzTopCut
  //   );

  Pmt_log
    = new G4LogicalVolume(Pmt
        ,PMTglass,
        "pmt_tube"
        );

 G4VPhysicalVolume* PmtPhys
    = new G4PVPlacement(0,
      G4ThreeVector(0., 0., 0.5*h*cm - height_pmt*cm),//295.*cm),//60.*cm), //posicion del pmt
      Pmt_log,
      "pmt_tube",
      //expHall_log,
      wcd_tank_log,
      false,
      0,
      checkOverlaps
      );


  //Optical surface PMT-Water

  G4OpticalSurface* OS_PMT_Water = new G4OpticalSurface("OpticalSurface");

  OS_PMT_Water->SetType(dielectric_dielectric);
  OS_PMT_Water->SetFinish(polished);
  OS_PMT_Water->SetModel(glisur);

  // Añadir propiedades a la superficie
  G4MaterialPropertiesTable* mptSurface = new G4MaterialPropertiesTable();
  G4double reflectivityPMT[] = {0.1, 0.1};
  mptSurface->AddProperty("REFLECTIVITY", energies, reflectivityPMT, num);
  OS_PMT_Water->SetMaterialPropertiesTable(mptSurface);

  new G4LogicalBorderSurface("Surface", wcd_tank_phys, PmtPhys, OS_PMT_Water);


  // Asignar el detector sensible al PMT
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  auto* pmtSD = new PMTSD("PmtSD");
  sdManager->AddNewDetector(pmtSD);
  Pmt_log->SetSensitiveDetector(pmtSD);

  // *** PMT optical surface ***
  //
  //G4OpticalSurface* opPMTsurface 
  //  = new G4OpticalSurface("PMTsurface");

  //..............Revisar.................
  //opPMTsurface->SetType(dielectric_LUT); 
  //opPMTsurface->SetFinish(polished);
  //opPMTsurface->SetModel(LUT);
  //......................................

  //new G4LogicalSkinSurface("PMTsurface", Pmt_log, opPMTsurface );


  return expHall_phys;
}
