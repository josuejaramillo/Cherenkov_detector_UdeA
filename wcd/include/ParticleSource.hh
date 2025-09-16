#ifndef PARTICLESOURCE_H
#define PARTICLESOURCE_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include <vector>
#include <string>
#include <random>
#include <map>

class ParticleSource : public G4VUserPrimaryGeneratorAction {
public:
    ParticleSource(int seed, const std::map<std::string,int>& counts);
    ~ParticleSource() override;

    void GeneratePrimaries(G4Event* anEvent) override;

private:
    G4ParticleGun* particleGun;
    std::default_random_engine gen;

    // Distribution maps: per particle type
    std::map<std::string, std::vector<std::pair<double, double>>> energyDistributions;
    std::map<std::string, std::vector<std::pair<double, double>>> thetaDistributions;
    std::map<std::string, std::vector<std::pair<double, double>>> phiDistributions;

    // Remaining number of particles to generate for each species
    std::map<std::string,int> remainingCounts;

    // Helper functions
    void LoadDistribution(const std::string& filename, std::vector<std::pair<double, double>>& distribution);
    double SampleFromDistribution(const std::vector<std::pair<double, double>>& distribution);
    std::string SampleParticleType();
};

#endif // PARTICLESOURCE_H
