import json
import random
from datetime import datetime

def generate_status():
    """
        message DeviceStatus {
            string deviceId = 1;
            bool isCharging = 2;
            uint32 percentCharged = 3;
            string timestamp = 4;
        }
    """
    status = {
        "deviceId": str(random.randint(0, 1000)),
        "isCharging": random.choice([True, False]),
        "percentCharged": random.randint(0, 100),
        "timestamp": datetime(year=2024, month=4, day=random.randint(1, 2), 
                              hour=random.randint(0, 23), minute=random.randint(0, 59), 
                              second=random.randint(0, 59)).strftime('%Y-%m-%dT%H:%M:%S')
    }
    return status

def generate_bulk_request(num_requests, outputJson):
    with open(outputJson, 'w') as jsonfile:
        for dataId in range(num_requests):

            # Construct the JSON document
            json_doc = {
                "index": {
                    "_index": "device_status_202404",
                    "_id": dataId  # Use timestamp as unique id
                }
            } 
            jsonfile.write(json.dumps(json_doc) + '\n')
            jsonfile.write(json.dumps(generate_status()) + '\n')

if __name__ == "__main__":
    num_requests = 2000  # Change this to the number of requests you want in the bulk request
    generate_bulk_request(num_requests, "device_status.json")