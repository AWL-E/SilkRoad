import csv
import numpy as np

def generate_random_coordinates(center, std_dev_range, num_coords, output_file):
    """
    Generate random coordinates around a given center point using normal distribution and write them to a CSV file.

    Args:
    - center (tuple): The center coordinate (x, y).
    - std_dev_range (tuple): Range for standard deviation (min_std_dev, max_std_dev).
    - num_coords (int): Number of random coordinates to generate.
    - output_file (str): Name of the CSV file to write.

    Returns:
    None
    """
    x_center, y_center = center
    min_std_dev, max_std_dev = std_dev_range
    std_dev = np.random.uniform(min_std_dev, max_std_dev)
    
    x_coords = np.random.normal(x_center, std_dev, num_coords)
    y_coords = np.random.normal(y_center, std_dev, num_coords)
    
    with open(output_file, 'a', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for x, y in zip(x_coords, y_coords):
            writer.writerow([x, y])

def clear_csv_file(file_path):
    with open(file_path, 'w') as file:
        file.truncate(0)

    with open(file_path, mode='a', newline='') as csv_file:
        fieldnames = ['lat', 'lon']
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()

# Example usage:
output_file = 'coordinates.csv'
clear_csv_file(output_file)
std_dev_range = (0.0001, 0.001)
num_random_coords = 1000

center_point = (28.478565667918506, -81.47084564861488)
generate_random_coordinates(center_point, std_dev_range, num_random_coords, output_file)

center_point = (28.478565627918506, -81.47074564861488)
generate_random_coordinates(center_point, std_dev_range, num_random_coords, output_file)

center_point = (28.476566627918506, -81.47054564861488)
generate_random_coordinates(center_point, std_dev_range, num_random_coords, output_file)

center_point = (28.479565667918506, -81.47284564861488)
generate_random_coordinates(center_point, std_dev_range, num_random_coords, output_file)

center_point = (28.478575627918506, -81.47076564861488)
generate_random_coordinates(center_point, std_dev_range, num_random_coords, output_file)

center_point = (28.476766627918506, -81.47055564861488)
generate_random_coordinates(center_point, std_dev_range, num_random_coords, output_file)