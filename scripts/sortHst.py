import numpy as np
import pandas as pd

data = pd.read_csv("./histogram.hst", delimiter=" ")
data = data.sort_values(by=["p_in_bin(GeV)"]).reset_index(drop=True).groupby("p_in_bin(GeV)").sum().reset_index()
print(data, data.keys())
data.to_csv("./histogram.hst", sep = " ", index=False) 
