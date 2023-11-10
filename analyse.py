import os
import sys
import pandas as pd
import matplotlib.pyplot as plt
import re
import numpy as np
from scipy.stats import norm
from sklearn.linear_model import LinearRegression

marker_size = 2

def extract_number_from_string(input_string):
    # Define a regular expression pattern to match numbers
    pattern = r'\d+'

    # Use re.findall to extract all numbers from the input string
    numbers = re.findall(pattern, input_string)

    # If there are numbers, convert the first one to an integer and return it
    if numbers:
        return int(numbers[0])
    else:
        return None  # Return None if no numbers are found


def get_file_names(folder_path):
    # Check if the provided path is a directory
    if not os.path.isdir(folder_path):
        print(f"{folder_path} is not a valid directory.")
        return []

    # Get all files in the directory
    files = os.listdir(folder_path)

    # Filter out directories, keep only files
    file_names = [file for file in files if os.path.isfile(os.path.join(folder_path, file))]

    return file_names



def analyse_files(folder_path):

    stats = open(folder_path+"/stats/stats.csv", "w")
    stats.write("index,valore,media,devstd\n")
    i = 0


    for x in get_file_names(folder_path=folder_path):  # x is a std measure
        file_path = folder_path+"/"+ x
        # STEP 1: REMOVE COMMA
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
                    updated_line = (
                        line.rstrip()[:-1] + "\n"
                    )  # Remove last character (comma) and add newline
                    output_file.write(updated_line)
                else:
                    # If there is no trailing comma, write the line as it is to the output file
                    output_file.write(line)

        # print("Last comma removed from each row. Output written to 'output_file.txt'")

        # Step 2: Read the CSV File
        print("Analysing: " + file_path)
        df = pd.read_csv(file_path)  # Replace 'your_file.csv' with the actual file path
        #Step 4: Create Plots
        plt.plot(
            df["index"].astype(int),
            df["distance"].astype(float),
            marker="o",
            linestyle="-",
            linewidth=0.5,
            markersize=marker_size,
            color="b",
        )
        plt.title(x)
        plt.xlabel("Indice misura")
        plt.ylabel("Distanza misurata in mm")
        plt.ylim(0,200)
        plt.tight_layout() 
        plt.grid(True)  # Optional: Add grid lines

        # Step 5: Show or Save the Plot (Optional)
        
        distance_stats = df["distance"].describe()
        min_value = distance_stats["min"]
        max_value = distance_stats["max"]
        mean_distance = distance_stats["mean"]
        median_distance = distance_stats["50%"]  # 50% corresponds to the median
        std_dev_distance = distance_stats["std"]
        tag_text = f'Mean: {mean_distance:.2f}\nStd Dev: {std_dev_distance:.2f}\nMin: {min_value:.2f}\nMax: {max_value:.2f}'

        plt.annotate(tag_text,
             xy=(1, 1), xycoords='axes fraction',
             xytext=(-10, -10), textcoords='offset points',
             ha='right', va='top',
             bbox=dict(boxstyle='round,pad=0.3', edgecolor='black', facecolor='white'),
             fontsize=10)
        plt.savefig(folder_path +"/plots/plot_" + x + ".png")
        # print(
        #     distance_stats
        # )
        
        misura = extract_number_from_string(x)

        stats.write(str(i) + "," + str(misura) + "," + str(mean_distance) + "," + str(std_dev_distance)+ '\n')
        i+=1
        plt.close()
        
        x_values = np.linspace(0, 255, 5000)

        # Calculate the corresponding y values for the Gaussian distribution
        desired_tollerance = 5
        y_values = norm.pdf(x_values, misura, desired_tollerance/3)
        y_values_m = norm.pdf(x_values, mean_distance, std_dev_distance)


        plt.hist(df["distance"].astype(float), bins=20, color="skyblue", edgecolor="black",density= True, stacked = True)
        plt.plot(x_values, y_values, 'r-', label='Desired distribution')
        plt.plot(x_values, y_values_m, 'b-', label='Measured distribution')
        plt.legend()

        plt.xlim(min_value,max(misura,max_value) + desired_tollerance)

        # Add labels and title
        plt.xlabel("Valore misura mm")
        plt.ylabel("Probabilità")
        plt.title("Distribuzione dei valori")
        plt.tight_layout() 
        plt.savefig(folder_path + "/plots/histogram_" + x + ".png")
        plt.close()
        # plt.show()

    stats.close()
    stats_df = pd.read_csv(folder_path + "/stats/stats.csv")
    errors = abs(stats_df['media'].astype(float) - stats_df['valore'].astype(float))
    
    model = LinearRegression()
    model.fit(X=stats_df["valore"].values.reshape(-1,1),y= stats_df["media"].values,)
    slope = model.coef_[0]
    intercept = model.intercept_
    predicted_values = model.predict(stats_df["valore"].values.reshape(-1,1))
    
    
    
    plt.figure(figsize=(10, 6))  # Optional: Set the figure size
    equation = f'Y = {slope:.2f}X + {intercept:.2f}'
    plt.text(0.8, 0.9, equation, ha='center', va='center', transform=plt.gca().transAxes, fontsize=10, bbox=dict(facecolor='white', alpha=0.5))

    plt.plot(
        stats_df["valore"], 
        predicted_values,
        color='brown',
        label='Linear Regression Curve',
        linestyle="-",
        linewidth=2,
             )
    plt.plot(
        stats_df["valore"].astype(float),
        stats_df["valore"].astype(float),
        marker="x",
        linestyle="-",
        linewidth=2,
        markersize=marker_size,
        color="black",
        label = "valore misurato mm",
    )
    plt.plot(
        stats_df["valore"].astype(float),
        stats_df["media"].astype(float),
        marker="o",
        linestyle="-",
        linewidth=0.5,
        markersize=marker_size,
        color="b",
        label = "media misure mm",
    )
    plt.plot(
        stats_df["valore"].astype(float),
        stats_df["devstd"].astype(float),
        marker="o",
        linestyle="-",
        linewidth=0.5,
        markersize= marker_size,
        color="r",
        label = "deviazione standard mm",
    )
    plt.plot(
        stats_df["valore"].astype(float),
        errors,
        marker="o",
        linestyle="-",
        linewidth=0.5,
        markersize=marker_size,
        color="green",
        label = "errore assoluto tra media e riferimento  mm",
    )
    plt.xlabel("misura aspettata mm")
    plt.ylabel("media misurata mm")
    plt.legend()
    plt.grid(True)  # Optional: Add grid lines

    # Step 5: Show or Save the Plot (Optional)
    plt.savefig(folder_path+"/plots/stats_plot.png")
    print(stats_df["devstd"].describe())
    print("La deviazione standard media in mm: " + str(stats_df["devstd"].describe()["mean"]))
    plt.show()
    plt.close()



def main():
    # Check if a folder path is provided as a command-line argument
    if len(sys.argv) != 2:
        print("Usage: python script.py /path/to/your/folder")
        sys.exit(1)
    # Get the folder path from the command-line argument
    folder_path = sys.argv[1]
    analyse_files(folder_path)

if __name__ == "__main__":
    main()