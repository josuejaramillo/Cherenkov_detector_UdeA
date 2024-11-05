
// Geant4 Libraries
// 
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


// Local Libraries
// 
#include "PMTHit.hh"


G4ThreadLocal G4Allocator<PMTHit>* PMTHitAllocator=0;


PMTHit::PMTHit()
  : waveLength(0.)
{}


PMTHit::~PMTHit()
{}

G4int PMTHit::askDetected(G4double phoEner)
{

  this->GetWavelength(phoEner);
  
  if(waveLength >= 250.*nm && waveLength < 300.*nm)
  {
    if(G4UniformRand() <= 0.01)
      return 1;
    else 
      return 0;
  }
  else if(waveLength >= 300.*nm && waveLength < 350.*nm)
  {
    if(G4UniformRand() <= 0.03) 
      return 1;
    else
      return 0;
  }
  else if(waveLength >= 350.*nm && waveLength < 400.*nm)
  {
    if(G4UniformRand() <= 0.2) 
      return 1;
    else 
      return 0;
  }
  else if(waveLength >= 400.*nm && waveLength < 450.*nm)
  {
    if(G4UniformRand() <= 0.25)
      return 1;
    else
      return 0;
  }
  else if(waveLength >= 450.*nm && waveLength < 500.*nm)
  {
    if(G4UniformRand() <= 0.2) 
      return 1;
    else 
      return 0;
  }
  else if(waveLength >= 500.*nm && waveLength < 550.*nm)
  {
    if(G4UniformRand() <= 0.14) 
      return 1;
    else
      return 0;
  }
  else if(waveLength >= 550.*nm && waveLength < 600.*nm)
  {
    if(G4UniformRand() <= 0.07)
      return 1;
    else 
      return
        0;
  }
  else if(waveLength >= 600.*nm && waveLength < 650.*nm)
  {
    if(G4UniformRand() <= 0.03) 
      return 1;
    else 
      return 0;
  }
  else if(waveLength >= 650.*nm && waveLength < 700.*nm)
  {
    if(G4UniformRand() <= 0.06)
      return 1;
    else 
      return 0;
  }
  else
   return 0;
}


void PMTHit::GetWavelength(G4double ener)
{
  waveLength = (0.00124 / ener)*nm;//ener siempre en MeV. lambda = hc/E, hc=1240eV*nm = 0.00124MeV*nm 
 /*G4cout << "lambda"
	<< " " 
        << waveLength
	<< " " 
	<< "energia"
	<< " " 
        << ener
        << G4endl;*/
}

