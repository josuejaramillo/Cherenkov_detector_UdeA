//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// G4HEPEvtParticle class implementation
//
// Author: Makoto Asai, 1997
// --------------------------------------------------------------------

#include "HEPEvtParticle.hh"

G4Allocator<G4HEPEvtParticle>*& aHEPEvtParticleAllocator()
{
  G4ThreadLocalStatic G4Allocator<G4HEPEvtParticle>* _instance = nullptr;
  return _instance;
}

G4HEPEvtParticle::G4HEPEvtParticle()
{
}

G4HEPEvtParticle::
G4HEPEvtParticle(G4PrimaryParticle* pp,
                 G4int isthep, G4int jdahep1, G4int jdahep2)
  : theParticle(pp),ISTHEP(isthep),JDAHEP1(jdahep1),JDAHEP2(jdahep2)

  // G4int ISTHEP;   // status code
  //   G4int IDHEP;    // PDG code
  //   G4int JDAHEP1;  // first daughter
  //   G4int JDAHEP2;  // last daughter
  //   G4double PHEP1; // px in GeV
  //   G4double PHEP2; // py in GeV
  //   G4double PHEP3; // pz in GeV
  //   G4double PHEP5; // mass in GeV
  //   G4double PHEP6; // x position
	//   G4double PHEP7; // y position
	//   G4double PHEP8; // z position
{
}

G4HEPEvtParticle::~G4HEPEvtParticle()
{
}

G4HEPEvtParticle& G4HEPEvtParticle::operator=(const G4HEPEvtParticle &)
{ 
  return *this;
}

G4bool G4HEPEvtParticle::operator==(const G4HEPEvtParticle &right) const
{
  return (this==&right);
}

G4bool G4HEPEvtParticle::operator!=(const G4HEPEvtParticle &right) const
{
  return (this!=&right);
}
