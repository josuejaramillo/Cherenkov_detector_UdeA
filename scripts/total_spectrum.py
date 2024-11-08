import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import mplhep as mp

# Cargar datos
data = pd.read_csv("./histogram.hst", delimiter=" ")

# Definir los bins
bins = np.asarray(data["p_in_bin(GeV)"])
mp.style.use("CMS")

# Crear figura
fig, ax = plt.subplots(figsize=(12, 8))

# Graficar muones (sin el total μ)
mp.histplot((data['N_mu-']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="μ-", binwnorm=True, color="dodgerblue", linewidth=2.5, alpha=0.8)
mp.histplot((data['N_mu+']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="μ+", binwnorm=True, color="crimson", linewidth=2.5, alpha=0.8)

# Graficar electrones y positrones
mp.histplot((data['N_e-']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="e-", binwnorm=True, color="orange", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_e+']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="e+", binwnorm=True, color="green", linewidth=2.5, alpha=0.7)

# Graficar piones
mp.histplot((data['N_pi-']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="π-", binwnorm=True, color="mediumblue", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_pi+']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="π+", binwnorm=True, color="darkred", linewidth=2.5, alpha=0.7)
mp.histplot((data['N_pi0']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="π0", binwnorm=True, color="lightcoral", linewidth=2.5, alpha=0.7)

# Graficar neutrones, protones, y antiprotones
mp.histplot((data['N_n']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="n", binwnorm=True, color="navy", linewidth=2.5, alpha=0.6)
mp.histplot((data['N_p']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="p", binwnorm=True, color="magenta", linewidth=2.5, alpha=0.6)
mp.histplot((data['N_pbar']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="pbar", binwnorm=True, color="brown", linewidth=2.5, alpha=0.6)

# Graficar otras partículas
mp.histplot((data['N_others']/(12*3600)), np.concatenate((bins, [bins[-1]+50])), label="Otros", binwnorm=True, color="dimgray", linewidth=2.5, alpha=0.5)

# Configuración de los ejes
plt.xlabel("Momentum [GeV/c]", fontsize=14)
plt.ylabel("Particles flux [Particles/m²s]", fontsize=14) 

# Ajustes adicionales
plt.xscale("log")
#plt.xlim(0.2, 250)
plt.xlim(1e-4, 1e3)
plt.yscale("log")
plt.ylim(1e-5, 1e4)  # Ajusta el rango de Y para evitar demasiada compresión

# Añadir título
plt.title("Secondary cosmic ray flux in Medellín", fontsize=16)

# Leyenda
plt.legend(loc="upper right", fontsize=12)

# Guardar y mostrar
plt.savefig("spectrum_all_particles.png")
plt.show()

