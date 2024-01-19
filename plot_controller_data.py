# purpose: this script analyse the control system response

import os  # interation with operating system
import sys  # interation with operating system
import pandas as pd  # draw graph
import matplotlib.pyplot as plt  # draw graph
# import re  # support for working with regular expression (string)
# import numpy as np  # support for working with multidimension variables (array)
# from scipy.stats import norm  # probability and statistic
# from sklearn.linear_model import LinearRegression  # for best fit


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

    # REMOVE TRAILING COMMAS
    remove_trailing_commas(file_path)

    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(file_path)

    # Assuming the CSV file has two columns named 'time' and 'value'
    time = df['time']
    reference = df['reference']
    measured_distance = df['measured_distance']
    error = df['error']
    velocity_control = df['velocity_control']

    plt.figure(1)

    plt.subplot(2, 2, 1)
    plt.plot(time, -reference, label='Reference [mm]')
    plt.xlabel('Time [s]')
    plt.ylabel('Reference [mm]')
    plt.legend(loc='best')

    plt.subplot(2, 2, 2)
    plt.plot(time, -measured_distance,
             label='Measured Distance [mm]')
    plt.xlabel('Time [s]')
    plt.ylabel('Measured distance [mm]')
    plt.legend(loc='best')

    plt.subplot(2, 2, 3)
    plt.plot(time, error, label='Error [mm]')
    plt.xlabel('Time [s]')
    plt.ylabel('Error [mm]')
    plt.legend(loc='best')

    plt.subplot(2, 2, 4)
    plt.plot(time, velocity_control,
             label='Velocity Control [mm/s]')
    plt.xlabel('Time [s]')
    plt.ylabel('Velocity control [mm/s]')
    plt.legend(loc='best')

    plt.figure(2)

    plt.plot(time, -reference, label='Reference [mm]')

    plt.plot(time, -measured_distance,
             label='Measured Distance [mm]')

    plt.plot(time, error, label='Error [mm]')

    plt.plot(time, velocity_control,
             label='Velocity Control [mm/s]')

    plt.xlabel('Time [s]')
    plt.legend(loc='best')

    plt.show()

    plt.tight_layout()
    plt.grid(True)


def main():
    analyse_file("../test_closed_loop/data_test.csv")


if __name__ == "__main__":
    main()
