parallel 'echo "tiempo seed {}: $(time (./wcd_water -N 1000 -output run_water -seed {} > ./parallel_outputs/water_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_water.txt' ::: {9..16} &&parallel 'echo "tiempo seed {}: $(time (./wcd_water -N 1000 -output run_water -seed {} > ./parallel_outputs/water_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_water.txt' ::: {17..24} && parallel 'echo "tiempo seed {}: $(time (./wcd_colloid -N 1000 -output run_colloid -seed {} > ./parallel_outputs/colloid_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_colloid.txt' ::: {9..16} && parallel 'echo "tiempo seed {}: $(time (./wcd_colloid -N 1000 -output run_colloid -seed {} > ./parallel_outputs/colloid_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_colloid.txt' ::: {17..24}  