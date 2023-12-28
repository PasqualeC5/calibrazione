# PURPOSE: this script generates:
# 1 - the velocity-response derivating the position-response
# 2 - the filtered signal 1
# 3 - the filtered measured velocity-response (directly measured in rispostavelocita.cpp)

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


file_path = "control/position_response" 

# REMOVE FINAL COMMAS
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


#GENERATING velocity_response_computed

# Read the CSV file into a pandas DataFrame
df = pd.read_csv(file_path)

# Assuming the CSV file has two columns named 'time' and 'value'
x_values = df['time']
y_values = df['value']


# Compute derivative
dy_dx = np.gradient(y_values, x_values)


# write to file csv velocity_response_computed
file_to_write_path = 'control/velocity_response_computed'

# Write the data to the CSV file
data = list(zip(x_values, dy_dx))

with open(file_to_write_path, 'w', newline='') as csvfile:
    csv_writer = csv.writer(csvfile)
    
    # Write header (optional)
    csv_writer.writerow(['time', 'value'])
    
    # Write the data rows
    csv_writer.writerows(data)


#GENERATING velocity_response_computed_filtered
    
# Compute filtering 
window_size = 50  # Adjust the window size based on your data characteristics
poly_order = 1
filtered_derivative = savgol_filter(dy_dx, window_size, poly_order)

# write to file csv velocity_response_computed
file_to_write_path = 'control/velocity_response_computed_filtered'

# Write the data to the CSV file
data = list(zip(x_values, filtered_derivative))

with open(file_to_write_path, 'w', newline='') as csvfile:
    csv_writer = csv.writer(csvfile)
    
    # Write header (optional)
    csv_writer.writerow(['time', 'value'])
    
    # Write the data rows
    csv_writer.writerows(data)



#GENERATING velocity_response_filtered
    
file_path = "control/velocity_response" 

# Remove final commas of the datas


# Read the CSV file into a pandas DataFrame
df = pd.read_csv(file_path)

# Assuming the CSV file has two columns named 'time' and 'value'
x_values = df['time']
y_values = df['value']

# Compute filtering 
window_size = 50  # Adjust the window size based on your data characteristics
poly_order = 1
filtered_derivative = savgol_filter(y_values, window_size, poly_order)

# write to file csv velocity_response_computed
file_to_write_path = 'control/velocity_response_filtered'

# Write the data to the CSV file
data = list(zip(x_values, filtered_derivative))

with open(file_to_write_path, 'w', newline='') as csvfile:
    csv_writer = csv.writer(csvfile)
    
    # Write header (optional)
    csv_writer.writerow(['time', 'value'])
    
    # Write the data rows
    csv_writer.writerows(data)





        
        
    
