import pandas as pd
import matplotlib.pyplot as plt

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

def plot_csv_data(file1, file2):
    # Read CSV files into Pandas DataFrames
    df1 = pd.read_csv(file1)
    df2 = pd.read_csv(file2)

    # Check if the columns 'time' and 'value' exist in both DataFrames
    if 'time' not in df1.columns or 'value' not in df1.columns:
        print(f"Error: 'time' and 'value' columns not found in {file1}")
        return
    if 'time' not in df2.columns or 'value' not in df2.columns:
        print(f"Error: 'time' and 'value' columns not found in {file2}")
        return

    # Plot the data
    plt.figure(figsize=(10, 6))
    plt.plot(df1['time'], df1['value'], label='File 1')
    plt.plot(df2['time'], df2['value'], label='File 2')
    plt.xlabel('Time')
    plt.ylabel('Value')
    plt.title('Comparison of CSV Files')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    # Replace 'file1.csv' and 'file2.csv' with your actual CSV file paths
    csv_file1 = 'delay/position_response'
    csv_file2 = 'delay/sensor_response'
    remove_trailing_commas(csv_file1)
    remove_trailing_commas(csv_file2)

    plot_csv_data(csv_file1, csv_file2)
