#!/bin/bash

# Número total de iteraciones y tamaño de grupo
total_iterations=36
group_size=8

# Carpeta de salida
output_dir="./parallel_outputs"
mkdir -p "$output_dir"

# Ejecutar los grupos
for ((start=1; start<=total_iterations; start+=group_size)); do
  end=$((start + group_size - 1))
  if (( end > total_iterations )); then
    end=$total_iterations
  fi

  echo "Running from seed $start to $end"

  parallel 'echo "tiempo seed {}: $(time (./wcd_water -time 1 -output run_water -seed {} > ./parallel_outputs/water_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_water.txt' ::: $(seq $start $end)
done
