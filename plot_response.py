# PURPOSE: this script analyse data-sensor

import os  # interation with operating system
import sys  # interation with operating system
import pandas as pd  # draw graph
import matplotlib.pyplot as plt  # draw graph
# import re  # support for working with regular expression (string)
# import numpy as np  # support for working with multidimension variables (array)
# from scipy.stats import norm  # probability and statistic
# from sklearn.linear_model import LinearRegression  # for best fit
import numpy as np
from scipy.signal import savgol_filter, butter, filtfilt


# marker_size = 2

def remove_trailing_commas(file_path):
    # Open the input file in read mode
    with open(file_path, "r") as input_file:
        # Read lines from the input file
        lines = input_file.readlines()

    # Open the output file in write mode
    with open(file_path, "w") as output_file:
        # Iterate through each line and remove the last comma if it exists
        for line in lines:
            # Remove trailing whitespace and check if the last character is a comma
            if line.rstrip().endswith(","):
                # Remove the last comma and write the updated line to the output file
                # Remove last character (comma) and add newline
                updated_line = line.rstrip()[:-1] + "\n"
                output_file.write(updated_line)
            else:
                # If there is no trailing comma, write the line as it is to the output file
                output_file.write(line)


def analyse_file(file_path):
    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(file_path)

    # Assuming the CSV file has two columns named 'x' and 'y'
    x_values = df['time']
    y_values = df['value']
    if (file_path == "control/velocity_response"):
        y_values = [20 if num > 20 else num for num in y_values]

    # Plotting the data
    plt.subplot(3, 1, 1)
    plt.plot(x_values, y_values, marker='.', markersize=0.2,
             linestyle='-', color='b', linewidth=0.3,)

    # Adding labels and title
    plt.xlabel('time[s]')
    plt.ylabel('velocity[mm/s]')
    plt.title(file_path)

    if (file_path == "control/position_response"):
        window_size = 50  # Adjust the window size based on your data characteristics
        poly_order = 1
        dy_dx = np.gradient(y_values, x_values)
        filtered_derivative = savgol_filter(dy_dx, window_size, poly_order)
        
        plt.subplot(3, 1, 2)
        plt.plot(x_values, dy_dx, label='Derivative')
        plt.title('Derivative of the Vector')
        plt.xlabel('x')
        plt.ylabel('dy/dx')
        plt.legend()
        plt.subplot(3, 1, 3)
        plt.plot(x_values, filtered_derivative,
                 label=f'Filtered Derivative (Savitzky-Golay)')
        plt.title('Filtered Derivative')
        plt.xlabel('x')
        plt.ylabel('Filtered dy/dx')
        plt.legend()
        

# Apply the filter to the derivative


    # Show the plot
    plt.show()


def main():
    # remove_trailing_commas("control/velocity_control")
    # remove_trailing_commas("control/velocity_response")
    remove_trailing_commas("control/position_response")

    # analyse_file("control/velocity_control")
    # analyse_file("control/velocity_response")
    analyse_file("control/position_response")


if __name__ == "__main__":
    main()
