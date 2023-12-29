# PURPOSE: this script find the transfer function of the system using open loop calibration technique

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


def main():
    
    # Get the file path where take data
    file_path = "control/velocity_response_computed_filtered" 

    
    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(file_path)

    # Assuming the CSV file has two columns named 'time' and 'value'
    x_values = df['time']
    y_values = df['value']

    # Extract the first N elements (indicial response)
    N = 500
    x_values = x_values[:N]
    y_values = y_values[:N]



