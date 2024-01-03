#purpose: this script analyse the control system response

import os  # interation with operating system
import sys  # interation with operating system
import pandas as pd  # draw graph
import matplotlib.pyplot as plt  # draw graph
#import re  # support for working with regular expression (string)
#import numpy as np  # support for working with multidimension variables (array)
#from scipy.stats import norm  # probability and statistic
#from sklearn.linear_model import LinearRegression  # for best fit


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
    x_values = df['time']
    y_values = df['distance']

    #plot
    plt.plot(x_values, y_values)
    plt.title("Control system")
    plt.xlabel("time[s]")
    plt.ylabel("Distance[mm]")
    plt.ylim(0, 255)
    plt.tight_layout()
    plt.grid(True)
    
    
def main():
    analyse_file("data_test.csv")


if __name__ == "__main__":
    main()


