import pandas as pd
import numpy as np

# Load data
data = pd.read_csv("../histogram.hst", delimiter=" ")

# Define the muon mass in GeV/c²
mass_mu = 0.10566

area_detector = np.pi * (0.88 * 0.5) ** 2
tiempo = 12*3600
normalizacion = area_detector*tiempo

# Function to convert momentum to energy
def momentum_to_energy(p, mass):
    return np.sqrt(p**2 + mass**2)

# Convert momentum bins to energy for muons
centers_momentum = np.asarray(data["p_in_bin(GeV)"])
centers_energy = momentum_to_energy(centers_momentum, mass_mu)

# Calculate the bin edges
# We assume that the distance between centers is constant
delta_p = np.diff(centers_momentum) / 2  # Half of the distance between consecutive centers
lower_edges_momentum = centers_momentum - np.concatenate(([delta_p[0]], delta_p))
upper_edges_momentum = centers_momentum + np.concatenate((delta_p, [delta_p[-1]]))

# Convert momentum edges to energy
lower_edges_energy = momentum_to_energy(lower_edges_momentum, mass_mu)
upper_edges_energy = momentum_to_energy(upper_edges_momentum, mass_mu)

# Calculate the muon flux (sum of positive and negative muons)
flux_mu_total = (data['N_mu+'] + data['N_mu-']) / normalizacion # Normalized by time in seconds

# Create DataFrame with results
muon_histogram = pd.DataFrame({
    "Lower_Energy_bin(GeV)": lower_edges_energy,
    "Upper_Energy_bin(GeV)": upper_edges_energy,
    "Energy_bin_center(GeV)": centers_energy,
    "Muon_flux": flux_mu_total
})

# Save the DataFrame to a CSV file
muon_histogram.to_csv("muon_flux_histogram.csv", index=False)
