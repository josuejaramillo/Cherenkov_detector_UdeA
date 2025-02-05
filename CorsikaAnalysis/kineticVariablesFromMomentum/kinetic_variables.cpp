#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

const double muon_mass = 0.10566;  // MeV/c^2

int main() {
    ifstream inputFile("../showers.shw");
    ofstream outputFile("kinetic_variables.txt");
    
    outputFile << "energy, theta, phi" << endl;
    
    string line;
    double CorsikaId, px, py, pz, x, y, z, shower_id, prm_id, prm_energy, prm_theta, prm_phi;
    int i = 0;
    
    while (getline(inputFile, line)) {
        if (i == 0) { i++; continue; }  // Skip header line
        istringstream iss(line);
        iss >> CorsikaId >> px >> py >> pz >> x >> y >> z >> shower_id >> prm_id >> prm_energy >> prm_theta >> prm_phi;
        
        // Only process if CorsikaId is 5 or 6 (muons)
        if (CorsikaId == 5 || CorsikaId == 6) {
            // Compute the magnitude of the momentum
            double p = sqrt(px * px + py * py + pz * pz);
            
            // Compute the energy using relativistic formula
            double energy = sqrt(p * p + muon_mass * muon_mass);
            
            // Compute theta (angle from the z-axis)
            double theta = acos(pz / p);
            
            // Compute phi (angle in the xy-plane)
            double phi = atan2(py, px);
            
            // Write the computed energy, theta, and phi to the output file
            outputFile << energy << "," << theta << "," << phi << endl;
        }
    }
    
    outputFile.close();
    inputFile.close();
    
    cout << "success" << endl;
    return 0;
}

