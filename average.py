import csv

# Assuming the CSV data is stored in a file named 'distances.csv'
file_path = 'misura20.csv'

# Read the CSV file and calculate the average distance
with open(file_path, 'r') as file:
    reader = csv.DictReader(file)
    distances = [int(row['distance']) for row in reader]

average_distance = sum(distances) / len(distances)

print(f'The average distance is: {average_distance}')
