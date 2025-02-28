import pandas as pd
import matplotlib.pyplot as plt

# Tree sizes used in the experiment
tree_sizes = [64, 128, 256]

# Plotting IPL trends for asymmetric vs symmetric deletion
plt.figure(figsize=(10, 6))

for size in tree_sizes:
    for method in ["asymmetric", "symmetric"]:
        # Load the CSV file
        df = pd.read_csv(f"{method}_{size}.csv")
        # Plot IPL trends
        plt.plot(df["Step"], df["IPL"], label=f"{method.capitalize()} - {size} nodes")

plt.xlabel("Number of Insertion/Deletion Pairs")
plt.ylabel("Internal Path Length (IPL)")
plt.title("IPL Trends for Asymmetric vs. Symmetric Deletion")
plt.legend()
plt.show()
