import ROOT
import numpy as np
import matplotlib.pyplot as plt
import mplhep as mp
import glob

# Usa el estilo CMS de mplhep
mp.style.use("CMS")

# Valores dados
radius_cm = 0.5 * 5.1  # radio en cm
PMTarea = np.pi * radius_cm**2  # área en cm²

# Inicializar arrays para almacenar datos de múltiples archivos
all_wavelengths_water = []
all_energies_water = []
all_wavelengths_colloid = []
all_energies_colloid = []

# Cargar todos los archivos .root que coincidan con el patrón "run_water_*.root" y "run_colloid_*.root"
root_files_water = glob.glob("./rootFiles/run_water_*.root")
root_files_colloid = glob.glob("./rootFiles/run_colloid_*.root")

# Función para cargar datos desde archivos ROOT
def load_root_data(files):
    wavelengths = []
    energies = []
    for root_file in files:
        # Abrir el archivo ROOT
        file = ROOT.TFile(root_file)
        
        # Crear un RDataFrame para el TTree photonData
        df = ROOT.RDataFrame("photonData", file)
        
        # Seleccionar las ramas y convertirlas en arrays de numpy
        wavelengths.extend(df.AsNumpy(columns=["photonWavelength"])["photonWavelength"])
        energies.extend(df.AsNumpy(columns=["photonEnergy"])["photonEnergy"])
    
    return np.array(wavelengths), np.array(energies)

# Cargar datos de ambos conjuntos de archivos
all_wavelengths_water, all_energies_water = load_root_data(root_files_water)
all_wavelengths_colloid, all_energies_colloid = load_root_data(root_files_colloid)

# Crear histogramas de longitudes de onda para ambos conjuntos de datos
counts_water, bin_edges = np.histogram(all_wavelengths_water, bins=70)
counts_colloid, _ = np.histogram(all_wavelengths_colloid, bins=bin_edges)

# Calcular el ancho de bin para escalar adecuadamente
bin_width = bin_edges[1] - bin_edges[0]

# Normalizar los conteos por el área del PMT y el ancho del bin
normalized_counts_water = counts_water / PMTarea
normalized_counts_colloid = counts_colloid / PMTarea

# Calcular el error para cada bin: error = 1 / sqrt(NumEventBin)
errors_water = np.sqrt(counts_water)
errors_colloid = np.sqrt(counts_colloid)
normalized_errors_water = errors_water / PMTarea
normalized_errors_colloid = errors_colloid / PMTarea

# Calcular el número total de eventos para cada dataset
total_events_water = np.sum(counts_water)
total_events_colloid = np.sum(counts_colloid)

# Graficar ambos histogramas normalizados con barras de error
plt.figure(figsize=(8, 6))
plt.bar(bin_edges[:-1], normalized_counts_colloid, width=bin_width, align='edge', yerr=normalized_errors_colloid,capsize=2, color='crimson', alpha=0.5, label='TiO2 colloid')
plt.bar(bin_edges[:-1], normalized_counts_water, width=bin_width, align='edge', yerr=normalized_errors_water,
        capsize=2, color='blue', alpha=0.7, label='Water')

# Añadir texto con el número total de eventos
plt.text(0.45, 0.65, f"Total photons using water: {total_events_water}", transform=plt.gca().transAxes,
         fontsize=12, color='black', ha='left')
plt.text(0.45, 0.60, f"Total photons using TiO2 colloid: {total_events_colloid}", transform=plt.gca().transAxes,
         fontsize=12, color='black', ha='left')

plt.xlabel(r"$\lambda$ [nm]", fontsize=14)
plt.ylabel(r"$\Phi(\lambda)$ [counts / s cm^2]", fontsize=14)
plt.title("Comparision of Spectral Flux", fontsize=18)
plt.legend()

plt.tick_params(axis='both', which='major', labelsize=14)
plt.tick_params(axis='both', which='minor', labelsize=14)

plt.savefig("WavelengthHist_Comparison_Water_vs_Colloid.png", dpi=300)

#Ratio
bin_centers = bin_edges[:-1] + bin_width / 2
plt.figure(figsize=(8, 6))
plt.scatter(bin_centers, normalized_counts_colloid/normalized_counts_water, color='navy', s=15)
plt.ylabel(r"$\Phi_{TiO2} / \Phi_{Water} $", fontsize=14)
plt.xlabel(r"$\lambda$ [nm]", fontsize=14)
plt.title("Spectral Flux Ratio between TiO2 and Water", fontsize=18)
plt.savefig("Ratio_Water_Colloid.png", dpi=300)
plt.show()






