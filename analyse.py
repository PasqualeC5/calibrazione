import os
import sys
import pandas as pd
import matplotlib.pyplot as plt
import re

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
        plt.tight_layout() 
        plt.grid(True)  # Optional: Add grid lines

        # Step 5: Show or Save the Plot (Optional)
        plt.savefig(folder_path +"/plots/plot_" + x + ".png")
        distance_stats = df["distance"].describe()
        mean_distance = distance_stats["mean"]
        median_distance = distance_stats["50%"]  # 50% corresponds to the median
        std_dev_distance = distance_stats["std"]


        # print(
        #     distance_stats
        # )
        
        misura = extract_number_from_string(x)

        stats.write(str(i) + "," + str(misura) + "," + str(mean_distance) + "," + str(std_dev_distance)+ '\n')
        i+=1
        plt.close()

        plt.hist(df["distance"].astype(float), bins=20, color="skyblue", edgecolor="black",density= True)
        

        # Add labels and title
        plt.xlabel("Valore misura")
        plt.ylabel("Probabilità")
        plt.title("Distribuzione dei valori")
        plt.tight_layout() 
        plt.savefig(folder_path + "/plots/histogram_" + x + ".png")
        plt.close()
        # plt.show()

    stats.close()
    stats_df = pd.read_csv(folder_path + "/stats/stats.csv")
    errors = abs(stats_df['media'].astype(float) - stats_df['valore'].astype(float))

    plt.figure(figsize=(10, 6))  # Optional: Set the figure size
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