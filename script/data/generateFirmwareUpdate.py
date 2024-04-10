import json
import random
from datetime import datetime

# Génère une fausse alerte de mise à jour
def generate_data(version, deviceId):
    data = {
        "version": f'1.{version}.0',
        "timestamp": datetime(year=2023, month=version, day=random.randint(1, 28), 
                              hour=random.randint(0, 23), minute=random.randint(0, 59), 
                              second=random.randint(0, 59)).strftime('%Y-%m-%dT%H:%M:%S'),
        "deviceId": str(deviceId)
    }
    return data

# Génère une multitude de faux messages dans un fichier JSON
# Ce fichier peut être donné à OpenSearch
def generate_bulk_request(num_device, outputJson):

    with open(outputJson, 'w') as jsonfile:
        dataId = 0
        for deviceId in range(num_device):
            nb_update = random.randint(8,9)
            json_doc = {
                "index": {
                    "_index": "devices_firmware_version",
                    "_id": dataId
                }
            } 
            dataId = dataId + 1
            jsonfile.write(json.dumps(json_doc) + '\n')
            jsonfile.write(json.dumps(generate_data(nb_update + 1, deviceId)) + '\n')

if __name__ == "__main__":
    num_requests = 1000
    generate_bulk_request(num_requests, "./updates.json")
