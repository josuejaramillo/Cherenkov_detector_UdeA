import pandas as pd
import numpy as np

# Cargar datos
data = pd.read_csv("./histogram.hst", delimiter=" ")

# Definir la masa del muon en GeV/c²
mass_mu = 0.10566

# Función para convertir momentum a energía
def momentum_to_energy(p, mass):
    return np.sqrt(p**2 + mass**2)

# Convertir los bins de momentum a energía para los muones
centers_momentum = np.asarray(data["p_in_bin(GeV)"])
centers_energy = momentum_to_energy(centers_momentum, mass_mu)

# Calcular los bordes de los bines
# Suponemos que la distancia entre los centros es constante
delta_p = np.diff(centers_momentum) / 2  # Mitad de la distancia entre centros consecutivos
lower_edges_momentum = centers_momentum - np.concatenate(([delta_p[0]], delta_p))
upper_edges_momentum = centers_momentum + np.concatenate((delta_p, [delta_p[-1]]))

# Convertir los bordes de momentum a energía
lower_edges_energy = momentum_to_energy(lower_edges_momentum, mass_mu)
upper_edges_energy = momentum_to_energy(upper_edges_momentum, mass_mu)

# Calcular el flujo de muones (suma de muones positivos y negativos)
flux_mu_total = (data['N_mu+'] + data['N_mu-']) / (12 * 3600)  # Normalizado por tiempo en segundos

# Crear DataFrame con los resultados
muon_histogram = pd.DataFrame({
    "Lower_Energy_bin(GeV)": lower_edges_energy,
    "Upper_Energy_bin(GeV)": upper_edges_energy,
    "Energy_bin_center(GeV)": centers_energy,
    "Muon_flux": flux_mu_total
})

# Guardar el DataFrame en un archivo CSV
muon_histogram.to_csv("muon_flux_histogram.csv", index=False)

