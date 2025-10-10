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

// --- NEW: simple params you can later expose via ctor or macro ---
static const double Rcore_m  = 200.0;  // core-shift radius (m)
static const double Rcatch_m = 0.6;    // catchment ~ tank radius + margin (m)
static const double zTop_m   = 1.0;    // top of tank is ~1 m above ground
static const int    kMaxPosTrials = 200; // resample attempts per particle

// ------------------------------------------------------------
ParticleSource::ParticleSource(int seed, const std::map<std::string,int>& counts)
: gen(seed), remainingCounts(counts)
{
    particleGun = new G4ParticleGun(1);  // One particle per event
    
    // Muons
    LoadDistribution("../Distributions/mu-_energy.csv",   energyDistributions["mu-"]);
    LoadDistribution("../Distributions/mu-_theta.csv",    thetaDistributions["mu-"]);
    LoadDistribution("../Distributions/mu-_phi.csv",      phiDistributions["mu-"]);
    LoadDistribution("../Distributions/mu-_r.csv",        rDistributions["mu-"]);   // NEW

    LoadDistribution("../Distributions/mu+_energy.csv",   energyDistributions["mu+"]);
    LoadDistribution("../Distributions/mu+_theta.csv",    thetaDistributions["mu+"]);
    LoadDistribution("../Distributions/mu+_phi.csv",      phiDistributions["mu+"]);
    LoadDistribution("../Distributions/mu+_r.csv",        rDistributions["mu+"]);   // NEW

    // Electrons / positrons
    LoadDistribution("../Distributions/e-_energy.csv",    energyDistributions["e-"]);
    LoadDistribution("../Distributions/e-_theta.csv",     thetaDistributions["e-"]);
    LoadDistribution("../Distributions/e-_phi.csv",       phiDistributions["e-"]);
    LoadDistribution("../Distributions/e-_r.csv",         rDistributions["e-"]);    // NEW

    LoadDistribution("../Distributions/e+_energy.csv",    energyDistributions["e+"]);
    LoadDistribution("../Distributions/e+_theta.csv",     thetaDistributions["e+"]);
    LoadDistribution("../Distributions/e+_phi.csv",       phiDistributions["e+"]);
    LoadDistribution("../Distributions/e+_r.csv",         rDistributions["e+"]);    // NEW

    // Proton
    LoadDistribution("../Distributions/proton_energy.csv", energyDistributions["proton"]);
    LoadDistribution("../Distributions/proton_theta.csv",  thetaDistributions["proton"]);
    LoadDistribution("../Distributions/proton_phi.csv",    phiDistributions["proton"]);
    LoadDistribution("../Distributions/proton_r.csv",      rDistributions["proton"]); // NEW
}

// ------------------------------------------------------------
ParticleSource::~ParticleSource() {
    delete particleGun;
}

// ------------------------------------------------------------
void ParticleSource::GeneratePrimaries(G4Event* anEvent) {
    // 1) Choose particle type according to your remainingCounts
    std::string particleName = SampleParticleType();
    auto particle = G4ParticleTable::GetParticleTable()->FindParticle(particleName);
    if (!particle) {
        G4cerr << "Particle not found: " << particleName << G4endl;
        return;
    }
    particleGun->SetParticleDefinition(particle);

    // 2) Sample energy and direction from your PDFs
    G4double energy = SampleFromDistribution(energyDistributions[particleName]) * GeV;
    particleGun->SetParticleEnergy(energy);

    G4double theta = SampleFromDistribution(thetaDistributions[particleName]);
    G4double phi   = SampleFromDistribution(phiDistributions[particleName]);

    // Downward-pointing unit vector (z negative)
    G4ThreeVector direction(std::sin(theta) * std::cos(phi),
                            std::sin(theta) * std::sin(phi),
                            -std::cos(theta));
    particleGun->SetParticleMomentumDirection(direction);

    // 3) Sample position using radial PDF + core shift + catchment
    //    - Core shift: shower core uniform-in-area within Rcore_m
    //    - r: from PDF (meters); azimuth uniform
    //    - Accept only if (x,y) falls inside catchment disk around tank
    std::uniform_real_distribution<> U01(0.0, 1.0);
    std::uniform_real_distribution<> Uphi(0.0, 2.0*M_PI);

    // Precompute a per-particle core shift (this is “ambient exposure”)
    double rc   = Rcore_m * std::sqrt(U01(gen));
    double ac   = Uphi(gen);
    double dx_m = rc * std::cos(ac);
    double dy_m = rc * std::sin(ac);

    // Try up to kMaxPosTrials to get an (x,y) within catchment
    G4double x = 0.0, y = 0.0;
    bool ok = false;

    for (int t=0; t<kMaxPosTrials; ++t) {
        double r_m = 0.0;
        // If we have a radial PDF for this particle, use it; else fallback to small uniform disk
        if (!rDistributions[particleName].empty()) {
            r_m = SampleFromDistribution(rDistributions[particleName]); // meters
        } else {
            // conservative fallback radius: same as catchment
            r_m = Rcatch_m * std::sqrt(U01(gen));
        }
        double a   = Uphi(gen);
        double xm  = dx_m + r_m * std::cos(a);
        double ym  = dy_m + r_m * std::sin(a);

        if ( (xm*xm + ym*ym) <= (Rcatch_m*Rcatch_m) ) {
            x = xm * m;  // to G4 units
            y = ym * m;
            ok = true;
            break;
        }
    }

    // If no acceptable position found, just place at tank center (rare if PDFs reasonable)
    if (!ok) {
        x = 0.0; y = 0.0;
    }

    // z at the top of the tank (just above to avoid boundary issues)
    G4double z = (zTop_m + 0.05) * m; // +5 cm safety

    particleGun->SetParticlePosition(G4ThreeVector(x, y, z));

    // 4) Fire
    particleGun->GeneratePrimaryVertex(anEvent);
}

// ------------------------------------------------------------
void ParticleSource::LoadDistribution(const std::string& filename,
                                      std::vector<std::pair<double, double>>& distribution) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // It’s okay if some files (e.g., proton_r.csv) don’t exist yet; just warn.
        G4cout << "Notice: could not open " << filename << " (will fallback if needed)" << G4endl;
        return;
    }

    double value, probability;
    char comma;
    while (file >> value >> comma >> probability) {
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
double ParticleSource::SampleFromDistribution(const std::vector<std::pair<double, double>>& distribution) {
    if (distribution.empty()) {
        // caller should handle fallback; but keep a safe return
        return 0.0;
    }

    // Build CDF (could cache per distribution if you want speed)
    std::vector<double> cdf(distribution.size());
    cdf[0] = distribution[0].second;
    for (size_t i = 1; i < distribution.size(); ++i)
        cdf[i] = cdf[i - 1] + distribution[i].second;

    std::uniform_real_distribution<> dis(0.0, cdf.back());
    double u = dis(gen);
    auto it = std::lower_bound(cdf.begin(), cdf.end(), u);
    return distribution[std::distance(cdf.begin(), it)].first;
}

// ------------------------------------------------------------
std::string ParticleSource::SampleParticleType() {
    for (auto& kv : remainingCounts) {
        if (kv.second > 0) {
            kv.second--;
            return kv.first;
        }
    }
    return "mu-"; // fallback
}
