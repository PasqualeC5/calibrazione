# PURPOSE: this script find the transfer function of the system using open loop calibration technique
# in particular we found T and Tau


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
import csv


def find_Tau(folder_path, file_name):

    file_path = folder_path + "/" + file_name

    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(file_path)

    # Assuming the CSV file has two columns named 'time' and 'value'
    x_values = df['time']
    y_values = df['value']

    # Rounding to zero the infinitesimal value (|| < 1e-4 m)
    for index, value in enumerate(y_values[0:], start=0):
        if abs(value) < 1e-4:
            y_values[index] = round(abs(value))


    # Store the first element as the initial value to compare
    # Prepare to find index of rise
    initial_value = y_values[0]
    index_of_rise = -1

    # Iterate through the vector starting from the second element
    for index, value in enumerate(y_values[1:], start=1):
        if value != initial_value:
            # Found a different value
            index_of_rise = index - 1
            break
    
    # Computed delay
    return x_values[index_of_rise]


def find_T(folder_path):
    # Get the file path where take data
    file_path = folder_path + "/velocity_response_computed_filtered"

    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(file_path)

    # Assuming the CSV file has two columns named 'time' and 'value'
    x_values = df['time']
    y_values = df['value']

    # Extract the first N elements (indicial response)
    N = 500
    x_values = x_values[:N]
    y_values = y_values[:N]


    # Plotting the graph
    plt.plot(x_values, y_values, linestyle='-', color='b', label='Indicial response')
    plt.show()


def main():
    
    # Check if a folder path is provided as a command-line argument
    if len(sys.argv) != 2:
        print("Usage: python script.py /folder_to_analyse")
        sys.exit(1)
    # Get the folder path from the command-line argument
    folder_path = sys.argv[1]


    # Compute
    Tau = find_Tau(folder_path, "position_response_computed")
    T = find_T((folder_path, "position_response_computed"))
    




if __name__ == "__main__":
    main()



