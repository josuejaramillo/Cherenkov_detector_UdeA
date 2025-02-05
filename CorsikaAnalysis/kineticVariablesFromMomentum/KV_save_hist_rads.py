import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import mplhep as mp

# Use CMS style from mplhep
mp.style.use("CMS")

# Load CORSIKA output file
data = pd.read_csv('kinetic_variables.txt', sep=",")  # Make sure to use the correct file name

# Access columns by index
energies = data.iloc[:, 0]    # If the file has no header, access by index
zenith = data.iloc[:, 1]  # Keep in radians
azimuth = data.iloc[:, 2] # Keep in radians

# Number of total events
num_events = len(energies)

# Create a 2x3 subplot figure
fig, axs = plt.subplots(2, 3, figsize=(18, 12))

# First row: total counts
# Zenith angle distribution (\theta)
axs[0, 0].hist(zenith, bins=50, color='blue', alpha=0.7, label=r'$\theta$ Angle')
axs[0, 0].set_title(r'$\theta$ Angle Distribution', fontsize=16)
axs[0, 0].set_xlabel(r'$\theta$ [radians]', fontsize=14)
axs[0, 0].set_ylabel('Frequency', fontsize=14)
axs[0, 0].legend(loc="upper right", fontsize=12, frameon=False)
axs[0, 0].tick_params(axis='both', which='major', labelsize=15)

# Azimuth angle distribution (\phi)
axs[0, 1].hist(azimuth, bins=50, color='green', alpha=0.7, label=r'$\phi$ Angle')
axs[0, 1].set_title(r'$\phi$ Angle Distribution', fontsize=16)
axs[0, 1].set_xlabel(r'$\phi$ [radians]', fontsize=14)
axs[0, 1].set_ylabel('Frequency', fontsize=14)
axs[0, 1].legend(loc="upper right", fontsize=12, frameon=False)
axs[0, 1].tick_params(axis='both', which='major', labelsize=15)
axs[0, 1].set_ylim([0, axs[0, 1].get_ylim()[1] * 1.1])

# Energy distribution
axs[0, 2].hist(energies, bins=50, color='red', alpha=0.7, label='Energy')
axs[0, 2].set_title('Energy Distribution', fontsize=16)
axs[0, 2].set_xlabel('Energy [GeV]', fontsize=14)
axs[0, 2].set_ylabel('Frequency', fontsize=14)
axs[0, 2].set_xscale("log")
axs[0, 2].set_yscale("log")
axs[0, 2].legend(loc="upper right", fontsize=12, frameon=False)
axs[0, 2].tick_params(axis='both', which='major', labelsize=15)

# Second row: normalized to probability
# Zenith angle distribution (normalized to probability density)
counts_theta, bins_theta = np.histogram(zenith, bins=50, density=True)
bin_widths_theta = np.diff(bins_theta)
normalized_counts_theta = counts_theta * bin_widths_theta
bin_centers_theta = 0.5 * (bins_theta[1:] + bins_theta[:-1])
axs[1, 0].bar(bin_centers_theta, normalized_counts_theta, width=bin_widths_theta, color='blue', alpha=0.7, label=r'$\theta$ Normalized')
axs[1, 0].set_title(r'Normalized $\theta$ Angle Distribution', fontsize=16)
axs[1, 0].set_xlabel(r'$\theta$ [radians]', fontsize=14)
axs[1, 0].set_ylabel('Probability', fontsize=14)
axs[1, 0].legend(loc="upper right", fontsize=12, frameon=False)
axs[1, 0].tick_params(axis='both', which='major', labelsize=15)

# Azimuth angle distribution (normalized to probability density)
counts_phi, bins_phi = np.histogram(azimuth, bins=50, density=True)
bin_widths_phi = np.diff(bins_phi)
normalized_counts_phi = counts_phi * bin_widths_phi
bin_centers_phi = 0.5 * (bins_phi[1:] + bins_phi[:-1])
axs[1, 1].bar(bin_centers_phi, normalized_counts_phi, width=bin_widths_phi, color='green', alpha=0.7, label=r'$\phi$ Normalized')
axs[1, 1].set_title(r'Normalized $\phi$ Angle Distribution', fontsize=16)
axs[1, 1].set_xlabel(r'$\phi$ [radians]', fontsize=14)
axs[1, 1].set_ylabel('Probability', fontsize=14)
axs[1, 1].legend(loc="upper right", fontsize=12, frameon=False)
axs[1, 1].tick_params(axis='both', which='major', labelsize=15)
axs[1, 1].set_ylim([0, axs[1, 1].get_ylim()[1] * 1.1])

# Energy distribution (normalized to probability density)
counts_energy, bins_energy = np.histogram(energies, bins=50, density=True)
bin_widths_energy = np.diff(bins_energy)
normalized_counts_energy = counts_energy * bin_widths_energy
bin_centers_energy = 0.5 * (bins_energy[1:] + bins_energy[:-1])
axs[1, 2].bar(bin_centers_energy, normalized_counts_energy, width=bin_widths_energy, color='red', alpha=0.7, label='Energy Normalized')
axs[1, 2].set_title('Normalized Energy Distribution', fontsize=16)
axs[1, 2].set_xlabel('Energy [GeV]', fontsize=14)
axs[1, 2].set_ylabel('Probability', fontsize=14)
axs[1, 2].set_xscale("log")
axs[1, 2].set_yscale("log")
axs[1, 2].legend(loc="upper right", fontsize=12, frameon=False)
axs[1, 2].tick_params(axis='both', which='major', labelsize=15)

# Adjust layout and save figure
plt.tight_layout()
plt.savefig("normalized_angle_energy_distributions_radians.png", dpi=300)

# Save normalized distributions to CSV files
theta_distribution = pd.DataFrame({'Theta [radians]': bin_centers_theta, 'Probability': normalized_counts_theta})
phi_distribution = pd.DataFrame({'Phi [radians]': bin_centers_phi, 'Probability': normalized_counts_phi})
energy_distribution = pd.DataFrame({'Energy [GeV]': bin_centers_energy, 'Probability': normalized_counts_energy})

# Save to CSV
theta_distribution.to_csv('theta_distribution_radians.csv', index=False)
phi_distribution.to_csv('phi_distribution_radians.csv', index=False)
energy_distribution.to_csv('energy_distribution.csv', index=False)

plt.show()

