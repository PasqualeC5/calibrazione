import pandas as pd
import matplotlib.pyplot as plt

# read file of misure standard
f = open("misure_da_prendere.txt", "r")
stats = open("misure/stats.csv", "w")
stats.write("index,media,devstd\n")
measures_spoilt = f.readlines()  # newline to remove

# Removing newline character from string
measures = []
i = 0
for sub in measures_spoilt:
    measures.append(sub.replace("\n", ""))


for x in measures:  # x is a std measure
    file_path = "misure/prova" + x + "00000.csv"
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
    df = pd.read_csv(file_path)  # Replace 'your_file.csv' with the actual file path
    # #Step 4: Create Plots
    # plt.figure(figsize=(10, 6))  # Optional: Set the figure size
    # plt.plot(
    #     df["index"].astype(int),
    #     df["distance"].astype(float),
    #     marker="o",
    #     linestyle="-",
    #     color="b",
    # )
    # plt.title("Misura a " + x + " cm")
    # plt.xlabel("indice i")
    # plt.ylabel("distanza cm")
    # plt.grid(True)  # Optional: Add grid lines

    # # Step 5: Show or Save the Plot (Optional)
    # plt.savefig("plots/output_plot_" + x + ".png")
    # Calculate descriptive statistics for the 'distance' column
    distance_stats = df["distance"].describe()
    mean_distance = distance_stats["mean"]
    median_distance = distance_stats["50%"]  # 50% corresponds to the median
    std_dev_distance = distance_stats["std"]

    print(
        distance_stats
    )
    

    stats.write(str(float(x)/100.0) + "," + str(mean_distance) + "," + str(std_dev_distance)+ '\n')
    i+=1
    # Save the plot as PNG file
    #plt.show()

    plt.hist(df["distance"], bins=20, color="skyblue", edgecolor="black")
    

    # Add labels and title
    plt.xlabel("X-axis label")
    plt.ylabel("Y-axis label")
    plt.title("Histogram of Data")
    plt.savefig("plots/output_plot_" + x + "_histogram.png")
    # plt.show()

stats.close()
plt.figure().clear()
stats_df = pd.read_csv("misure/stats.csv")
plt.figure(figsize=(10, 6))  # Optional: Set the figure size
plt.plot(
    stats_df["index"].astype(float),
    stats_df["media"].astype(float),
    marker="o",
    linestyle="-",
    color="b",
)
plt.plot(
    stats_df["index"].astype(float),
    stats_df["devstd"].astype(float),
    marker="o",
    linestyle="-",
    color="r",
)
plt.xlabel("indice")
plt.ylabel("stats")
plt.grid(True)  # Optional: Add grid lines

# Step 5: Show or Save the Plot (Optional)
plt.savefig("plots/stats_plot.png")
plt.show()
