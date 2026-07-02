import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load the C output

df = pd.read_csv("Ex1.csv")
mean = df['heads']/df['n']
plt.plot(df['n'], mean, color='b', label='Mean heads fraction')



plt.xlabel('n events')
plt.ylabel('heads fraction')
plt.xscale('log')

plt.title('Mean heads fraction')
plt.legend()

# Save the figure directly without calling plt.show()
plt.savefig("Ex1_plot.png")