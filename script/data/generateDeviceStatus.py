import json
import random
from datetime import datetime

# Génère un faux statut d'appareil
def generate_status():
    status = {
        "deviceId": str(random.randint(0, 1000)),
        "isCharging": random.choice([True, False]),
        "percentCharged": random.randint(0, 100),
        "timestamp": datetime(year=2024, month=4, day=random.randint(1, 2), 
                              hour=random.randint(0, 23), minute=random.randint(0, 59), 
                              second=random.randint(0, 59)).strftime('%Y-%m-%dT%H:%M:%S')
    }
    return status

# Génère une multitude de faux messages dans un fichier JSON
# Ce fichier peut être donné à OpenSearch
def generate_bulk_request(num_requests, outputJson):
    with open(outputJson, 'w') as jsonfile:
        for dataId in range(num_requests):

            json_doc = {
                "index": {
                    "_index": "device_status_202404",
                    "_id": dataId 
                }
            } 
            jsonfile.write(json.dumps(json_doc) + '\n')
            jsonfile.write(json.dumps(generate_status()) + '\n')

# Modifier les paramètres
if __name__ == "__main__":
    num_requests = 2000 
    generate_bulk_request(num_requests, "device_status.json")