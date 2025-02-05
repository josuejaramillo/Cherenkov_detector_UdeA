import os

ruta_carpeta = 'YOURPATH/corsika-77500/run/inputFiles/'
extension_deseada = '.input'

archivos_en_carpeta = [archivo for archivo in os.listdir(ruta_carpeta) if archivo.endswith(extension_deseada)]

for archivo in archivos_en_carpeta:
   with open(ruta_carpeta + archivo, 'r+') as file:
      lines = file.readlines()
        # Modificar la línea deseada
      lines[30] = "RADDET      80\n"
      lines[31] = "SAREA      2.0106\n"
      lines[25] = "DIRECT      ./\n"
      # lines[6] = "ERANGE      5.0000e+05 5.0000e+06\n"
        # Rebobinar y escribir las líneas modificadas
      file.seek(0)
      file.writelines(lines)
      file.close()