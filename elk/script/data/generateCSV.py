import csv
import random
from datetime import datetime, timedelta
import matplotlib.pyplot as plt
import json
import requests

def divide_interval(total_interval):
    intervals = []

    min_sub_interval_size = 200
    max_sub_interval_size = 800

    while total_interval > 0:
        # Generate a random sub-interval size between min and max
        sub_interval_size = random.randint(min_sub_interval_size, max_sub_interval_size)
        
        # Adjust sub-interval size if it exceeds the remaining total interval
        sub_interval_size = min(sub_interval_size, total_interval)

        # Add the sub-interval to the list
        intervals.append(sub_interval_size)

        # Update the remaining total interval
        total_interval -= sub_interval_size
    print(intervals)
    print(sum(intervals))

    return intervals

def generate_sequence(N_steps):
    sequence = []
    steps = divide_interval(N_steps)

    for _ in range(len(steps)):
        entry = {}
        entry['steps'] = steps.pop(0)

        choice = random.choice(['charge', 'discharge', 'plateau'])
        entry['type'] = choice

        if  choice == 'charge':
            entry['rateHour'] = random.randint(4, 8)
            entry['noise'] = random.uniform(0.1, 0.4)

        elif choice == 'plateau':
            entry['noise'] = random.uniform(0.05, 0.15)

        else:
            entry['rateHour'] = random.randint(8, 12)
            entry['noise'] = random.uniform(0.3, 0.7)

        sequence.append(entry)

    return sequence

def generate_battery_data2(device_id,steps, initial_voltage_value):
    timestamp = 0
    voltage = initial_voltage_value
    data = []

    for step in steps:
        step_type = step['type']
        noise = step.get('noise', 0)
        rate_hour = step.get('rateHour', 0)
        num_steps = step.get('steps', 0)
        rate_minute = rate_hour / 60

        for _ in range(num_steps):
            if step_type == 'discharge':
                voltage -= rate_minute + random.uniform(-noise, noise)
                voltage = max(0, voltage)
            elif step_type == 'charge':
                voltage += rate_minute + random.choice([-noise, -noise, -noise, -noise, -noise, noise ,noise])
                voltage = min(100, voltage)
            elif step_type == 'plateau':
                voltage += random.uniform(-noise, noise)

            timestamp += 1
            row = {
                'deviceID': device_id,
                'batteryVoltage': round(voltage, 2),
                'timestamp': timestamp
            }
            data.append(row)

    return data

def clear_csv_file(file_path):
    with open(file_path, 'w') as file:
        file.truncate(0)

    with open(file_path, mode='a', newline='') as csv_file:
        fieldnames = ['deviceID', 'batteryVoltage', 'timestamp']
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()

def append_to_file(file_path, content):
    with open(file_path, mode='a', newline='') as csv_file:
        fieldnames = ['deviceID', 'batteryVoltage', 'timestamp']
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writerows(content)

def write_header_to_csv(file_path, data):
    with open(file_path, mode='a', newline='') as csv_file:
        fieldnames = ['deviceID', 'batteryVoltage', 'timestamp']
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

        writer.writeheader()
        writer.writerows(data)

def write_to_csv(data, file_path):
    with open(file_path, mode='w', newline='') as csv_file:
        fieldnames = ['deviceID', 'batteryVoltage', 'timestamp']
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

        writer.writeheader()
        writer.writerows(data)

def plot_battery_data(device_data_list):
    plt.figure(figsize=(12, 6))

    for i, device_data in enumerate(device_data_list):
        timestamps = [entry['timestamp'] for entry in device_data]
        battery_voltage = [entry['batteryVoltage'] for entry in device_data]

        plt.plot(timestamps, battery_voltage, label=f'Device {i + 1}')

    plt.xlabel('Time')
    plt.ylabel('Battery Voltage (%)')
    plt.title('Battery Voltage Over Time')
    plt.legend()
    plt.ylim(0, 110)  # Set Y-axis limits
    plt.show()

if __name__ == "__main__":
    csv_file_path = "battery_simulation.csv"
    clear_csv_file(csv_file_path)

    sequences_devices_battery = []

    for i in range(0,12):
        steps = 3000
        initial_voltage = random.randint(0, 100)

        print(f"Device'{i}'")
        print(f"Steps '{steps}'")
        print(f"Starts at '{initial_voltage}%'")

        sequence = generate_sequence(steps)
        data = generate_battery_data2(f"Device'{i}'", sequence, initial_voltage)
        append_to_file(csv_file_path, data)

        sequences_devices_battery.append(data)

