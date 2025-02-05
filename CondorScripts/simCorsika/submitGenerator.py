import os


path_input_files = 'YOURPATH/corsika-77500/run/inputFiles/'
input_files = [archivo for archivo in os.listdir(path_input_files) if archivo.endswith('.input')]

i = 1
for input in input_files:
    shs = "submits/runCorsika_" + str(i) + ".sh"
    with open(shs, 'w') as shs:
        shs.write("#!/bin/sh\n")
        shs.write(f"./corsika77500Linux_QGSII_gheisha < {input} > {input[:-5] + 'lst'}\n")
        shs.write(f"tar -czvf {input[:9]}.tar.gz {input[:9]} {'CER' + input[3:9]} {input[:9] + '.long'} {input[:-5] + 'lst'}")
    shs.close()

    archivo = "submits/submit_" + str(i)
    with open(archivo, 'w') as archivo:
        archivo.write("Universe   = vanilla\n")
        archivo.write(f"Executable = YOURPATH/corsika-77500/run/submits/runCorsika_{i}.sh\n")
        archivo.write("Log        = test.log.txt\n")
        archivo.write("Output     = test.out.txt\n")
        archivo.write("Error      = test.error.txt\n")
        archivo.write("initialdir = YOURPATH/corsika-77500/run/\n")
        archivo.write("should_transfer_files = yes\n")
        archivo.write(f"transfer_input_files = corsika77500Linux_QGSII_gheisha, submits/runCorsika_{i}.sh, inputFiles/, corsika_run_files/\n")
        archivo.write("when_to_transfer_output = ON_EXIT\n")
        archivo.write(f"transfer_output_files = {input[:9]}.tar.gz\n")
        archivo.write(f"output_destination = root://eosuser.cern.ch//eos/YOUReosPATH/outs\n")
        archivo.write("request_cpus = 4\n")
        archivo.write("request_memory = 20000\n")
        archivo.write("request_disk = 90GB\n")
        archivo.write('+JobFlavour = "nextweek"\n')
        archivo.write("Queue\n")
    archivo.close()
    i += 1

path_submit_files = 'YOURPATH/corsika-77500/run/submits/'
submit_files = [archivo for archivo in os.listdir(path_submit_files)]

with open("submits/submit_all.sh", 'w') as sh_file:
    sh_file.write("#!/bin/sh\n")

    for submit in submit_files:
        if submit[:-2] != ".sh" and submit[0] == "s":
            sh_file.write("condor_submit " + submit + "\n")
