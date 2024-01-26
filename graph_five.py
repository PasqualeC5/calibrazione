import matplotlib.pyplot as plt
import numpy as np

# Generate some sample data for the lines
x = np.linspace(50, 100, 100)  # 100 points between 0 and 10

# Define 5 different functions for the lines
y1 = 1.01*x + 6.58
y2 = 1.02*x + 6.36
y3 = 1.01*x + 11.80
y4 = 1.01*x + 10.43
y5 = 1.01*x + 9.57

# Plot the lines on the same graph
plt.plot(x, y1, label='blocco alluminio')
plt.plot(x, y2, label='plastica riflettente')
plt.plot(x, y3, label='cartoncino bianco')
plt.plot(x, y4, label='cartoncino nero')
plt.plot(x, y5, label='cartone industriale')

# Add labels and legend
plt.xlabel('misura attesa[mm]')
plt.ylabel('misura ottenuta[mm]')
plt.title('Confronto best fit')
plt.legend()

# Display the plot
plt.savefig('five_plot.png')  
plt.show()