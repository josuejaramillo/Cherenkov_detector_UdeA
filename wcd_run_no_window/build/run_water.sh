parallel 'echo "tiempo seed {}: $(time (./wcd_water -N 1000 -output run_water -seed {} > ./parallel_outputs/water_output_{}.log 2>&1) 2>&1)" >> ./parallel_outputs/timing_water.txt' ::: {1..10}
