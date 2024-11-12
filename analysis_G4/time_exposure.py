import numpy as np
import pandas as pd
import uproot
import glob

# Cargar los datos del flujo de muones desde el archivo CSV
flux_data = pd.read_csv("muon_flux_histogram.csv")
lower_edges_energy = flux_data["Lower_Energy_bin(GeV)"].values  # Bordes inferiores de energía
upper_edges_energy = flux_data["Upper_Energy_bin(GeV)"].values  # Bordes superiores de energía
muon_flux = flux_data["Muon_flux"].values  # Flujo de muones (partículas/m²s)

# Crear los bines de energía a partir de los bordes inferior y superior
energy_bins = np.concatenate((lower_edges_energy, [upper_edges_energy[-1]]))

# Inicializar una lista para acumular todas las energías
all_energies = []

# Iterar sobre todos los archivos .root en la carpeta rootFiles con el patrón run_colloid_*.root
for file_path in glob.glob("./rootFiles/run_colloid_*.root"):
	print(file_path)
	with uproot.open(file_path) as file:
		tree = file["muonData"]
		energies = tree["energy"].array(library="np")  # Energías de las partículas
		all_energies.append(energies)

# Combinar todas las energías en un solo array
all_energies = np.concatenate(all_energies)

# Crear el histograma de densidad de partículas utilizando los mismos bines de energía
counts, _ = np.histogram(all_energies, bins=energy_bins)

# Calcular la densidad de partículas (partículas/m²) para cada bin de energía
area_detector = np.pi * (0.88 * 0.5) ** 2
muon_density = counts / area_detector

# Calcular el tiempo de exposición para cada bin de energía
muon_flux[muon_flux == 0] = np.nan  # Evita la división por cero
time_exposure = muon_density / muon_flux

# Tiempo de exposición promedio
average_time_exposure = np.nanmean(time_exposure)

print(f"Tiempo de exposición promedio: {average_time_exposure:.4f} segundos")

