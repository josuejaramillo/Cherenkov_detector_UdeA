import os
import sys
import uproot
import numpy as np
import matplotlib.pyplot as plt

def load_root_files(medium):
    # Obtener la lista de archivos en la carpeta "rootFiles"
    folder_path = 'rootFiles'
    files = [f for f in os.listdir(folder_path) if f.startswith(f'run_{medium}_') and f.endswith('.root')]
    
    # Inicializar listas para almacenar los datos
    all_hits = []
    all_deposited_energy = []
    
    # Leer cada archivo y extraer los datos
    for file_name in files:
        file_path = os.path.join(folder_path, file_name)
        with uproot.open(file_path) as file:
            # Acceder al árbol muonData
            tree = file['muonData']
            hits = tree['hits'].array(library="np")
            deposited_energy = tree['depositedEnergy'].array(library="np")
            
            # Agregar los datos a las listas
            all_hits.extend(hits)
            all_deposited_energy.extend(deposited_energy)

    return np.array(all_hits), np.array(all_deposited_energy)

def plot_hits_vs_energy(medium):
    # Cargar los datos
    hits, deposited_energy = load_root_files(medium)
    
    # Crear el gráfico
    plt.figure(figsize=(10, 6))
    plt.scatter(hits, deposited_energy*1000, alpha=0.7, color='navy', s=2, label=f'{medium}')
    plt.xlabel('Hits')
    plt.ylabel('Deposited Energy [MeV]')
    plt.title(f'Hits vs Deposited Energy for medium: {medium}')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    # Validar el argumento de línea de comandos
    if len(sys.argv) != 2:
        print("Uso: python3 depositedEnergy.py <medium>")
        sys.exit(1)
    
    # Obtener el tipo de medium del argumento
    medium = sys.argv[1]
    plot_hits_vs_energy(medium)

