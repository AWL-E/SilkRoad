import json
import random
from datetime import datetime

# Génère un faux message d'enregistrement
def generate_registration(deviceId):
    # Distribution inégale
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

# Génère une multitude de faux messages dans un fichier JSON
# Ce fichier peut être donné à OpenSearch
def generate_bulk_request(num_requests, outputJson):
    with open(outputJson, 'w') as jsonfile:
        for dataId in range(num_requests):

            json_doc = {
                "index": {
                    "_index": "device_registration_2024_03",
                    "_id": dataId 
                }
            } 
            jsonfile.write(json.dumps(json_doc) + '\n')
            jsonfile.write(json.dumps(generate_registration(dataId)) + '\n')

# Modifier les paramètres
if __name__ == "__main__":
    num_requests = 1000
    generate_bulk_request(num_requests, "registration.json")
