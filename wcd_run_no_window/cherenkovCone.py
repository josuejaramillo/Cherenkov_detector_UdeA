import pandas as pd
import ROOT
import matplotlib.pyplot as plt
import numpy as np

file = ROOT.TFile.Open("build/wcdRoot.root")
if not file:
    print("Error: Unable to open file.")
    exit()

tree = file.Get("Hits")

# Check if the tree is retrieved successfully
if not tree:
    print("Error: Unable to retrieve tree.")
    exit()

# Create empty dictionaries to hold the data
data = {}

# Loop over all branches in the tree
for branch in tree.GetListOfBranches():
    # Get the branch name
    branch_name = branch.GetName()
    
    # Create an empty list to hold branch values
    data[branch_name] = []
    
    # Loop over all entries in the tree
    for entry in tree:
        # Fill the list with branch values
        data[branch_name].append(getattr(entry, branch_name))
    
# Convert the dictionaries to a pandas DataFrame
df = pd.DataFrame(data) [1::]
df = df[df["fZ"] == 5.]
df_copy = df
df = df[df["zFoton"] > 426]
# df = df[(df["fX"] **2  + df["fY"] **2 ) > 395**2]
# df = df[(df["fX"] **2  + df["fY"] **2 ) < 415**2]




print(df)
n = np.mean(df["n"])
r = np.mean(np.sqrt(df["fX"] **2 + df["fY"] **2))

n = df["n"]
r = np.sqrt(df["fX"] **2 + df["fY"] **2)
z = df["zFoton"] - 5

cos = np.cos(np.arctan(r/z))
E02 = 938.272**2
Ef = df["Ef"]


# vel = 0.5 * ( (n*cos*(n**2 - 1)*Ef) /(E02*( n**2 * cos**2 - 1)) + np.sqrt(  (  (n*cos*(n**2 - 1)*Ef) / (E02*(n**2 * cos**2 - 1)) )**2 - 4*( ((n**2 - 1)**2 * (Ef**2)/4) - E02) / (E02*(n**2 * cos**2 - 1))   ) )
# vel = np.sqrt(1/((n*cos)**2 - 1))
# print(vel)


print(f"""Mean values

    Radius = {r} mm
    n = {n}
    V = {1/(n* np.cos(np.arctan(r/z)))} c
    V = {np.mean(1/(n* np.cos(np.arctan(r/z))))} c
    
      """)

# Close the ROOT file
file.Close()

fig = plt.figure(figsize=(10,10))
plt.scatter(df_copy["fX"], df_copy["fY"], color = "red", s = 0.8, alpha = 0.7)
plt.scatter(df["fX"], df["fY"], color = "navy", s = 1.5)

plt.show()