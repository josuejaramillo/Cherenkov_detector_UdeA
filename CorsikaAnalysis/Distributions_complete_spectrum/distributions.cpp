#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Particle masses in GeV (CORSIKA momenta are in GeV/c usually)
const map<int, double> particleMass = {
    {5, 0.10566},   // mu-
    {6, 0.10566},   // mu+
    {2, 0.000511},  // e-
    {3, 0.000511},  // e+
    {1, 0.0},       // gamma
    {14, 0.93827},  // proton
    {13, 0.93957}   // neutron
};

// Particle labels
const map<int, string> particleName = {
    {5, "mu-"},
    {6, "mu+"},
    {2, "e-"},
    {3, "e+"},
    {1, "gamma"},
    {14, "proton"},
    {13, "neutron"}
};

// Simple histogram function
void makeHistogram(const vector<double>& data, int bins,
                   const string& filename, const string& header) {
    if (data.empty()) return;

    double minVal = *min_element(data.begin(), data.end());
    double maxVal = *max_element(data.begin(), data.end());

    // Expand slightly to avoid edge issues
    double eps = 1e-9;
    minVal -= eps;
    maxVal += eps;

    vector<int> counts(bins, 0);
    for (double v : data) {
        int bin = int((v - minVal) / (maxVal - minVal) * bins);
        if (bin == bins) bin = bins - 1;
        counts[bin]++;
    }

    ofstream out(filename);

    double total = data.size();
    for (int i = 0; i < bins; i++) {
        double center = minVal + (i + 0.5) * (maxVal - minVal) / bins;
        double prob = counts[i] / total;
        out << center << "," << prob << endl;
    }
    out.close();
}

int main() {
    ifstream inputFile("/home/josue/Desktop/sim_corsika_2nd/shw/showers.shw");
    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    string line;
    double CorsikaId, px, py, pz, x, y, z, shower_id, prm_id, prm_energy, prm_theta, prm_phi;
    int i = 0;

    // Storage: particle ID → vector of variables
    map<int, vector<double>> energies, thetas, phis;

    while (getline(inputFile, line)) {
        if (i == 0) { i++; continue; }  // Skip header line
        istringstream iss(line);
        iss >> CorsikaId >> px >> py >> pz >> x >> y >> z
            >> shower_id >> prm_id >> prm_energy >> prm_theta >> prm_phi;

        int id = int(CorsikaId);
        if (particleMass.count(id) == 0) continue; // skip others

        double mass = particleMass.at(id);

        // Momentum magnitude
        double p = sqrt(px * px + py * py + pz * pz);

        // Total energy (GeV)
        double E = sqrt(p * p + mass * mass);

        // θ: angle from z-axis
        double theta = acos(pz / p);

        // φ: angle in xy-plane
        double phi = atan2(py, px);

        energies[id].push_back(E);
        thetas[id].push_back(theta);
        phis[id].push_back(phi);
    }
    inputFile.close();

    // Write histograms
    int bins = 100;  // adjustable
    for (auto& kv : particleName) {
        int id = kv.first;
        string name = kv.second;

        if (!energies[id].empty()) {
            makeHistogram(energies[id], bins,
                          name + "_energy.csv",
                          "Energy_GeV");
            makeHistogram(thetas[id], bins,
                          name + "_theta.csv",
                          "Theta_rad");
            makeHistogram(phis[id], bins,
                          name + "_phi.csv",
                          "Phi_rad");
            cout << "Generated distributions for " << name << endl;
        }
    }

    cout << "All distributions generated." << endl;
    return 0;
}

