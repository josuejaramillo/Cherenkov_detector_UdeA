import uproot
import matplotlib.pyplot as plt

# Abre el archivo .root
file = uproot.open("wcdRoot.root")

# Accede al tree llamado "PhotonData"
tree = file["PhotonData"]

# Extrae los datos de las variables photonx y photony
photonx = tree["photonx"].array()/10
photony = tree["photony"].array()/10

# Configuración del radio del círculo
radio = 0.5 * 5.1  # Radio en cm

# Crea el plot de dispersión
plt.figure(figsize=(8, 8))
plt.scatter(photonx, photony, s=2, color='red', label='Photon Positions')

# Agrega el círculo centrado en (0, 0)
circle = plt.Circle((0, 0), radio, color='black', fill=False, linestyle='--', linewidth=2, label=f'PMT')
plt.gca().add_patch(circle)

# Configuración de etiquetas y leyenda
plt.xlabel("x")
plt.ylabel("y")
# plt.title("Scatter plot of photon x and y positions with a circle")
plt.legend()
plt.axis('equal')  # Para asegurar que el círculo sea realmente redondo
plt.show()