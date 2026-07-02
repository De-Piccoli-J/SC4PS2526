import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



# Load the C output

df = pd.read_csv("Ex3.csv")
plt.hist(df['y'], density=True, bins=200 ,color='b', edgecolor='black', label='Y = U^2')

y_vals = np.linspace(0.005, 1.0, 100)
curve = 1 / (2 * np.sqrt(y_vals))
plt.plot(y_vals, curve, 'r-', linewidth=2, label=r'$\frac{1}{2\sqrt{y}}$')

plt.xlabel('y values')
plt.ylabel('Frequency')
plt.title('Distribution of y = u^2')
plt.legend()

# Save the figure directly without calling plt.show()
plt.savefig("Ex3_plot.png")