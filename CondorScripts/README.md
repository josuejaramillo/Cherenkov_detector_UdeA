## Overview

This directory contains the necessary scripts and instructions to run cosmic ray simulations using CORSIKA and Geant4 in an HTCondor environment through the LXPLUS service. The directory is divided into two main subdirectories:

- **simCorsika:** Contains instructions and files for running CORSIKA simulations.

- **simG4:** Contains scripts and files for running Geant4 simulations.

1. simCorsika: Running CORSIKA Simulations in HTCondor
The simCorsika directory contains a PDF file with detailed instructions on how to set up and run CORSIKA simulations for cosmic ray flux in an HTCondor environment. Please refer to the PDF for step-by-step guidance.

**Files in simCorsika:**
Instructions.pdf: A detailed guide on how to run CORSIKA simulations.

2. simG4: Running Geant4 Simulations in HTCondor
The simG4 directory contains the necessary scripts and files to run Geant4 simulations in an HTCondor environment. It includes the wcd directory, which contains the Geant4 simulation scripts, and a Python script (submitGenerator.py) to automate the submission of jobs.

**Files in simG4:**

Ensure that **wcd** directory containing Geant4 simulation scripts is in the LXPLUS folder.

submitGenerator.py: Python script to generate and submit HTCondor jobs for Geant4 simulations.

**How to Use submitGenerator.py:**
Ensure you have the necessary input files (e.g., input_files.tar.gz) and libraries (e.g., libpng15.so.15) in the correct locations.

Modify the paths in submitGenerator.py to match your environment (e.g., YOURPATH).

Run the script to generate the .sh and .sub files for each simulation:

```bash
    python submitGenerator.py
```

After generating the files, a master script (submit_all_jobs.sh) will be created in the submit folder. Run this script to submit all jobs to HTCondor:

```bash
    ./submit/submit_all_jobs.sh
```
**Key Parameters in submitGenerator.py:**

- Mediums: The script simulates different mediums (water, colloid_5, colloid_10, etc.).

- Job Configuration: The script sets up HTCondor jobs with specific resource requests (e.g., 4 CPUs, 20GB memory, 5GB disk).

**General Notes**

Ensure you have access to the required software (e.g., CORSIKA, Geant4) and environments (e.g., CVMFS for Geant4).

Modify paths and parameters in the scripts as needed for your specific setup.

Check the log files (test.log.txt, test.out.txt, test.error.txt) for job status and debugging.

