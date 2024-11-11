parallel 'echo "tiempo seed {}: $(time (./wcd_colloid -N 1000 -output colloid -seed {} > ./parallel_outputs/colloid_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_colloid.txt' ::: {1..2}
parallel 'echo "tiempo seed {}: $(time (./wcd_water -N 1000 -output water -seed {} > ./parallel_outputs/water_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_water.txt' ::: {1..2}
