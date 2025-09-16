import pandas as pd
import numpy as np

# Load data
data = pd.read_csv("/home/josue/Desktop/sim_corsika_2nd/hst/histogram.hst", delimiter=" ")

# Normalization
tiempo = 12 * 3600   # 12 hours in seconds
normalizacion = tiempo  # could also be area_detector * tiempo

# Calculate total number of particles per second
particleSpectrum = {
    "mu-":     sum(data['N_mu-'] / normalizacion),
    "mu+":     sum(data['N_mu+'] / normalizacion),
    "e-":      sum(data['N_e-'] / normalizacion),
    "e+":      sum(data['N_e+'] / normalizacion),
    "gamma":   sum(data['N_phot'] / normalizacion),
    "proton":  sum(data['N_p'] / normalizacion),
    "neutron": sum(data['N_n'] / normalizacion)
}

# Print in requested format
print("particleSpectrum = {")
for particle, value in particleSpectrum.items():
    print(f'    {{"{particle}", {value:.3f}}},')
print("};")

