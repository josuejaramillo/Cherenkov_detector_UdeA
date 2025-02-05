## Overview

This folder contains a Python script designed to analyze and visualize data from ROOT files resulting from the simulation of Cherenkov detector, specifically focusing on the spectral flux comparison between water and TiO2 colloids at different concentrations. The script generates histograms and ratio plots to compare the spectral flux of photons detected in water versus TiO2 colloids.

## Directory Structure
The script expects the ROOT files containing the results to be located in the following directories:

    ./G4Analysis/RF_water/
    ./RF_colloid_{conc}

where **conc** corresponds to the specific concentration of the colloid media.

Running the Script
To run the script, navigate to the directory containing the script and execute:

    ```bash
    python compare_multiple_concentration.py

## Output
The script generates two plots:

WavelengthHist_Comparison_All.png: A histogram comparing the spectral flux of water and TiO2 colloids at different concentrations.

Ratio_Water_Colloid_All.png: A scatter plot showing the ratio of spectral flux between TiO2 colloids and water.

These plots are saved in the same directory as the script.

