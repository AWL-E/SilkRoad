import csv
import json

"""
curl -XPOST -u 'admin:Awleonship!1' 'https://search-silkroad-test-cq3gzgphhaaiivvm7zua2fhaue.ca-central-1.es.amazonaws.com/_bulk' --data-binary @notification.json -H 'Content-Type: application/json'
curl -XPOST -u 'admin:Awleonship!1' 'https://search-silkroad-test-cq3gzgphhaaiivvm7zua2fhaue.ca-central-1.es.amazonaws.com/_bulk' --data-binary @device_status.json -H 'Content-Type: application/json'
curl -XPOST -u 'admin:Awleonship!1' 'https://search-silkroad-test-cq3gzgphhaaiivvm7zua2fhaue.ca-central-1.es.amazonaws.com/_bulk' --data-binary @notification.json -H 'Content-Type: application/json'
curl -XPOST -u 'admin:Awleonship!1' 'https://search-silkroad-test-cq3gzgphhaaiivvm7zua2fhaue.ca-central-1.es.amazonaws.com/_bulk' --data-binary @registration.json -H 'Content-Type: application/json'

"""
def csv_to_json(csv_file, output_file):
    id = 0
    with open(csv_file, 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        with open(output_file, 'w') as jsonfile:
            for row in reader:
                row['batteryVoltage'] = float(row['batteryVoltage'])

                # Construct the JSON document
                json_doc = {
                    "index": {
                        "_index": "batterypercent",
                        "_id": id  # Use timestamp as unique id
                    }
                }
                id = id + 1
                jsonfile.write(json.dumps(json_doc) + '\n')
                
                # Remove timestamp field before writing the actual data
                del row['timestamp']
                jsonfile.write(json.dumps(row) + '\n')

# Example usage
csv_to_json('battery_simulation.csv', 'output.json')