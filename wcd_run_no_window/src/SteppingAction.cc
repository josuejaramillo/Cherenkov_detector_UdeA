// Geant4 Libraries
//
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "g4root.hh"
#include "G4SDManager.hh"
#include "G4TransportationManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4UserEventAction.hh"
#include "G4Event.hh"


// Local Libraries
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "PMTSD.hh"
// #include "PMTHit.hh"
#include "UserEventAction.hh"

SteppingAction::SteppingAction()
  : G4UserSteppingAction()
{
  //G4cout << "...SteppingAction..." << G4endl; 
  G4TransportationManager::GetTransportationManager()
    ->GetNavigatorForTracking()->SetPushVerbosity(0);
  
  fScintillationCounter = 0;
  fCerenkovCounter      = 0;
  lengthMaxOk = 0;
  fEventNumber = -1;
  // pmtSD = new PMTSD;
  phoOnPmt = 0;
  alpmt = 0;
  water_in = 0.;
  water_out = 0.;
  water_died = 0.;
  priEner = 0.;
  //tiempo = 0.;
  
  detectorConstruction 
     = static_cast < const DetectorConstruction* 
     > (G4RunManager::GetRunManager()
         ->GetUserDetectorConstruction());
}

SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{

  // ==========================
  // Get current PhysicalVolume
  G4VPhysicalVolume *thePostPV
    = step->GetPostStepPoint()->GetPhysicalVolume();

  G4VPhysicalVolume *thePrePV
    = step->GetPreStepPoint()->GetPhysicalVolume();
 
  // ==========================
  // Get Track
  G4Track* track = step->GetTrack();

  // ============
  // Get Event Id
  G4int eventNumber                
    = G4RunManager::GetRunManager()
    ->GetCurrentEvent()
    ->GetEventID();
  
  // ============
  // Get Particle Name
  G4String ParticleName 
    = track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();

  G4AnalysisManager* analysisManager
    = G4AnalysisManager::Instance();


  if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        PhotonCounter::Instance()->AddPhoton();
    }

    
  //=============
  // Tiempo global de un track

  //G4double tiempo = track->GetGlobalTime();
 
 
  // ******************************
  // Reset variables for each event
  // ******************************
  if (eventNumber != fEventNumber)
  {/* G4cout
	<< "distancia"
	<< " " 
        << water_died
	<< " "
       	<< "in"
	<< " " 
        << water_in
	<< " "
	<< "out"
	<< " " 
        << water_out
	<< " "
	<< "detectados"
	<< " " 
        << phoOnPmt
	<< G4endl; */

    //analysisManager->FillH1(0,fCerenkovCounter);
    //analysisManager->FillH1(2, alpmt);
    //analysisManager->FillH1(0, phoOnPmt);
    //analysisManager->FillH1(1, water_died);
    //analysisManager->FillH2(2, water_died, phoOnPmt); 
    fEventNumber = eventNumber;
    fScintillationCounter = 0;
    fCerenkovCounter = 0;
    phoOnPmt = 0;
    // pmtSD->resetPMTSD();
    lengthMaxOk = 0;
    alpmt = 0;
    generadas = 0;
    generadas1 = 0;
    water_in = 0.;
    water_out = 0.;
    water_died = 0.;
    priEner = 0.;
    ener_g = 0;
    //tiempo = 0.;
  }

 

  // *******************************************
  // Cherenkov and Scintillation Photons Counter
  // *******************************************
 const std::vector<const G4Track*>* secondaries 
    = step->GetSecondaryInCurrentStep();
    
 const G4VProcess* creatorProcess = step->GetTrack()->GetCreatorProcess();

  fwaterVolume
    = detectorConstruction->GetWaterVolume();


