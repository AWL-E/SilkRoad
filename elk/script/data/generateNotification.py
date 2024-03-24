import json
import random
from datetime import datetime

def generate_notification():
    notification = {
        "type": str(random.randint(0, 5)),
        "timestamp": datetime(year=2023, month=random.randint(1, 12), day=random.randint(1, 28), 
                              hour=random.randint(0, 23), minute=random.randint(0, 59), 
                              second=random.randint(0, 59)).strftime('%Y-%m-%dT%H:%M:%S'),
        "deviceId": str(random.randint(0, 100))
    }
    return notification

def generate_bulk_request(num_requests, outputJson):
    with open(outputJson, 'w') as jsonfile:
        for dataId in range(num_requests):

            # Construct the JSON document
            json_doc = {
                "index": {
                    "_index": "location_20240317",
                    "_id": dataId  # Use timestamp as unique id
                }
            } 
            jsonfile.write(json.dumps(json_doc) + '\n')
            jsonfile.write(json.dumps(generate_notification()) + '\n')

if __name__ == "__main__":
    num_requests = 10000  # Change this to the number of requests you want in the bulk request
    generate_bulk_request(num_requests, "notification.json")
