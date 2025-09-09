

#include "ParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include <fstream>
#include <random>
#include <cmath>
#include <numeric>
#include <algorithm>

ParticleSource::ParticleSource(int seed) : gen(seed) {
    particleGun = new G4ParticleGun(1);  // One particle per event

    // Load distributions
    LoadDistribution("../Distributions/energy_distribution.csv", energyDistribution);
    LoadDistribution("../Distributions/phi_distribution_radians.csv", phiDistribution);
    LoadDistribution("../Distributions/theta_distribution_radians.csv", thetaDistribution);

    // Atmospheric particles with relative weights (empirical/flexible)
    particleSpectrum = {
        {"mu-"},
        {"mu+"},
        {"e-"},
        {"e+"},
        {"gamma"},
        {"proton"},
        {"neutron"}
    };
}

ParticleSource::~ParticleSource() {
    delete particleGun;
}

void ParticleSource::GeneratePrimaries(G4Event* anEvent) {
    // Select particle type
    std::string particleName = SampleParticleType();
    auto particle = G4ParticleTable::GetParticleTable()->FindParticle(particleName);
    if (!particle) {
        G4cerr << "Particle not found: " << particleName << G4endl;
        return;
    }
    particleGun->SetParticleDefinition(particle);

    // Sample energy from shared distribution
    G4double energy = SampleFromDistribution(energyDistribution) * GeV;
    particleGun->SetParticleEnergy(energy);

    // Sample direction
    G4double theta = SampleFromDistribution(thetaDistribution);
    G4double phi = SampleFromDistribution(phiDistribution);
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

void ParticleSource::LoadDistribution(const std::string& filename, std::vector<std::pair<double, double>>& distribution) {
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
}

double ParticleSource::SampleFromDistribution(const std::vector<std::pair<double, double>>& distribution) {
    std::vector<double> cdf(distribution.size());
    cdf[0] = distribution[0].second;
    for (size_t i = 1; i < distribution.size(); ++i)
        cdf[i] = cdf[i - 1] + distribution[i].second;

    std::uniform_real_distribution<> dis(0.0, cdf.back());
    double r = dis(gen);
    auto it = std::lower_bound(cdf.begin(), cdf.end(), r);
    return distribution[std::distance(cdf.begin(), it)].first;
}

std::string ParticleSource::SampleParticleType() {
    std::vector<double> weights;
    for (const auto& entry : particleSpectrum) {
        weights.push_back(entry.weight);
    }

    std::vector<double> cdf(weights.size());
    cdf[0] = weights[0];
    for (size_t i = 1; i < weights.size(); ++i)
        cdf[i] = cdf[i - 1] + weights[i];

    std::uniform_real_distribution<> dis(0.0, cdf.back());
    double r = dis(gen);
    size_t index = std::distance(cdf.begin(), std::lower_bound(cdf.begin(), cdf.end(), r));
    return particleSpectrum[index].name;
}



/*
#include "ParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include <fstream>
#include <random>
#include <cmath>
#include <numeric>

ParticleSource::ParticleSource(int seed) : gen(seed) {
    particleGun = new G4ParticleGun(1);  // Dispara una partícula por evento

    auto particleTable = G4ParticleTable::GetParticleTable();
    auto particle = particleTable->FindParticle("mu-");  // Ajuste de partícula; aquí es un muon negativo
    particleGun->SetParticleDefinition(particle);

    // Cargar distribuciones desde rutas de archivos CSV
    LoadDistribution("../Distributions/energy_distribution.csv", energyDistribution);
    LoadDistribution("../Distributions/phi_distribution_radians.csv", phiDistribution);
    LoadDistribution("../Distributions/theta_distribution_radians.csv", thetaDistribution);
}

ParticleSource::~ParticleSource() {
    delete particleGun;
}

void ParticleSource::GeneratePrimaries(G4Event* anEvent) {
    // Muestrear energía, theta y phi usando distribuciones basadas en probabilidad
    G4double energy = SampleFromDistribution(energyDistribution) * GeV;
    G4double theta = SampleFromDistribution(thetaDistribution);
    G4double phi = SampleFromDistribution(phiDistribution);

    // Establecer energía y dirección de la partícula
    particleGun->SetParticleEnergy(energy);
    G4ThreeVector direction(std::sin(theta) * std::cos(phi),
                            std::sin(theta) * std::sin(phi),
                            -1*std::cos(theta));
    particleGun->SetParticleMomentumDirection(direction);

    // Posición de la partícula: dentro de un círculo en (0, 0, 74cm)
    G4double radius = 88*0.5 * cm;  // Radio del círculo
    std::uniform_real_distribution<> dist_radius(0, radius);
    std::uniform_real_distribution<> dist_angle(0, 2 * M_PI);

    // Muestrear una posición aleatoria dentro del círculo
    G4double r = dist_radius(gen);
    G4double angle = dist_angle(gen);
    G4double x = r * std::cos(angle);
    G4double y = r * std::sin(angle);
    G4double z = 74.0*0.5 * cm;  // Altura fija en z

    particleGun->SetParticlePosition(G4ThreeVector(x, y, z));

    // Generar el evento
    particleGun->GeneratePrimaryVertex(anEvent);

    // Output de energía, dirección y posición
    //G4cout << "Particle Energy: " << energy / GeV << " GeV, "
    //      << "Position: (" << x / cm << " cm, " << y / cm << " cm, " << z / cm << " cm), "
    //      << "Direction: (" << direction.x() << ", " << direction.y() << ", " << direction.z() << ")"
    //     << G4endl;
}

void ParticleSource::LoadDistribution(const std::string& filename, std::vector<std::pair<double, double>>& distribution) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        G4cerr << "Error al abrir el archivo: " << filename << G4endl;
        return;
    }
    
    double value, probability;
    while (file >> value && file.ignore(1) && file >> probability) {
        distribution.emplace_back(value, probability);
    }
    file.close();
}

double ParticleSource::SampleFromDistribution(const std::vector<std::pair<double, double>>& distribution) {
    // Crear un vector de la CDF
    std::vector<double> cdf(distribution.size());
    cdf[0] = distribution[0].second;
    for (size_t i = 1; i < distribution.size(); ++i) {
        cdf[i] = cdf[i - 1] + distribution[i].second;
    }

    // Generar un número aleatorio en el rango de la CDF
    std::uniform_real_distribution<> dis(0.0, cdf.back());
    double random_value = dis(gen);

    // Buscar el índice donde cae el número aleatorio
    auto it = std::lower_bound(cdf.begin(), cdf.end(), random_value);
    size_t index = std::distance(cdf.begin(), it);

    return distribution[index].first;
}
*\
