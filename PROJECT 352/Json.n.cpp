 # Example: Client connection and request sending
import socket
import json

with open("group_ID.json", "w") as json_file:
    json.dump(flight_data, json_file, indent=4)
Once the server fetches the flight data using the ICAO code, it must save the raw 100 records to a JSON file for testing and offline development.

# ... (rest of your client code)

def connect_to_server(username):
    # Client socket creation and connection
    pass

def send_request(client_socket, request_type, flight_code=None):
    # Logic to format and send requests
    pass

def display_response(response_data):
    # Logic to parse and display received data
    pass

# ... (rest of your client code)