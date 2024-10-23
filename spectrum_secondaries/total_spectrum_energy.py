import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import mplhep as mp

# Cargar datos
data = pd.read_csv("./histogram.hst", delimiter=" ")

# Definir las masas de las partículas en GeV/c²
mass_mu = 0.10566
mass_e = 0.000511
mass_pi = 0.13957
mass_pi0 = 0.13498
mass_p = 0.93827
mass_n = 0.93957

# Función para convertir momentum a energía
def momentum_to_energy(p, mass):
    return np.sqrt(p**2 + mass**2)

# Convertir los bins de momentum a energía para cada partícula
bins_mu_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_mu)
bins_e_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_e)
bins_pi_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_pi)
bins_pi0_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_pi0)
bins_p_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_p)
bins_n_energy = momentum_to_energy(np.asarray(data["p_in_bin(GeV)"]), mass_n)

mp.style.use("CMS")

# Crear figura
fig, ax = plt.subplots(figsize=(12, 8))

# Graficar muones (sin el total μ)
mp.histplot((data['N_mu-']/(12*3600)), np.concatenate((bins_mu_energy, [bins_mu_energy[-1]+50])), label="μ-", binwnorm=True, color="dodgerblue", linewidth=2.5, alpha=0.8)
mp.histplot((data['N_mu+']/(12*3600)), np.concatenate((bins_mu_energy, [bins_mu_energy[-1]+50])), label="μ+", binwnorm=True, color="crimson", linewidth=2.5, alpha=0.8)

# Graficar electrones y positrones
mp.histplot((data['N_e-']/(12*3600)), np.concatenate((bins_e_energy, [bins_e_energy[-1]+50])), label="e-", binwnorm=True, color="orange", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_e+']/(12*3600)), np.concatenate((bins_e_energy, [bins_e_energy[-1]+50])), label="e+", binwnorm=True, color="green", linewidth=2.5, alpha=0.7)

# Graficar piones
mp.histplot((data['N_pi-']/(12*3600)), np.concatenate((bins_pi_energy, [bins_pi_energy[-1]+50])), label="π-", binwnorm=True, color="mediumblue", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_pi+']/(12*3600)), np.concatenate((bins_pi_energy, [bins_pi_energy[-1]+50])), label="π+", binwnorm=True, color="darkred", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_pi0']/(12*3600)), np.concatenate((bins_pi0_energy, [bins_pi0_energy[-1]+50])), label="π0", binwnorm=True, color="lightcoral", linewidth=2.5, alpha=0.7)

# Graficar neutrones, protones, y antiprotones
mp.histplot((data['N_n']/(12*3600)), np.concatenate((bins_n_energy, [bins_n_energy[-1]+50])), label="n", binwnorm=True, color="navy", linewidth=2.5, alpha=0.6)
mp.histplot((data['N_p']/(12*3600)), np.concatenate((bins_p_energy, [bins_p_energy[-1]+50])), label="p", binwnorm=True, color="magenta", linewidth=2.5, alpha=0.6)
mp.histplot((data['N_pbar']/(12*3600)), np.concatenate((bins_p_energy, [bins_p_energy[-1]+50])), label="pbar", binwnorm=True, color="brown", linewidth=2.5, alpha=0.6)

# Graficar otras partículas
mp.histplot((data['N_others']/(12*3600)), np.concatenate((bins_mu_energy, [bins_mu_energy[-1]+50])), label="Otros", binwnorm=True, color="dimgray", linewidth=2.5, alpha=0.5)

# Configuración de los ejes
plt.xlabel("Energy [GeV]", fontsize=14)
plt.ylabel("Particles flux [Particles/m²s]", fontsize=14)

# Ajustes adicionales
plt.xscale("log")
plt.xlim(1e-4, 1e3)
plt.yscale("log")
plt.ylim(1e-4, 1e4)

# Añadir título
plt.title("Secondary cosmic ray flux in Medellín (Energy)", fontsize=16)

# Leyenda
plt.legend(loc="upper right", fontsize=12)
plt.tick_params(axis='both', which='major', labelsize=15)
# Guardar y mostrar
plt.savefig("energy_spectrum_all_particles.png", dpi=300)
plt.show()

