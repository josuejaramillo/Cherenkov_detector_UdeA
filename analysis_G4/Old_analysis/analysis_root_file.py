import ROOT
import numpy as np
import matplotlib.pyplot as plt
import mplhep as mp

# Use CMS style from mplhep
mp.style.use("CMS")

# Open the ROOT file
file = ROOT.TFile("wcdRoot.root")
# Create an RDataFrame for the TTree photonData
df = ROOT.RDataFrame("photonData", file)

# Use RDataFrame to select the branches and convert them to numpy arrays
energy = df.AsNumpy(columns=["photonEnergy"])["photonEnergy"]
wavelength = df.AsNumpy(columns=["photonWavelength"])["photonWavelength"]

# Convert the lists to numpy arrays
energy = np.array(energy)
wavelength = np.array(wavelength)

# Given values
radius_cm = 0.5 * 5.1  # radius in cm
PMTarea = np.pi * radius_cm**2  # area in cm²

# Create a histogram for photonWavelength (assuming wavelength is already loaded)
# plt.hist(wavelength, bins=50, density=False)  # density=False to keep raw counts

# Normalize the histogram by dividing by the area of the circle
# Get the current values of the histogram
counts, bin_edges = np.histogram(wavelength, bins=50)

# Calculate the bin width for proper scaling
bin_width = bin_edges[1] - bin_edges[0]

# Normalize the counts by dividing by the area and bin width
normalized_counts = counts / PMTarea

plt.figure(figsize=(8,6))
# Plot the normalized histogram
plt.bar(bin_edges[:-1], normalized_counts, width=bin_width, align='edge')
plt.xlabel(r"$\lambda$ [nm]", fontsize=14)
plt.ylabel(r"$\Phi(\lambda)$ [counts / s cm²]", fontsize=14)
plt.title("Normalized Histogram of Photon Wavelength", fontsize=18)


plt.tick_params(axis='both', which='major', labelsize=14)
plt.tick_params(axis='both', which='minor', labelsize=14)

plt.savefig("WavelengthHist_Normalized.png", dpi=300)
plt.show()

# Optionally, create a histogram for photonEnergy as well
# plt.hist(energy, bins=50)
# plt.xlabel("Photon Energy")
# plt.ylabel("Frequency")
# plt.title("Histogram of Photon Energy")
# plt.savefig("EnergyHist.png", dpi=300)
# plt.show()