/*if (secondaries->size()>0 && fwaterVolume == thePostPV)
    for(unsigned int i=0; i<secondaries->size(); ++i)
      if (secondaries->at(i)->GetParentID()>0)
        if(secondaries->at(i)->GetDynamicParticle()
            ->GetParticleDefinition() 
            == G4OpticalPhoton::OpticalPhotonDefinition())
        {
          if (secondaries->at(i)->GetCreatorProcess()
              ->GetProcessName() 
              == "Scintillation")fScintillationCounter++;
          if (secondaries->at(i)->GetCreatorProcess()
              ->GetProcessName()== "Cerenkov")
              G4cout << "Fotón generado por efecto Cherenkov con energía " << photonEnergy << G4endl;
            if(secondaries->at(i)->GetKineticEnergy() > 1.6e-06
                && secondaries->at(i)
                ->GetKineticEnergy() < 3.1e-6)
              fCerenkovCounter++;    

        }*/


  if (secondaries->size() > 0 && fwaterVolume == thePostPV) {
     for (unsigned int i = 0; i < secondaries->size(); ++i) {
         if (secondaries->at(i)->GetParentID() > 0) {
            if (secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
	       if (secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "Scintillation") {
	          fScintillationCounter++;
	       }
	       if (secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
	          //G4cout << "Fotón generado por efecto Cherenkov con energía " << secondaries->at(i)->GetKineticEnergy() <<G4endl;
	          if (secondaries->at(i)->GetKineticEnergy() > 1.6e-06 && secondaries->at(i)->GetKineticEnergy() < 3.1e-6) {
	          fCerenkovCounter++;
	          }
	       }
             }
           }
        }
  }
  


  // ************************
  // Catching Optical Photons
  // ************************
  
 if (ParticleName == "gamma" || ParticleName == "opticalphoton")//esto asumiendo que todos los fotones son cherenkov, pues en el detector construction se quitaron las propiedades de centelleo
  {
	//G4cout << " Proceso creado: " << creatorProcess->GetProcessName() << G4endl;
        
  	generadas1 = 4;
	// analysisManager->FillH1(0,generadas1);

  }
  
//...................... Segmentation fault ......................

//  if ((ParticleName == "gamma" || ParticleName == "opticalphoton") && (thePostPV->GetName() == "wcdThickness" || thePostPV->GetName() == "wcdinferior" || thePostPV->GetName() == "wcdsuperior"))//esto asumiendo que todos los fotones son cherenkov, pues en el detector construction se quitaron las propiedades de centelleo
//   {
// 	//G4cout << " Proceso creado: " << creatorProcess->GetProcessName() << G4endl;
        
//   	generadas = 3;
// 	// analysisManager->FillH1(0,generadas);
// 			 //numero de grafica, bin
// 	ener_g =step->GetPreStepPoint()->GetKineticEnergy();
// 	// analysisManager->FillH1(1,ener_g);
//         //G4cout << "Fotón generado por efecto Cherenkov con energía " << ener_g << G4endl;
// 	//alpmt++; //llegan al pmt
//     //phoOnPmt+=pmtSD->ProcessHits(step); //son detectados
//     	track->SetTrackStatus(fStopAndKill);
//     //analysisManager->FillH1(1,ener_g);
//     //analysisManager->FillH1(2,phoOnPmt);
//     //return;
//   }
//..................................................................

// midiendo la distancia recorrida en agua
/*if(step->GetTrack()->GetParentID()==0)
  {	if(thePrePV->GetName() == "wcdThickness" && thePostPV->GetName() == "Tank" ) //primer paso del primario en el agua 
		{  
		   water_in=step->GetTrack()->GetTrackLength();
 		   //G4cout << "entra al agua" << G4endl; 
		}
	
		if(thePrePV->GetName() == "Tank" && thePostPV->GetName() == "wcdThickness" ) //ultimo paso del primario en el agua
			{	
			  water_out=step->GetTrack()->GetTrackLength();
			  //G4cout << "sale del agua" << G4endl; 
			}
      
		else if(step->GetTrack()->GetKineticEnergy()==0 && step->GetTrack()->GetStepLength()==0 && step->GetTrack()->GetTrackLength()!=0) //si no atraviesa el wcd sino que muere en el agua
		{
			water_out=step->GetTrack()->GetTrackLength();
			//G4cout << "muere en el agua" << G4endl; 
		}
			

  }*/
water_died = water_out-water_in;

  
   

}


