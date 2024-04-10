import csv
import json

def csv_to_json(csv_file, output_file):
    id = 0
    with open(csv_file, 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        with open(output_file, 'w') as jsonfile:
            for row in reader:
                row['lon'] = float(row['lon'])
                row['lat'] = float(row['lat'])
                
                # Construct the JSON document
                json_doc = {
                    "index": {
                        "_index": "location_20240317",
                        "_id": id  # Use timestamp as unique id
                    }
                }
                id = id + 1
                jsonfile.write(json.dumps(json_doc) + '\n')

                # Construct the point object
                point = {"lat": row['lat'], "lon": row['lon']}
                json_doc = {"point": point}

                # Write the actual data
                jsonfile.write(json.dumps(json_doc) + '\n')

# Example usage
csv_to_json('coordinates.csv', 'output.json')