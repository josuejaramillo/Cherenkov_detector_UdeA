#!/bin/bash

# Número total de iteraciones y tamaño de grupo
total_iterations=36
group_size=8

# Carpeta de salida
output_dir="./parallel_outputs"
mkdir -p "$output_dir"

# Ejecutar los grupos
echo "Running Water"
for ((start=1; start<=total_iterations; start+=group_size)); do
  end=$((start + group_size - 1))
  if (( end > total_iterations )); then
    end=$total_iterations
  fi

  echo "Running from seed $start to $end"

  parallel 'echo "tiempo seed {}: $(time (./wcd_water -time 100 -output run_water -seed {} > ./parallel_outputs/water_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_water.txt' ::: $(seq $start $end)
done

echo "Running Colloid 5%"

# Corre para el coloide a una concentracion del 5%
for ((start=1; start<=total_iterations; start+=group_size)); do
  end=$((start + group_size - 1))
  if (( end > total_iterations )); then
    end=$total_iterations
  fi

  echo "Running from seed $start to $end"

  parallel 'echo "tiempo seed {}: $(time (./wcd_colloid_5 -time 100 -output run_colloid_5 -seed {} > ./parallel_outputs/colloid_5_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_colloid_5.txt' ::: $(seq $start $end)
done

echo "Running Colloid 10%"

# Corre para el coloide a una concentracion del 10%
for ((start=1; start<=total_iterations; start+=group_size)); do
  end=$((start + group_size - 1))
  if (( end > total_iterations )); then
    end=$total_iterations
  fi

  echo "Running from seed $start to $end"

  parallel 'echo "tiempo seed {}: $(time (./wcd_colloid_10 -time 100 -output run_colloid_10 -seed {} > ./parallel_outputs/colloid_10_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_colloid_10.txt' ::: $(seq $start $end)
done

echo "Running Colloid 20%"
# Corre para el coloide a una concentracion del 20%
for ((start=1; start<=total_iterations; start+=group_size)); do
  end=$((start + group_size - 1))
  if (( end > total_iterations )); then
    end=$total_iterations
  fi

  echo "Running from seed $start to $end"

  parallel 'echo "tiempo seed {}: $(time (./wcd_colloid_20 -time 100 -output run_colloid_20 -seed {} > ./parallel_outputs/colloid_20_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_colloid_20.txt' ::: $(seq $start $end)
done

echo "Running Colloid 30%"
# Corre para el coloide a una concentracion del 30%
for ((start=1; start<=total_iterations; start+=group_size)); do
  end=$((start + group_size - 1))
  if (( end > total_iterations )); then
    end=$total_iterations
  fi

  echo "Running from seed $start to $end"

  parallel 'echo "tiempo seed {}: $(time (./wcd_colloid_30 -time 100 -output run_colloid_30 -seed {} > ./parallel_outputs/colloid_30_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_colloid_30.txt' ::: $(seq $start $end)
done