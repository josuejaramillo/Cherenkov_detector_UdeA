import uproot
import numpy as np
import os
import matplotlib.pyplot as plt
import argparse

# Configuración de argumentos de línea de comandos
parser = argparse.ArgumentParser(description="Seleccione el tipo de gráfico para los datos de muones")
parser.add_argument("plot_type", choices=["momentos", "histogramas"], 
                    help="Elige 'momentos' para graficar los vectores de momento o 'histogramas' para graficar los ángulos ajustados.")
args = parser.parse_args()

# Definir la carpeta de los archivos ROOT y el árbol a leer
folder_path = "rootFiles_20kevents"
tree_name = "muonData"

# Parámetros del cilindro cónico truncado
radius_top = 88 * 0.5  # Radio superior en cm
radius_bottom = 58 * 0.5  # Radio inferior en cm
height = 74  # Altura en cm
z_center = 0  # Centro en z del cilindro
z_top = z_center + height / 2  # Z en la parte superior
z_bottom = z_center - height / 2  # Z en la parte inferior

# Parámetros del cilindro normal
radius_cylinder = 0.5 * 5.1  # Radio en cm
height_cylinder = 0.6  # Altura en cm
cylinder_z_center = 37  # Posición central en z
cylinder_z_top = cylinder_z_center + height_cylinder / 2
cylinder_z_bottom = cylinder_z_center - height_cylinder / 2

# Función para dibujar el cilindro cónico truncado
def draw_conical_cylinder(ax):
    z = np.linspace(z_bottom, z_top, 50)
    theta = np.linspace(0, 2 * np.pi, 50)
    theta_grid, z_grid = np.meshgrid(theta, z)
    
    # Radios lineales desde la base hasta la parte superior
    radius_grid = radius_bottom + (radius_top - radius_bottom) * ((z_grid - z_bottom) / height)
    x_grid = radius_grid * np.cos(theta_grid)
    y_grid = radius_grid * np.sin(theta_grid)
    
    ax.plot_surface(x_grid, y_grid, z_grid, color='orange', alpha=0.3, edgecolor='none')

# Función para dibujar el cilindro normal
def draw_cylinder(ax):
    z = np.linspace(cylinder_z_bottom, cylinder_z_top, 20)
    theta = np.linspace(0, 2 * np.pi, 50)
    theta_grid, z_grid = np.meshgrid(theta, z)
    
    x_grid = radius_cylinder * np.cos(theta_grid)
    y_grid = radius_cylinder * np.sin(theta_grid)
    
    ax.plot_wireframe(x_grid, y_grid, z_grid, color='black', linewidth=0.5)

# Obtener lista de archivos ROOT en la carpeta
root_files = [f for f in os.listdir(folder_path) if f.endswith(".root")]

if args.plot_type == "momentos":
    # Graficar los momentos en 3D para cada archivo
    for filename in root_files:
        file_path = os.path.join(folder_path, filename)
        
        # Leer el archivo ROOT y el árbol específico
        with uproot.open(file_path) as file:
            tree = file[tree_name]
            
            # Extraer las variables necesarias
            px = tree["px"].array(library="np")
            py = tree["py"].array(library="np")
            pz = tree["pz"].array(library="np")
            x = tree["x"].array(library="np")
            y = tree["y"].array(library="np")
            z = tree["z"].array(library="np")
            hits = tree["hits"].array(library="np")
            
            # Filtrar solo las filas donde hits == 1002
            mask = hits == 1002
            px_filtered = px[mask]
            py_filtered = py[mask]
            pz_filtered = pz[mask]
            x_filtered = x[mask] / 10  # Convertir de mm a cm
            y_filtered = y[mask] / 10  # Convertir de mm a cm
            z_filtered = z[mask] / 10  # Convertir de mm a cm
            
            # Crear una figura 3D
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            
            # Dibujar el cilindro cónico truncado
            draw_conical_cylinder(ax)
            
            # Dibujar el cilindro normal en (0,0,37)
            draw_cylinder(ax)
            
            # Graficar los vectores de momento en 3D
            ax.quiver(
                x_filtered, y_filtered, z_filtered,  # Puntos de inicio de los vectores
                px_filtered, py_filtered, pz_filtered,  # Componentes de los vectores
                length=8, normalize=True, color="red", alpha=0.7, arrow_length_ratio=0.1
            )
            
            # Configurar etiquetas y título
            ax.set_xlabel("X (posición) [cm]")
            ax.set_ylabel("Y (posición) [cm]")
            ax.set_zlabel("Z (posición) [cm]")
            ax.set_title(f"Vectores de momento para {filename}")
            
            # Ajustar límites de los ejes para ver bien el cilindro y los vectores
            ax.set_xlim(-radius_top, radius_top)
            ax.set_ylim(-radius_top, radius_top)
            ax.set_zlim(z_bottom, z_top)
            
            # Mostrar el gráfico
            plt.show()

elif args.plot_type == "histogramas":
    # Crear figura con subplots 2x2 para los histogramas
    fig, axs = plt.subplots(2, 2, figsize=(10, 8))
    
    # Iterar sobre los archivos y cada subplot
    for i, filename in enumerate(root_files[:4]):  # Tomar los primeros 4 archivos
        file_path = os.path.join(folder_path, filename)
        
        # Leer el archivo ROOT y el árbol específico
        with uproot.open(file_path) as file:
            tree = file[tree_name]
            
            # Extraer las variables necesarias
            px = tree["px"].array(library="np")
            py = tree["py"].array(library="np")
            pz = tree["pz"].array(library="np")
            hits = tree["hits"].array(library="np")
            
            # Filtrar solo las filas donde hits == 1002
            mask = hits > 1002
            px_filtered = px[mask]
            py_filtered = py[mask]
            pz_filtered = pz[mask]
            
            # Cálculo de ángulos en grados
            angles = np.degrees(np.arccos(pz_filtered / np.sqrt(px_filtered**2 + py_filtered**2 + pz_filtered**2)))
            adjusted_angles = 180 - angles  # Ajustar ángulos a 180 - ánguloCalculado
            
            # Graficar el histograma en el subplot correspondiente
            ax = axs[i // 2, i % 2]  # Determinar la posición del subplot
            ax.hist(adjusted_angles, bins=30, color="skyblue", edgecolor="black")
            ax.set_title(f"Ángulos ajustados - {filename}")
            ax.set_xlabel("Ángulo [grados]")
            ax.set_ylabel("Frecuencia")
    
    # Ajustar espaciado entre subplots
    plt.tight_layout()
    plt.suptitle("Distribución de ángulos ajustados", y=1.05)
    
    # Mostrar el gráfico
    plt.show()
