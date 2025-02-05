import os

# Create folders for the files
sh_folder = "submit"
submit_folder = "submit"
os.makedirs(sh_folder, exist_ok=True)
os.makedirs(submit_folder, exist_ok=True)

mediums = ["water", "colloid_5", "colloid_10", "colloid_20", "colloid_30"]
num_seeds = range(1, 37)

for medium in mediums:
    for num_seed in num_seeds:
        # Create the .sh file in the 'scripts' folder
        sh_filename = os.path.join(sh_folder, f"runSim_{medium}_{num_seed}.sh")
        with open(sh_filename, 'w') as sh_file:
            sh_file.write(f"""#!/bin/sh
source /cvmfs/geant4.cern.ch/geant4/10.7.p04/x86_64-centos7-gcc9-optdeb/bin/geant4.sh
export LD_LIBRARY_PATH=/usr/lib64:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
tar -xzf input_files.tar.gz
cd build/
./wcd_{medium} -time 100 -output run_{medium} -seed {num_seed}

cd ..
mv build/rootFiles/run_{medium}_{num_seed}.root ./

""")
        
        # Create the .sub file in the 'submit' folder
        sub_filename = os.path.join(submit_folder, f"submit_{medium}_{num_seed}")
        with open(sub_filename, 'w') as sub_file:
            sub_file.write(f"""Universe   = vanilla
Executable = /afs/cern.ch/user/YOURPATH/geant4/{sh_filename}
Log        = test.log.txt
Output     = test.out.txt
Error      = test.error.txt
initialdir = /afs/cern.ch/user/YOURPATH/geant4/
should_transfer_files = yes
transfer_input_files = {sh_filename}, wcd_lxplus/input_files.tar.gz, libpng15.so.15
when_to_transfer_output = ON_EXIT
transfer_output_files = run_{medium}_{num_seed}.root
output_destination = root://eosuser.cern.ch//eos/user/YOURPATH/simG4/RF_{medium}
request_cpus = 4
request_memory = 20000
request_disk = 5GB
+JobFlavour = "tomorrow"
environment = "PATH=/bin:/usr/bin:/cvmfs/geant4.cern.ch/geant4/10.7.p04/x86_64-centos7-gcc9-optdeb/bin:$PATH"
environment = "LD_LIBRARY_PATH=/usr/lib64:$LD_LIBRARY_PATH"
Queue

""")


# Folder where the .sub files are located
submit_folder = "submit"

# Name of the .sh file to submit all jobs
master_sh_filename = os.path.join(submit_folder, "submit_all_jobs.sh")

# Open the .sh file to write the commands
with open(master_sh_filename, 'w') as master_sh_file:
    # Write the script header
    master_sh_file.write("#!/bin/bash\n\n")
    
    # Write the commands to submit all .sub files
    for sub_file in os.listdir(submit_folder):
        if sub_file[-1] != "h":
            sub_file_path = os.path.join(submit_folder, sub_file)
            master_sh_file.write(f"condor_submit {sub_file_path[7:]}\n")

# Make the .sh file executable
os.chmod(master_sh_filename, 0o755)

print(f"The file {master_sh_filename} has been created and is ready to submit all jobs.")
