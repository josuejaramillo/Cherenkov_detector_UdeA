## Overview

This script calculates and visualizes the effective refractive index of a water-based medium with varying concentrations of titanium dioxide (TiO₂) nanoparticles using the Maxwell-Garnett effective medium approximation. The results are plotted as a function of photon energy.

## Usage

Ensure you have the required CSV files:

n_ti_dioxide.csv and k_ti_dioxide.csv: Contain the refractive index and extinction coefficient data for TiO₂.

n_water.csv and k_water.csv: Contain the refractive index and extinction coefficient data for water.

Run the script:

```bash
    python script.py
```
The script will generate a plot (refractive_index_concentrations.png) showing the refractive index for different TiO₂ concentrations.

## Output

The script produces a plot of the refractive index as a function of photon energy. It includes:

The refractive index of water.

The effective refractive index for TiO₂ concentrations of 5%, 10%, 20%, and 30%.

## Maxwell-Garnett Approximation

The effective permittivity (ε_eff) is calculated using the Maxwell-Garnett formula: $$\epsilon_{MG} = \epsilon_H \frac{\epsilon_H + \frac{1+2f}{3} (\epsilon_I-\epsilon_H)}{\epsilon_H + \frac{1-f}{3} (\epsilon_I-\epsilon_H)}$$

where:

 is the permittivity of the host medium (water).

 is the permittivity of the inclusions (TiO₂).

 is the volume fraction of TiO₂ nanoparticles.
