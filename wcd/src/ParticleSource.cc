#include "ParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include <fstream>
#include <random>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <map>

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
ParticleSource::ParticleSource(int seed, const std::map<std::string,int>& counts)
: gen(seed), remainingCounts(counts)
{
    particleGun = new G4ParticleGun(1);  // One particle per event
    
    LoadDistribution("../Distributions/mu-_energy.csv",   energyDistributions["mu-"]);
    LoadDistribution("../Distributions/mu-_theta.csv",    thetaDistributions["mu-"]);
    LoadDistribution("../Distributions/mu-_phi.csv",      phiDistributions["mu-"]);

    LoadDistribution("../Distributions/mu+_energy.csv",   energyDistributions["mu+"]);
    LoadDistribution("../Distributions/mu+_theta.csv",    thetaDistributions["mu+"]);
    LoadDistribution("../Distributions/mu+_phi.csv",      phiDistributions["mu+"]);

    // Electrons / positrons
    LoadDistribution("../Distributions/e-_energy.csv",    energyDistributions["e-"]);
    LoadDistribution("../Distributions/e-_theta.csv",     thetaDistributions["e-"]);
    LoadDistribution("../Distributions/e-_phi.csv",       phiDistributions["e-"]);

    LoadDistribution("../Distributions/e+_energy.csv",    energyDistributions["e+"]);
    LoadDistribution("../Distributions/e+_theta.csv",     thetaDistributions["e+"]);
    LoadDistribution("../Distributions/e+_phi.csv",       phiDistributions["e+"]);

    // Gamma
    // LoadDistribution("../Distributions/gamma_energy.csv", energyDistributions["gamma"]);
    // LoadDistribution("../Distributions/gamma_theta.csv",  thetaDistributions["gamma"]);
    // LoadDistribution("../Distributions/gamma_phi.csv",    phiDistributions["gamma"]);

    // Proton
    LoadDistribution("../Distributions/proton_energy.csv", energyDistributions["proton"]);
    LoadDistribution("../Distributions/proton_theta.csv",  thetaDistributions["proton"]);
    LoadDistribution("../Distributions/proton_phi.csv",    phiDistributions["proton"]);

    // Neutron
    // LoadDistribution("../Distributions/neutron_energy.csv", energyDistributions["neutron"]);
    // LoadDistribution("../Distributions/neutron_theta.csv",  thetaDistributions["neutron"]);
    // LoadDistribution("../Distributions/neutron_phi.csv",    phiDistributions["neutron"]);
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
ParticleSource::~ParticleSource() {
    delete particleGun;
}

// ------------------------------------------------------------
// Generate primary particles
// ------------------------------------------------------------
void ParticleSource::GeneratePrimaries(G4Event* anEvent) {
    // Select particle type from remaining counts
    std::string particleName = SampleParticleType();
    auto particle = G4ParticleTable::GetParticleTable()->FindParticle(particleName);
    if (!particle) {
        G4cerr << "Particle not found: " << particleName << G4endl;
        return;
    }
    particleGun->SetParticleDefinition(particle);

    // Energy from particle-specific distribution
    G4double energy = SampleFromDistribution(energyDistributions[particleName]) * GeV;
    particleGun->SetParticleEnergy(energy);

    // Angles from particle-specific distribution
    G4double theta = SampleFromDistribution(thetaDistributions[particleName]);
    G4double phi   = SampleFromDistribution(phiDistributions[particleName]);

    G4ThreeVector direction(std::sin(theta) * std::cos(phi),
                            std::sin(theta) * std::sin(phi),
                            -std::cos(theta));
    particleGun->SetParticleMomentumDirection(direction);

    // Position inside a circular source area 
    G4double radius = 500 * 0.5 * cm;
    std::uniform_real_distribution<> dist_radius(0, radius);
    std::uniform_real_distribution<> dist_angle(0, 2 * M_PI);
    G4double r = dist_radius(gen);
    G4double angle = dist_angle(gen);
    G4double x = r * std::cos(angle);
    G4double y = r * std::sin(angle);
    G4double z = 15000.0 * 0.5 * cm;

    particleGun->SetParticlePosition(G4ThreeVector(x, y, z));

    // Generate event
    particleGun->GeneratePrimaryVertex(anEvent);
}

// ------------------------------------------------------------
// Load distribution from CSV
// ------------------------------------------------------------
void ParticleSource::LoadDistribution(const std::string& filename,
                                      std::vector<std::pair<double, double>>& distribution) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        G4cerr << "Error opening file: " << filename << G4endl;
        return;
    }

    double value, probability;
    while (file >> value && file.ignore(1) && file >> probability) {
        distribution.emplace_back(value, probability);
    }
    file.close();

    if (distribution.empty()) {
        G4cerr << "Warning: loaded empty distribution from " << filename << G4endl;
    } else {
        G4cout << "Loaded " << distribution.size()
               << " entries from " << filename << G4endl;
    }
}

// ------------------------------------------------------------
// Sample a value from distribution (CDF method)
// ------------------------------------------------------------
double ParticleSource::SampleFromDistribution(const std::vector<std::pair<double, double>>& distribution) {
    if (distribution.empty()) {
        G4cerr << "Warning: empty distribution, returning 0" << G4endl;
        return 0.0;
    }

    std::vector<double> cdf(distribution.size());
    cdf[0] = distribution[0].second;
    for (size_t i = 1; i < distribution.size(); ++i)
        cdf[i] = cdf[i - 1] + distribution[i].second;

    std::uniform_real_distribution<> dis(0.0, cdf.back());
    double r = dis(gen);
    auto it = std::lower_bound(cdf.begin(), cdf.end(), r);
    return distribution[std::distance(cdf.begin(), it)].first;
}

// ------------------------------------------------------------
// Select particle type from remaining counts
// ------------------------------------------------------------
std::string ParticleSource::SampleParticleType() {
    for (auto& kv : remainingCounts) {
        if (kv.second > 0) {
            kv.second--;       // consume one from quota
            return kv.first;   // return particle name
        }
    }
    return "mu-"; // fallback (should not happen if counts are set correctly)
}