import json
import random
from datetime import datetime

def generate_notification():
    notification = {
        "type": str(random.choice(['Battery below 20%', 'Battery below 10%', 'Battery is fully charged', 'Out of perimeter'])),
        "timestamp": datetime(year=2024, month=4, day=random.randint(1, 2), 
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
                    "_index": "notification_2024_04",
                    "_id": dataId  # Use timestamp as unique id
                }
            } 
            jsonfile.write(json.dumps(json_doc) + '\n')
            jsonfile.write(json.dumps(generate_notification()) + '\n')

if __name__ == "__main__":
    num_requests = 10000  # Change this to the number of requests you want in the bulk request
    generate_bulk_request(num_requests, "notification.json")