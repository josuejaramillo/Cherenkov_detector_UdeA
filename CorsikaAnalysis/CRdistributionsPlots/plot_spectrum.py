import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import mplhep as mp

# Load data
data = pd.read_csv("../histogram.hst", delimiter=" ")

# Define the masses of the particles in GeV/c²
mass_mu = 0.10566
mass_e = 0.000511
mass_pi = 0.13957
mass_pi0 = 0.13498
mass_p = 0.93827
mass_n = 0.93957

# Normalization
area_detector = np.pi * (0.88 * 0.5) ** 2
tiempo = 12*3600
normalizacion = tiempo #area_detector*tiempo

# Function to convert momentum to energy
def momentum_to_energy(p, mass):
    return np.sqrt(p**2 + mass**2)

# Convert momentum bins to energy for each particle
bins_mu_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_mu)
bins_e_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_e)
bins_pi_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_pi)
bins_pi0_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_pi0)
bins_p_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_p)
bins_n_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_n)

mp.style.use("CMS")

# Create figure
fig, ax = plt.subplots(figsize=(12, 8))

# Plot photons
mp.histplot((data['N_phot'] / normalizacion), np.concatenate((bins_e_energy, [bins_e_energy[-1] + 50])), label="γ", binwnorm=True, color="purple", linewidth=2.5, alpha=0.6)

# Plot muons
mp.histplot((data['N_mu-'] / normalizacion), np.concatenate((bins_mu_energy, [bins_mu_energy[-1] + 50])), label="μ-", binwnorm=True, color="dodgerblue", linewidth=2.5, alpha=0.8)
mp.histplot((data['N_mu+'] / normalizacion), np.concatenate((bins_mu_energy, [bins_mu_energy[-1] + 50])), label="μ+", binwnorm=True, color="crimson", linewidth=2.5, alpha=0.8)

# Plot electrons and positrons
mp.histplot((data['N_e-'] / normalizacion), np.concatenate((bins_e_energy, [bins_e_energy[-1] + 50])), label="e-", binwnorm=True, color="orange", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_e+'] / normalizacion), np.concatenate((bins_e_energy, [bins_e_energy[-1] + 50])), label="e+", binwnorm=True, color="green", linewidth=2.5, alpha=0.7)

# Plot pions
mp.histplot((data['N_pi-'] / normalizacion), np.concatenate((bins_pi_energy, [bins_pi_energy[-1] + 50])), label="π-", binwnorm=True, color="mediumblue", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_pi+'] / normalizacion), np.concatenate((bins_pi_energy, [bins_pi_energy[-1] + 50])), label="π+", binwnorm=True, color="darkred", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_pi0'] / normalizacion), np.concatenate((bins_pi0_energy, [bins_pi0_energy[-1] + 50])), label="π0", binwnorm=True, color="lightcoral", linewidth=2.5, alpha=0.7)

# Plot neutrons, protons, and antiprotons
mp.histplot((data['N_n'] / normalizacion), np.concatenate((bins_n_energy, [bins_n_energy[-1] + 50])), label="n", binwnorm=True, color="navy", linewidth=2.5, alpha=0.6)
mp.histplot((data['N_p'] / normalizacion), np.concatenate((bins_p_energy, [bins_p_energy[-1] + 50])), label="p", binwnorm=True, color="magenta", linewidth=2.5, alpha=0.6)
mp.histplot((data['N_pbar'] / normalizacion), np.concatenate((bins_p_energy, [bins_p_energy[-1] + 50])), label="pbar", binwnorm=True, color="brown", linewidth=2.5, alpha=0.6)

# Plot other particles and total per bin
# mp.histplot((data['N_others'] / normalizacion), np.concatenate((bins_mu_energy, [bins_mu_energy[-1] + 50])), label="Others", binwnorm=True, color="dimgray", linewidth=2.5, alpha=0.5)

# Axis settings
plt.xlabel("Energy [GeV]", fontsize=20)
plt.ylabel(r"$\Xi_{CR}$ [Particles/m²s]", fontsize=20)

# Additional adjustments
plt.xscale("log")
plt.xlim(2e-4, 300)
plt.yscale("log")
plt.ylim(1e-4, 7e6)

# Add title
plt.title("Secondary cosmic ray flux in Medellín", fontsize=25)

# Legend
plt.legend(loc="upper right", fontsize=16)
plt.tick_params(axis='both', which='major', labelsize=16)

# Save and display
fig.savefig("energy_spectrum_all_particles.png", dpi=300)

fig2, ax = plt.subplots(figsize=(12, 8))

# Plot muons
mp.histplot((data['N_mu-'] / normalizacion), np.concatenate((bins_mu_energy, [bins_mu_energy[-1] + 50])), label="μ-", binwnorm=True, color="dodgerblue", linewidth=2.5, alpha=0.8)
mp.histplot((data['N_mu+'] / normalizacion), np.concatenate((bins_mu_energy, [bins_mu_energy[-1] + 50])), label="μ+", binwnorm=True, color="crimson", linewidth=2.5, alpha=0.8)
mp.histplot((data['N_mu+'] / normalizacion) + data['N_mu-'] / normalizacion, np.concatenate((bins_mu_energy, [bins_mu_energy[-1] + 50])), label="μ- + μ+", binwnorm=True, color="black", linewidth=2.5, alpha=0.8)

print(f"Number of muons per second (all energies): {sum((data['N_mu-'] + data['N_mu+']) / normalizacion)}")

# Additional adjustments
plt.xscale("log")
plt.xlim(1e-1, 300)
plt.yscale("log")
plt.ylim(1e-4, 1e2)

# Add title
plt.title("Muon flux in Medellín", fontsize=25)

# Axis settings
plt.xlabel("Energy [GeV]", fontsize=20)
plt.ylabel(r"$\Xi_{\mu}$ [Particles/m²s]", fontsize=20)

# Legend
plt.legend(loc="upper right", fontsize=16)
plt.tick_params(axis='both', which='major', labelsize=16)

# Save and display
fig2.savefig("energy_spectrum_muons.png", dpi=300)

plt.show()
