import ROOT
import numpy as np
import matplotlib.pyplot as plt
import mplhep as mp
import glob

# Use the CMS style from mplhep
mp.style.use("CMS")

# Given values
radius_cm = 0.5 * 5.1  # radius in cm
PMT_area = np.pi * radius_cm**2  # area in cm²
norm = PMT_area * 3600 # Normalizing to time
# Initialize arrays to store data
all_wavelengths_water = []
all_energies_water = []

# TiO2 concentrations and corresponding data
concentrations = [30,20,10,5]
# concentrations = [5, 10, 20, 30]
colloid_data = {conc: {"wavelengths": [], "energies": []} for conc in concentrations}

# Load all .root files matching the patterns
root_files_water = glob.glob("./RF_water/run_water_*.root")
root_files_colloids = {
    conc: glob.glob(f"./RF_colloid_{conc}/run_colloid_*.root") for conc in concentrations
}

# Function to load data from ROOT files
def load_root_data(files):
    wavelengths = []
    energies = []
    for root_file in files:
        # Open the ROOT file
        file = ROOT.TFile(root_file)
        
        # Create an RDataFrame for the TTree photonData
        df = ROOT.RDataFrame("photonData", file)
        
        # Select the branches and convert them to numpy arrays
        wavelengths.extend(df.AsNumpy(columns=["photonWavelength"])["photonWavelength"])
        energies.extend(df.AsNumpy(columns=["photonEnergy"])["photonEnergy"])
    
    return np.array(wavelengths), np.array(energies)

# Load water data
all_wavelengths_water, all_energies_water = load_root_data(root_files_water)

# Load data for different TiO2 concentrations
for conc, files in root_files_colloids.items():
    wavelengths, energies = load_root_data(files)
    colloid_data[conc]["wavelengths"] = wavelengths
    colloid_data[conc]["energies"] = energies

# Create histograms for water
counts_water, bin_edges = np.histogram(all_wavelengths_water, bins=70)
bin_width = bin_edges[1] - bin_edges[0]
normalized_counts_water = counts_water / norm
errors_water = np.sqrt(counts_water)
normalized_errors_water = errors_water / norm

# Plot histograms for water and each TiO2 concentration
fig, ax = plt.subplots(figsize=(12, 8))

bin_centers = bin_edges[:-1] + bin_width / 2


# Plot each TiO2 concentration
colors = {"5": "crimson", "10": "limegreen", "20": "darkmagenta", "30": "darkorange"}

# Plot each TiO2 concentration with filled area
for conc, data in colloid_data.items():
    counts_colloid, _ = np.histogram(data["wavelengths"], bins=bin_edges)
    normalized_counts_colloid = counts_colloid / norm
    errors_colloid = np.sqrt(counts_colloid)
    normalized_errors_colloid = errors_colloid / norm
    color = colors[str(conc)]
    
    # Plot the histogram as a line
    mp.histplot(
        normalized_counts_colloid,
        bins=bin_edges,
        histtype="step",
        label=f"TiO2 colloid ({conc}%)",
        color=color
    )
    
    # Fill the area under the curve with all bins
    ax.fill_between(
        bin_edges[:-1],  # Use the lower edges of the bins
        normalized_counts_colloid,  # Height of the histogram
        step="post",
        color=color,
        alpha=1  # Adjust the opacity as preferred
    )
    
    # Plot error bars
    ax.errorbar(
        bin_centers,
        normalized_counts_colloid,
        yerr=normalized_errors_colloid,
        fmt="none",
        ecolor="black",
        elinewidth=1.5,
    )

# Plot water with filled area
mp.histplot(
    [normalized_counts_water],
    bins=bin_edges,
    histtype="step",
    label="Water",
    color="dodgerblue",
)

ax.fill_between(
    bin_edges[:-1],
    normalized_counts_water,
    step="post",
    color="dodgerblue",
    alpha=1  # Adjust the opacity for water
)

ax.errorbar(
    bin_centers,
    normalized_counts_water,
    yerr=normalized_errors_water,
    fmt="none",
    ecolor="black",
    elinewidth=1.5,
)

# Add text with the total number of events
#plt.text(0.45, 0.65, f"Total photons using water: {np.sum(counts_water)}", transform=plt.gca().transAxes,fontsize=12, color='black', ha='left')
for i, conc in enumerate(concentrations):
    total_events = np.sum(np.histogram(colloid_data[conc]["wavelengths"], bins=bin_edges)[0])
    #plt.text(0.45, 0.60 - 0.05 * i, f"Total photons TiO2 {conc}%: {total_events}", transform=plt.gca().transAxes, fontsize=12, color='black', ha='left')

# Configure the plot
ax.set_xlim(180,1050)
ax.set_xlabel(r"$\lambda$ [nm]", fontsize=20)
ax.set_ylabel(r"$\Phi(\lambda)$ [counts / s cm^2]", fontsize=20)
ax.set_title("Comparison of Spectral Flux", fontsize=25)


# Get the current legend handles and labels
handles, labels = ax.get_legend_handles_labels()

# Reorder the elements (e.g., putting "Water" at the end)
order = [4,3,2,1,0]  # Indices of the elements in the desired order
ax.legend([handles[idx] for idx in order], [labels[idx] for idx in order])

ax.tick_params(axis='both', which='major', labelsize=14)
ax.tick_params(axis='both', which='minor', labelsize=14)

fig.savefig("WavelengthHist_Comparison_All.png", dpi=300)

# Plot of ratios between TiO2 and water
bin_centers = bin_edges[:-1] + bin_width / 2
fig2, ax2 = plt.subplots(figsize=(12, 8))

for conc, data in colloid_data.items():
    counts_colloid, _ = np.histogram(data["wavelengths"], bins=bin_edges)
    normalized_counts_colloid = counts_colloid / norm
    ratio = normalized_counts_colloid / normalized_counts_water
    ax2.scatter(bin_centers, ratio, label=f"TiO2 {conc}%", s=15, marker="p")

ax2.hlines(1,180,1050, color = "black")
ax2.set_xlim(180,1050)
ax2.set_ylabel(r"$\Phi_{TiO2} / \Phi_{Water}$", fontsize=20)
ax2.set_xlabel(r"$\lambda$ [nm]", fontsize=20)  
ax2.set_title("Spectral Flux Ratio between TiO2 and Water", fontsize=25)

handles2, labels2 = ax2.get_legend_handles_labels()
order2 = [3,2,1,0]  # Indices of the elements in the desired order
ax2.legend([handles2[idx] for idx in order2], [labels2[idx] for idx in order2], loc="upper right")

fig2.savefig("Ratio_Water_Colloid_All.png", dpi=300)
# plt.show()