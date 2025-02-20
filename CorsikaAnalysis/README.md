## Overview

This directory contains scripts and code for analyzing CORSIKA simulation data, specifically focusing on extracting and visualizing kinetic variables of muons and other secondary cosmic ray particles.

## C++ Codes for Merging CORSIKA Results
The following C++ codes are used to merge the results from multiple CORSIKA output files into a single file for further analysis.

## **Code 1: Merge Histogram Files (merge_histograms.cpp)**
This code merges multiple CORSIKA histogram files (Salida_1.hst, Salida_2.hst, ..., Salida_60.hst) into a single histogram file (histogram.hst).

**Compilation and Execution:**

To compile and run the code, use the following commands:

```bash
    # Compile the C++ code
    g++ -o merge_histograms merge_histograms.cpp

    # Run the compiled executable
    ./merge_histograms
```
This will generate the histogram.hst file containing the merged histogram data from all input files.

## **Code 2: Merge Shower Files (merge_showers.cpp)**
This code merges multiple CORSIKA shower files (Salida_1.shw, Salida_2.shw, ..., Salida_60.shw) into a single shower file (showers.shw).

**Compilation and Execution:**

To compile and run the code, use the following commands:

```bash
    # Compile the C++ code
    g++ -o merge_showers merge_showers.cpp

    # Run the compiled executable
    ./merge_showers
```
This will generate the showers.shw file containing the merged shower data from all input files.


## Directory Structure
- **kineticVariablesFromMomentum**: This subdirectory contains scripts to extract and plot kinetic variables (energy, theta, phi) from the momentum components of muons generated by CORSIKA simulations.

- **CRdistributionsPlots**: This subdirectory contains scripts to analyze the energy spectrum of secondary cosmic ray particles, including muons, electrons, pions, protons, neutrons, and photons, from CORSIKA simulation data.

## kineticVariablesFromMomentum
This directory contains the following files:

1. C++ Code (extract_kinetic_variables.cpp): This C++ script reads the CORSIKA output file (showers.shw), extracts the momentum components of muons, and computes their kinetic variables (energy, theta, phi). The results are saved in a text file (kinetic_variables.txt).

2. Python Script (plot_kinetic_variables.py): This Python script reads the kinetic_variables.txt file, generates histograms of the kinetic variables, and saves the plots as PNG images. It also saves the normalized distributions to CSV files.

## C++ Code (extract_kinetic_variables.cpp)
This script processes the CORSIKA output file to extract the kinetic variables of muons. It computes the energy, theta (angle from the z-axis), and phi (angle in the xy-plane) from the momentum components (px, py, pz) of each muon.

**Compilation and Execution:**

To compile and run the C++ code, use the following commands:

```bash
    # Compile the C++ code
    g++ -o extract_kinetic_variables extract_kinetic_variables.cpp

    # Run the compiled executable
    ./extract_kinetic_variables
```
This will generate the kinetic_variables.txt file containing the computed kinetic variables.

## Python Script (plot_kinetic_variables.py)

This script reads the kinetic_variables.txt file and generates histograms of the kinetic variables (energy, theta, phi). It also normalizes the distributions and saves them as CSV files.

**Execution:**

To run the Python script, use the following command:

```bash
    python plot_kinetic_variables.py
```
This will generate the following output files:

- normalized_angle_energy_distributions_radians.png: A plot showing the distributions of the kinetic variables.

- theta_distribution_radians.csv: CSV file containing the normalized theta distribution.

- phi_distribution_radians.csv: CSV file containing the normalized phi distribution.

- energy_distribution.csv: CSV file containing the normalized energy distribution.

## CRdistributionsPlots

This directory contains the following files:

1. Python Script (plot_energy_spectrum.py): This script reads the CORSIKA histogram file (histogram.hst), converts momentum bins to energy for various particles, and plots the energy spectrum of secondary cosmic ray particles. It also generates a separate plot for the muon flux.

2. Python Script (calculate_muon_flux.py): This script reads the CORSIKA histogram file (histogram.hst), calculates the muon flux, and saves the results to a CSV file.

## plot_energy_spectrum.py
This script reads the histogram.hst file, converts momentum bins to energy for various particles (muons, electrons, pions, protons, neutrons, and photons), and plots the energy spectrum. It also generates a separate plot for the muon flux.

**Execution:**

To run the Python script, use the following command:

```bash
    python plot_energy_spectrum.py
```
This will generate the following output files:

- energy_spectrum_all_particles.png: A plot showing the energy spectrum of all secondary cosmic ray particles.

- energy_spectrum_muons.png: A plot showing the energy spectrum of muons.

## calculate_muon_flux.py
This script reads the histogram.hst file, calculates the muon flux, and saves the results to a CSV file.

**Execution:**

To run the Python script, use the following command:

```bash
    python calculate_muon_flux.py
```
This will generate the following output file:

- muon_flux_histogram.csv: A CSV file containing the muon flux histogram data.
