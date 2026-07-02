import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load the C output

df = pd.read_csv("Ex2.csv")
error = abs(df['pi_estimate'] - np.pi)
plt.plot(df['n'], error, color='b', label='Error in pi estimate')



plt.xlabel('n events')
plt.ylabel('Error')
plt.yscale('log')
plt.xscale('log')

plt.title('Error pi estimate')
plt.legend()

# Save the figure directly without calling plt.show()
plt.savefig("Ex2_plot.png")