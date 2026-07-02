import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



# Load the C output

df = pd.read_csv("Ex4_5.csv")
plt.hist(df['y'], density=True, bins=200 ,color='b', edgecolor='black', label='Y = -log(1-U)/1.5')

y_vals = np.linspace(0.005, 4.0, 100)
curve = 1.5 * np.exp(-1.5 * y_vals)
plt.plot(y_vals, curve, 'r-', linewidth=2, label=r'$1.5 e^{-1.5 y}$')

plt.xlabel('y values')
plt.ylabel('Frequency')
plt.title('Distribution of y = -log(1-U)/1.5')
plt.legend()

# Save the figure directly without calling plt.show()
plt.savefig("Ex4_plot.png")

plt.figure()
plt.plot(df['CDF_x'],df['CDF_y'],color='b',linewidth=2, label='Empirical CDF')

y_vals = np.linspace(0.001, 8.0, 100)
curve = 1.0 - np.exp(-1.5 * y_vals)

plt.plot(y_vals, curve, color='r', linestyle='--', linewidth=2, label=r'Theoretical CDF')

plt.xlabel('y values')
plt.ylabel('Frequency')
plt.title('Distribution of y = -log(1-U)/1.5')
plt.legend()

# Save the figure directly without calling plt.show()
plt.savefig("Ex5_plot.png")