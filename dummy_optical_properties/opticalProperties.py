#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Optical properties plotting script for Water, TiO₂ colloid, and Glycerine
"""

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import mplhep as mp
import os

# -----------------------------------------------------------
# Setup: use CMS style and fix missing glyphs
# -----------------------------------------------------------
mp.style.use("CMS")

# Use DejaVu Sans to support subscripts like TiO₂
matplotlib.rcParams['font.family'] = 'DejaVu Sans'

# -----------------------------------------------------------
# Photon energy (eV)
# -----------------------------------------------------------
photonEnergy = np.array([
    1.127,1.158,1.190,1.224,1.260,1.298,1.339,1.383,
    1.429,1.478,1.531,1.588,1.650,1.716,1.788,1.866,
    1.951,2.044,2.147,2.261,2.387,2.529,2.688,2.868,
    3.075,3.313,3.592,3.922,4.319,4.804,5.413,6.199
])

# -----------------------------------------------------------
# Optical properties
# -----------------------------------------------------------

# --- Water ---
refr_water = np.array([
    1.32548669,1.32592875,1.32636092,1.32679534,1.32700000,1.32700000,1.32793651,1.32800000,
    1.32827081,1.32900000,1.32900000,1.32974810,1.33000000,1.33007925,1.33100000,1.33100000,
    1.33156278,1.33200000,1.33288495,1.33305041,1.33420904,1.33537643,1.33653720,1.33769595,
    1.33886081,1.34104044,1.34355121,1.34703875,1.35154687,1.35935552,1.37114869,1.39586638
])
abs_water = np.array([
    0.014, 0.016, 0.019, 0.024, 0.024, 0.025, 0.063, 0.150,
    0.190, 0.271, 0.434, 0.437, 0.385, 0.662, 1.795, 2.657,
    3.375, 4.115, 10.358, 22.652, 33.008, 40.019, 37.455, 28.337,
    18.017, 8.370, 3.770, 1.998, 1.153, 0.681, 0.393, 0.145
])
rayleigh_water = np.array([
    35.,38.,41.,44.,47.,50.,55.,60.,
    65.,70.,75.,80.,85.,90.,95.,100.,
    110.,120.,130.,140.,160.,180.,200.,220.,
    240.,260.,280.,300.,320.,340.,360.,380.
])

# --- TiO₂ colloid (10%) ---
refr_TiO2 = np.array([
    1.401,1.402,1.403,1.403,1.404,1.405,1.406,1.407,
    1.408,1.409,1.410,1.411,1.412,1.413,1.414,1.415,
    1.416,1.417,1.418,1.419,1.420,1.422,1.424,1.426,
    1.428,1.430,1.432,1.434,1.436,1.438,1.440,1.442
])
abs_TiO2 = np.array([
    50.,48.,45.,40.,35.,30.,20.,10.,
    5.,3.,1.,0.8,0.6,0.5,0.4,0.3,
    0.25,0.20,0.15,0.12,0.10,0.08,0.06,0.05,
    0.04,0.03,0.025,0.020,0.015,0.010,0.008,0.005
])
mie_TiO2 = np.array([
    0.5,0.45,0.40,0.35,0.30,0.28,0.25,0.20,
    0.18,0.16,0.14,0.13,0.12,0.11,0.10,0.095,
    0.090,0.085,0.080,0.075,0.07,0.065,0.060,0.055,
    0.050,0.045,0.042,0.038,0.035,0.030,0.028,0.025
])

# --- Glycerine ---
refr_gly = np.array([
    1.46,1.4605,1.4610,1.4615,1.4620,1.4625,1.4630,1.4635,
    1.4640,1.4645,1.4650,1.4655,1.4660,1.4665,1.4670,1.4675,
    1.4680,1.4685,1.4690,1.4695,1.4700,1.4705,1.4710,1.4715,
    1.4720,1.4725,1.4730,1.4735,1.4740,1.4745,1.4750,1.4755
])
abs_gly = np.array([
    30.,35.,40.,45.,50.,55.,60.,65.,
    70.,75.,80.,85.,90.,95.,100.,105.,
    110.,115.,120.,125.,130.,135.,140.,145.,
    150.,155.,160.,165.,170.,175.,180.,185.
])
rayleigh_gly = np.full(32, 2000.)

# -----------------------------------------------------------
# Create 3 subplots (n, scattering, absorption)
# -----------------------------------------------------------
fig, axs = plt.subplots(3, 1, figsize=(10, 14), sharex=True)

# --- Refractive Index ---
axs[0].plot(photonEnergy, refr_water, '--', alpha=0.3, color='blue')
axs[0].scatter(photonEnergy, refr_water, color='blue', label='Water')
axs[0].plot(photonEnergy, refr_TiO2, '--', alpha=0.3, color='red')
axs[0].scatter(photonEnergy, refr_TiO2, color='red', label='TiO₂ (10%)')
axs[0].plot(photonEnergy, refr_gly, '--', alpha=0.3, color='green')
axs[0].scatter(photonEnergy, refr_gly, color='green', label='Glycerine')
axs[0].set_ylabel("Refractive Index (n)", fontsize=14)
axs[0].set_title("Optical Properties of Media", fontsize=18)
axs[0].legend()
axs[0].grid(alpha=0.3)

# --- Scattering Length ---
axs[1].plot(photonEnergy, rayleigh_water, '--', alpha=0.3, color='blue')
axs[1].scatter(photonEnergy, rayleigh_water, color='blue', label='Water (Rayleigh)')
axs[1].plot(photonEnergy, mie_TiO2, '--', alpha=0.3, color='red')
axs[1].scatter(photonEnergy, mie_TiO2, color='red', label='TiO₂ (Mie)')
axs[1].plot(photonEnergy, rayleigh_gly, '--', alpha=0.3, color='green')
axs[1].scatter(photonEnergy, rayleigh_gly, color='green', label='Glycerine (Rayleigh)')
axs[1].set_yscale('log')
axs[1].set_ylabel("Scattering Length [m]", fontsize=14)
axs[1].legend()
axs[1].grid(alpha=0.3)

# --- Absorption Length ---
axs[2].plot(photonEnergy, abs_water, '--', alpha=0.3, color='blue')
axs[2].scatter(photonEnergy, abs_water, color='blue', label='Water')
axs[2].plot(photonEnergy, abs_TiO2, '--', alpha=0.3, color='red')
axs[2].scatter(photonEnergy, abs_TiO2, color='red', label='TiO₂ (10%)')
axs[2].plot(photonEnergy, abs_gly, '--', alpha=0.3, color='green')
axs[2].scatter(photonEnergy, abs_gly, color='green', label='Glycerine')
axs[2].set_yscale('log')
axs[2].set_xlabel("Photon Energy [eV]", fontsize=14)
axs[2].set_ylabel("Absorption Length [m]", fontsize=14)
axs[2].legend()
axs[2].grid(alpha=0.3)

plt.tight_layout()

# -----------------------------------------------------------
# Always save figure; only show if GUI is available
# -----------------------------------------------------------
output_path = "optical_properties.png"
fig.savefig(output_path, dpi=300, bbox_inches='tight')
print(f"Plot saved to: {output_path}")

if os.environ.get("DISPLAY", "") != "":
    plt.show()
else:
    plt.close(fig)
