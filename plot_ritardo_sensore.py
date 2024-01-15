import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

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

def plot_csv_data(*files, rolling_window=1):
    # Check if at least one file is provided
    if not files:
        print("Error: At least one CSV file must be provided.")
        return

    # Create an empty DataFrame to hold the combined data
    combined_df = pd.DataFrame()

    # Read each CSV file and append its data to the combined DataFrame
    for file in files:
        remove_trailing_commas(file)
        df = pd.read_csv(file)
        if 'time' not in df.columns or 'value' not in df.columns:
            print(f"Error: 'time' and 'value' columns not found in {file}")
            return
        combined_df = pd.concat([combined_df, df], axis=0)

    # Apply rolling mean to smooth the data
    combined_df['smoothed_value'] = combined_df['value'].rolling(
        window=rolling_window).mean()

    # Plot the data
    plt.figure(figsize=(12, 8))

    # Plot each file's data
    for file in files:
        df = pd.read_csv(file)
        plt.subplot(2, 1, 1)
        plt.plot(df['time'], df['value'], label=f'{file}')
        plt.xlabel('Time')
        plt.ylabel('Value')
        plt.title('Comparison of CSV Files')
        plt.legend()
        plt.grid(True)

        # Plot Fourier spectrum
        plt.subplot(2, 1, 2)
        values = df['value']
        fourier_transform = np.fft.fft(values)
        frequencies = np.fft.fftfreq(len(fourier_transform))
        plt.plot(frequencies, np.abs(fourier_transform), label=f'{file}')
        plt.xlabel('Frequency')
        plt.ylabel('Amplitude')
        plt.title('Fourier Spectrum')
        plt.legend()
        plt.grid(True)

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    # Replace 'file1.csv', 'file2.csv', etc. with your actual CSV file paths
    csv_files = ['delay/position_response',
                 'delay/sensor_response', 'delay/velocity_control']

    plot_csv_data(*csv_files)
