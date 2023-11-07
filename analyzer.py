import pandas as pd
import matplotlib.pyplot as plt

#read file of misure standard
f = open("misure_da_prendere.txt", "r")
measures_spoilt = f.readlines()             #newline to remove

# Removing newline character from string
measures = []
for sub in measures_spoilt:
    measures.append(sub.replace("\n", ""))


for x in measures:          #x is a std measure

    file_path = "prova" + x + "00000.csv"
    #STEP 1: REMOVE COMMA 
    # Open the input file in read mode
    
    with open(file_path, 'r') as input_file:
        # Read lines from the input file
        lines = input_file.readlines()

    # Open the output file in write mode
    with open(file_path, 'w') as output_file:
        # Iterate through each line and remove the last comma if it exists
        for line in lines:
            # Remove trailing whitespace and check if the last character is a comma
            if line.rstrip().endswith(','):
                # Remove the last comma and write the updated line to the output file
                updated_line = line.rstrip()[:-1] + '\n'  # Remove last character (comma) and add newline
                output_file.write(updated_line)
            else:
                # If there is no trailing comma, write the line as it is to the output file
                output_file.write(line)

    #print("Last comma removed from each row. Output written to 'output_file.txt'")


    # Step 2: Read the CSV File
    df = pd.read_csv(file_path)  # Replace 'your_file.csv' with the actual file path
    # Step 4: Create Plots
    plt.figure(figsize=(10, 6))  # Optional: Set the figure size
    plt.plot(df['index'].astype(int), df['distance'].astype(float), marker='o', linestyle='-', color='b')
    plt.title('Misura a' + x +' cm')
    plt.xlabel('indice i')
    plt.ylabel('distanza cm')
    plt.grid(True)  # Optional: Add grid lines




    # Step 5: Show or Save the Plot (Optional)
    plt.savefig('output_plot' + x + '.png')
    # Calculate descriptive statistics for the 'distance' column
    distance_stats = df['distance'].describe()
    mean_distance = distance_stats['mean']
    median_distance = distance_stats['50%']  # 50% corresponds to the median
    std_dev_distance = distance_stats['std']

    print(distance_stats, mean_distance, median_distance, std_dev_distance)  # Save the plot as PNG file
    plt.show()


    plt.hist(df['distance'], bins=10, color='skyblue', edgecolor='black')

    # Add labels and title
    plt.xlabel('X-axis label')
    plt.ylabel('Y-axis label')
    plt.title('Histogram of Data')
    plt.show()