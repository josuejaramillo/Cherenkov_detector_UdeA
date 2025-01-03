// Geant libraries
//
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "g4root.hh"
#include "Randomize.hh"
#include "G4ios.hh"


// Local libraries
//
#include "PrimarySpectrum.hh"
#include "EventAction.hh"


// c++ libraries
//
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>


PrimarySpectrum::PrimarySpectrum():
	pi(3.14159265358979323846),
	Ro(100),//33.85), //radio del círculo donde se ubican las partículas sobre el detector
	initx(0.*cm), //posición de la partícula en esa circunferencia
	inity(0.*cm),
	initz(46.*cm),
	r(0.*cm), //
	phi(0.*cm),
	rphi(0.),
	signo1(0),
	signo2(0),
	//line(),
	px(0.),
	py(0.),
	pz(0.),
	condicion(0.)
//	inputFile(),
{
	particlePosition 
		= G4ThreeVector(0.*cm,0.*cm,46.*cm);
	particleDirection
		= G4ThreeVector(0., 0., -1.);
	
	char inputFile[] ="salidasimu.shw.bz2"; //si se cambia debe cambiarse en la línea 91 de éste y en el cmake 

	//"tmpMachin24h.shw.bz2";
	//"salidaMachin24H.shw.bz2";
	openFile(inputFile);

//	inputFile.open("momentum-dist.dat");
//	G4cout << "File was opened" << G4endl;

}


PrimarySpectrum::~PrimarySpectrum()
{	
//	inputFile.close();
}


int PrimarySpectrum::openFile(char *nfi)
{
	char tmpc[256]; //xq ese numero ???___________----- no entiendo esta parte que hace// descomprime leee

	snprintf(tmpc,256,"bzip2 -d -c %s",nfi); //lee y descomprime 
	inFile = popen(tmpc,"r");

	//G4cout << "File was jajaja opened" << G4endl;

	return 1;
}


void PrimarySpectrum::primaryMomento()
{
	G4int search = 1;
	char line[256];

	while(search)
	{
	
		if(feof(inFile))
		{
			char inputFile[] = "salidasimu.shw.bz2"; //"salidaMachin24H.shw.bz2"; //"tmpMachin24h.shw.bz2"; 
			openFile(inputFile);
		}

		if(fgets(line,256,inFile))
		{
			if(line[0] != '#')
			{
				sscanf(
					line,
					"%d %lf %lf %lf %lf %lf %lf %d %d %lf %lf %lf\n",
					&crkId,
					&px,
					&py, 
					&pz,
					&x,
					&y,
					&z,
					&shwId,
					&prmId,
					&prmEner,
					&prmThe,
					&prmPhi
				      ); 
	
				px = px*GeV;
				py = py*GeV;
				pz = pz*GeV;
			}
		}

		search = 0;

		switch(crkId) //traduccion
		{
			case 1:
				parId = "gamma";
				break;
			case 2:
				parId = "e+";
				break;
			case 3:
				parId = "e-";
				break;
			case 5:
				parId = "mu+";
				break;
			case 6:
				parId = "mu-";
				break;
			case 7:
				parId = "pi(1300)0";
				break;
			case 8:
				parId = "pi(1300)+";
				break;
			case 9:
				parId = "pi(1300)-";
				break;
			case 10:
				parId = "kaon0L";
				break;
			case 11:
				parId = "kaon+";
				break;
			case 12:
				parId = "kaon-";
				break;
			case 13:
				parId = "neutron";
				break;
			case 14:
				parId = "proton";
				break;
			case 15:
				parId = "anti_proton";
				break;
			case 25:
				parId = "anti_neutron";
				break;
			default:
				search = 1;
		}
	}
	
	particleDirection
		= G4ThreeVector(px, py, pz);
}


void PrimarySpectrum::primaryPosition()
{
	G4int ok = 1;

	signo1 = (int) (10*G4UniformRand()); // signos de que ??????????

	signo2 = (int) (10*G4UniformRand());

	//G4AnalysisManager* analysisManager 
	//	= G4AnalysisManager::Instance();

	while(ok)
	{
		r = Ro*G4UniformRand()*pow((-1),signo1); 
		phi = Ro*G4UniformRand()*pow((-1),signo2); 
	
		rphi = sqrt(r*r + phi*phi);

		if(rphi < Ro) //Ro(1000)?????
		{
			ok = 0;
			initx = r; //(r + 1001.25)*m; //posicion particula en la circunferencia
			inity = phi; //(phi +0.6)*m;
			//initz = (.65)*m;
		
			particlePosition 
				= G4ThreeVector(initx, inity, initz);

			G4cout << "andrei " 
				<< Ro << " "
				<< initx << " "
				<< inity << " "
				<< initz << " "
				<< G4endl;
					
			//analysisManager->FillNtupleDColumn(0,0,initx);
			//analysisManager->FillNtupleDColumn(0,1,inity);
			//analysisManager->FillNtupleDColumn(0,2,initz);
			//analysisManager->AddNtupleRow(0);
		}
	}
}

