#ifndef PrimarySpectrum_h
#define PrimarySpectrum_h 1


//Geant libraries
//
#include "globals.hh"
#include "G4ThreeVector.hh"


// c++ libraries
//
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <iomanip>


class PrimarySpectrum
{
	public:
		PrimarySpectrum();
		~PrimarySpectrum();

		void primaryPosition();

		G4ThreeVector particlePosition;
		G4ThreeVector particleDirection;
		G4String parId;

		void primaryMomento();


	private:
		G4double pi;
		G4double Ro;
		G4double initx;
		G4double inity;
		G4double initz;
		G4double r;
		G4double phi;
		G4double rphi;
		G4int signo1;
	       	G4int signo2;
		
		G4int crkId;
		G4double px;
		G4double py;
		G4double pz;
		G4double x;
		G4double y;
		G4double z;
		G4int shwId;
		G4int prmId;
		G4double prmEner;
		G4double prmThe;
		G4double prmPhi;
		G4double condicion;

		//std::ifstream inputFile;
		int openFile(char*);
		FILE *inFile = NULL;
};
#endif
