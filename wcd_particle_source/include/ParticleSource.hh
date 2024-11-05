#ifndef PARTICLESOURCE_H
#define PARTICLESOURCE_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include <vector>
#include <string>

class ParticleSource : public G4VUserPrimaryGeneratorAction {
public:
    ParticleSource();
    ~ParticleSource() override;

    void GeneratePrimaries(G4Event* anEvent) override;

private:
    G4ParticleGun* particleGun;
    std::vector<std::pair<double, double>> energyDistribution;
    std::vector<std::pair<double, double>> phiDistribution;
    std::vector<std::pair<double, double>> thetaDistribution;

    void LoadDistribution(const std::string& filename, std::vector<std::pair<double, double>>& distribution);
    double SampleFromDistribution(const std::vector<std::pair<double, double>>& distribution);
};

#endif // PARTICLESOURCE_H
