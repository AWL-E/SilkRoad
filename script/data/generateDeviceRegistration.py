import json
import random
from datetime import datetime

def generate_registration(deviceId):

    """
        message DeviceManufactureEvent {
            string deviceId = 1;
            string deviceType = 2;
            string manufacturerModel = 3;
            uint32 timestamp = 4;
        }
    """
    deviceType = str(random.choice(['Transmitter', 'Transmitter', 'Transmitter', 'Transmitter', 'Receiver', 'Receiver', 'Receiver', 'Receiver', 'Receiver', 'Receiver']))
    registration = {
        "deviceId": str(deviceId),
        "deviceType": deviceType,
        "manufacturerModel": random.choice(['TurboCruiser Maxima', 'PowerPacer Elite', 'ElectraDrive Navigator', 'ElectraDrive Navigator', 'SwiftCruise Ultra', 'SwiftCruise Ultra', 'SwiftCruise Ultra']) if deviceType == 'Receiver' else 'Agile Station transmitter',
        "timestamp": datetime(year=2024, month=3, day=random.randint(1, 31), 
                              hour=random.randint(0, 23), minute=random.randint(0, 59), 
                              second=random.randint(0, 59)).strftime('%Y-%m-%dT%H:%M:%S')
    }
    return registration

def generate_bulk_request(num_requests, outputJson):
    with open(outputJson, 'w') as jsonfile:
        for dataId in range(num_requests):

            # Construct the JSON document
            json_doc = {
                "index": {
                    "_index": "device_registration_2024_03",
                    "_id": dataId  # Use timestamp as unique id
                }
            } 
            jsonfile.write(json.dumps(json_doc) + '\n')
            jsonfile.write(json.dumps(generate_registration(dataId)) + '\n')

if __name__ == "__main__":
    num_requests = 1000  # Change this to the number of requests you want in the bulk request
    generate_bulk_request(num_requests, "registration.json")
