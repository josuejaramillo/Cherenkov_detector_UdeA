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
all_wavelengths = []
all_energies = []

# Cargar todos los archivos .root que coincidan con el patrón "run_*.root"
root_files = glob.glob("./rootFiles/run_*.root")

# Iterar sobre cada archivo y extraer los datos
for root_file in root_files:
    # Abrir el archivo ROOT
    file = ROOT.TFile(root_file)
    
    # Crear un RDataFrame para el TTree photonData
    df = ROOT.RDataFrame("photonData", file)
    
    # Seleccionar las ramas y convertirlas en arrays de numpy
    wavelengths = df.AsNumpy(columns=["photonWavelength"])["photonWavelength"]
    energies = df.AsNumpy(columns=["photonEnergy"])["photonEnergy"]
    
    # Agregar datos a los arrays de todas las longitudes de onda y energías
    all_wavelengths.extend(wavelengths)
    all_energies.extend(energies)

# Convertir las listas acumuladas en arrays de numpy
all_wavelengths = np.array(all_wavelengths)
all_energies = np.array(all_energies)
# Crear un histograma de longitudes de onda
counts, bin_edges = np.histogram(all_wavelengths, bins=70)

# Calcular el ancho de bin para escalar adecuadamente
bin_width = bin_edges[1] - bin_edges[0]

# Normalizar los conteos por el área del PMT y el ancho del bin
normalized_counts = counts / (PMTarea)

# Calcular el error para cada bin: error = 1 / sqrt(NumEventBin)
errors = 1 / np.sqrt(counts)
normalized_errors = errors / (PMTarea)  # Normalizar los errores igual que los conteos

# Graficar el histograma normalizado con barras de error
plt.figure(figsize=(8, 6))
plt.bar(bin_edges[:-1], normalized_counts, width=bin_width, align='edge', yerr=normalized_errors, capsize=3, color='blue', alpha=0.7)
plt.xlabel(r"$\lambda$ [nm]", fontsize=14)
plt.ylabel(r"$\Phi(\lambda)$ [counts / s cm^2]", fontsize=14)
plt.title("Photon Wavelength Histogram", fontsize=18)

plt.tick_params(axis='both', which='major', labelsize=14)
plt.tick_params(axis='both', which='minor', labelsize=14)

plt.savefig("WavelengthHist_Normalized_with_Errors.png", dpi=300)
plt.show()

