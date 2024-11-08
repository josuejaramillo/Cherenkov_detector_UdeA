import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import mplhep as mp

# Use CMS style from mplhep
mp.style.use("CMS")

df = pd.read_csv("showers.shw", sep=" ", header=None)

# Asignar las columnas de momento a variables
x = df[4]
y = df[5]

# Graficar la dispersión en x e y con ejes logarítmicos
plt.scatter(x, y, s=0.1, color="navy", alpha=0.7)
plt.title("Positions of secondary cosmic rays")

# Cambiar el tamaño de los ticks a 14
plt.tick_params(axis='both', which='major', labelsize=14)
plt.tick_params(axis='both', which='minor', labelsize=14)
plt.xlabel(x, fontsize=15)
plt.ylabel(y, fontsize=15)
# Guardar la figura
plt.savefig("positions.png", dpi=300)

# Crear una figura con dos subplots
# fig, axs = plt.subplots(1, 2, figsize=(12, 6))

# # Histograma para la distribución en X (PHEP6) con escala logarítmica en x
# axs[0].hist(x, bins=100, color='blue', alpha=0.7)
# axs[0].set_title('Distribución en x')
# axs[0].set_xlabel('x')
# axs[0].set_ylabel('Frecuencia')
# axs[0].set_xlim(1, 50000)  # Asegurarse de que el rango de valores no incluya cero
# axs[0].set_xscale("log")
# axs[0].tick_params(axis='both', which='major', labelsize=14)
# axs[0].tick_params(axis='both', which='minor', labelsize=14)

# # Histograma para la distribución en Y (PHEP7) con escala logarítmica en x
# axs[1].hist(y, bins=100, color='green', alpha=0.7)
# axs[1].set_title('Distribución en y')
# axs[1].set_xlabel('y')
# axs[1].set_ylabel('Frecuencia')
# axs[1].set_xlim(1, 50000)  # Asegurarse de que el rango de valores no incluya cero
# axs[1].set_xscale("log")
# axs[1].tick_params(axis='both', which='major', labelsize=14)
# axs[1].tick_params(axis='both', which='minor', labelsize=14)

# # Ajustar el espacio entre subplots
# plt.tight_layout()

# Mostrar la gráfica
# plt.show()
