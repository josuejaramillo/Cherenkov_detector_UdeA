import numpy as np
import matplotlib.pyplot as plt
import mplhep as mp
mp.style.use("CMS")

photonEnergy = np.asarray(
    [1.127, 1.158, 1.190, 1.224, 
    1.260, 1.298, 1.339, 1.383, 
    1.429, 1.478, 1.531, 1.588, 
    1.650, 1.716, 1.788, 1.866, 
    1.951, 2.044, 2.147, 2.261, 
    2.387, 2.529, 2.688, 2.868, 
    3.075, 3.313, 3.592, 3.922, 
    4.319, 4.804, 5.413, 6.199]
)

refractiveIndex1 = np.asarray(
    [1.32461554, 1.32506502, 1.32550999, 1.32595216,
    1.32639344, 1.32683587, 1.32728177, 1.32773371, 
    1.32819464, 1.32866791, 1.32915745, 1.32966784, 
    1.33020452, 1.330774, 1.33138419, 1.33204473, 
    1.33276761, 1.33356786, 1.33446457, 1.3354824,
    1.33665365, 1.33802145, 1.33964455, 1.34160493, 
    1.3440201,  1.3470643, 1.35100647, 1.35628372, 
    1.36365569, 1.37457069, 1.39219362, 1.42517179]
)


def refractive_index_TiO2(E):
    # Parámetros de la fórmula
    numerator = 4.6796
    E_factor = 0.2002148 / 1.2398  # Conversion factor for energy in the formula
    
    # Cálculo del índice de refracción
    n = np.sqrt(1 + numerator / (1 - (E * E_factor)**2))
    return n

fig = plt.subplots(figsize=(10, 6))
plt.scatter(photonEnergy, refractiveIndex1, s = 10, color = "crimson", label = "RI Water")
plt.scatter(photonEnergy, refractive_index_TiO2(photonEnergy), s = 10, color = "navy", label = "RI TiO2")

plt.tick_params(axis='both', which='major', labelsize=15)
plt.xlabel("Photon energy [eV]", fontsize=14)
plt.ylabel("Refractive Index", fontsize=14)
plt.title("Refractive index", fontsize=16)
plt.legend()
plt.savefig("RI_energy.png", dpi=300)
plt.show()
