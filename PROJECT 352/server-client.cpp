# flight_server.py
import socket
import threading
import requests
import json

# Replace with your aviationstack API key
API_KEY = 'YOUR_API_KEY_HERE'

# Prompt for airport code
arr_icao = input("Enter ICAO code for airport (e.g., EGLL): ")

# Retrieve data from API
url = f"http://api.aviationstack.com/v1/flights?access_key={API_KEY}&arr_icao={arr_icao}&limit=100"
response = requests.get(url)
data = response.json()

# Save data to JSON file
with open("group_ID.json", "w") as f:
    json.dump(data, f, indent=4)

print("Flight data retrieved and stored in 'group_ID.json'. Server is now running...")

# Load data for searching
flights = data.get("data", [])

# Server setup
HOST = '0.0.0.0'
PORT = 5000
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(5)
clients = {}

# Request handlers
def handle_client(client_socket, client_address):
    try:
        client_socket.send(b"Enter your name: ")
        name = client_socket.recv(1024).decode().strip()
        clients[client_socket] = name
        print(f"[+] New connection from {name} at {client_address}")

        while True:
            client_socket.send(b"\nOptions:\n1. Arrived Flights\n2. Delayed Flights\n3. Flight Details\n4. Quit\nChoose an option: ")
            choice = client_socket.recv(1024).decode().strip()

            if choice == '1':
                arrived = [f for f in flights if f['arrival']['actual'] is not None and f['flight']['iata']]
                result = "\n".join([
                    f"Flight: {f['flight']['iata']}, From: {f['departure']['airport']}, Arrival Time: {f['arrival']['actual']}, Terminal: {f['arrival'].get('terminal', '-')}, Gate: {f['arrival'].get('gate', '-')}"
                    for f in arrived]) or "No arrived flights found."

            elif choice == '2':
                delayed = [f for f in flights if f['arrival']['delay']]
                result = "\n".join([
                    f"Flight: {f['flight']['iata']}, From: {f['departure']['airport']}, Original Time: {f['departure']['scheduled']}, ETA: {f['arrival']['estimated']}, Delay: {f['arrival']['delay']} min, Terminal: {f['arrival'].get('terminal', '-')}, Gate: {f['arrival'].get('gate', '-')}"
                    for f in delayed]) or "No delayed flights found."

            elif choice == '3':
                client_socket.send(b"Enter flight IATA code: ")
                flight_code = client_socket.recv(1024).decode().strip()
                f = next((f for f in flights if f['flight']['iata'] == flight_code), None)
                if f:
                    result = (
                        f"Flight: {f['flight']['iata']}\n"
                        f"From: {f['departure']['airport']} Terminal: {f['departure'].get('terminal', '-')} Gate: {f['departure'].get('gate', '-')}\n"
                        f"To: {f['arrival']['airport']} Terminal: {f['arrival'].get('terminal', '-')} Gate: {f['arrival'].get('gate', '-')}\n"
                        f"Status: {f['flight_status']}\n"
                        f"Scheduled Departure: {f['departure']['scheduled']}\n"
                        f"Scheduled Arrival: {f['arrival']['scheduled']}\n"
                    )
                else:
                    result = "Flight not found."

            elif choice == '4':
                client_socket.send(b"Goodbye!\n")
                break
            else:
                result = "Invalid choice."

            print(f"[*] Request from {name}: {choice}")
            client_socket.send(result.encode() + b"\n")

    except Exception as e:
        print(f"[!] Error with client {client_address}: {e}")
    finally:
        print(f"[-] Disconnected: {clients.get(client_socket, client_address)}")
        clients.pop(client_socket, None)
        client_socket.close()

# Accept incoming connections
print(f"[*] Listening on port {PORT}...")
while True:
    client_socket, addr = server.accept()
    client_thread = threading.Thread(target=handle_client, args=(client_socket, addr))
    client_thread.start()
