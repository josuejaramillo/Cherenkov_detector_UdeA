import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy import interpolate
import mplhep as mp

# Use the CMS style for plotting
mp.style.use("CMS")

# Function to calculate the effective permittivity using the Maxwell-Garnett formula
def eMG(e_h, e_i, f):
    numerator = e_h + ((1 + 2 * f) / 3 ) * (e_i - e_h)
    denominator = e_h + ((1 - f) / 3) * (e_i - e_h)
    return e_h * np.asarray(numerator / denominator)

# Function to perform linear interpolation
def interpolation(points, wl, m):
    f_interpolacion = interpolate.interp1d(wl, m, kind='linear')
    return f_interpolacion(points)

# Constants
h = 4.135667696e-15  # Planck's constant in eVs
c = 3e8  # Speed of light in m/s
hc = h * c  # Product of Planck's constant and speed of light

# Photon energy data in eV
photonEnergy = np.asarray([
    1.127, 1.158, 1.190, 1.224,
    1.260, 1.298, 1.339, 1.383,
    1.429, 1.478, 1.531, 1.588,
    1.650, 1.716, 1.788, 1.866,
    1.951, 2.044, 2.147, 2.261,
    2.387, 2.529, 2.688, 2.868,
    3.075, 3.313, 3.592, 3.922,
    4.319, 4.804, 5.413, 6.199
])

# Convert photon energy to wavelength in micrometers (um)
photonWl = 1e6 * hc / photonEnergy  # um

# Load TiO2 data
n_ti_dioxide = pd.read_csv("n_ti_dioxide.csv", sep=",")
k_ti_dioxide = pd.read_csv("k_ti_dioxide.csv", sep=",")
wl_ti_dioxide = n_ti_dioxide["wl"]

# Create a mask to filter data within the energy range of interest
mask_ti_dioxide = (1 < 1e6 * hc / n_ti_dioxide["wl"]) & (1e6 * hc / n_ti_dioxide["wl"] < 6.3)

# Interpolate TiO2 refractive index (n) and extinction coefficient (k) data
n_ti_dioxide_int = interpolation(photonWl, wl_ti_dioxide[mask_ti_dioxide], n_ti_dioxide["n"][mask_ti_dioxide])
k_ti_dioxide_int = interpolation(photonWl, wl_ti_dioxide[mask_ti_dioxide], k_ti_dioxide["k"][mask_ti_dioxide])

# Load water data
n_water = pd.read_csv("n_water.csv", sep=",")
k_water = pd.read_csv("k_water.csv", sep=",")
wl_water = n_water["wl"]

# Create a mask to filter data within the energy range of interest
mask_water = (1 < 1e6 * hc / n_water["wl"]) & (1e6 * hc / n_water["wl"] < 6.3)

# Interpolate water refractive index (n) and extinction coefficient (k) data
n_water_int = interpolation(photonWl, wl_water[mask_water], n_water["n"][mask_water])
k_water_int = interpolation(photonWl, wl_water[mask_water], k_water["k"][mask_water])

# Calculate permittivity for TiO2 and water
e_i = (n_ti_dioxide_int + 1j * k_ti_dioxide_int)**2  # TiO2 permittivity
e_h = (n_water_int + 1j * k_water_int)**2  # Water permittivity

# Create the plot
fig1 = plt.figure(figsize=(12, 8))

# Plot water refractive index
plt.plot(photonEnergy, n_water_int, color="navy", linestyle='--', alpha=0.3)
plt.scatter(photonEnergy, n_water_int, color="navy", s=20, label="Water")

# Plot TiO2 refractive index (commented out)
# plt.plot(photonEnergy, n_ti_dioxide_int, color="crimson", linestyle='--', alpha=0.3)
# plt.scatter(photonEnergy, n_ti_dioxide_int, color="crimson", s=20, label="Pure TiO2")

# Calculate and plot effective refractive index for different TiO2 concentrations (f)
for f in [0.05, 0.1, 0.2, 0.3]:
    e_eff = eMG(e_h, e_i, f)  # Effective permittivity
    n_eff = np.sqrt(e_eff).real  # Effective refractive index
    k_eff = np.sqrt(e_eff).imag  # Effective extinction coefficient
    plt.plot(photonEnergy, n_eff, linestyle='--', alpha=0.3)
    plt.scatter(photonEnergy, n_eff, s=20, label=fr"{f * 100}% $TiO_2$")

# Add labels, title, and legend
plt.xlabel("Photon Energy [eV]", fontsize=20)
plt.ylabel("n", fontsize=20)
plt.title(r"Refractive index for different $TiO_2$ concentrations", fontsize=25)
plt.legend(loc="upper left")

# Save the plot
fig1.savefig("refractive_index_concentrations.png", dpi=300, bbox_inches='tight')

# Display the plot
plt.show()