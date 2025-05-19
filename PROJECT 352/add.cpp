import socket
import threading
import requests
import json

# === Configuration ===
HOST = '127.0.0.1'
PORT = 5050
API_KEY = 'YOUR_API_KEY'  # Replace with your aviationstack.com API key
BASE_URL = 'http://api.aviationstack.com/v1/flights?access_key=' + API_KEY

# === Threaded Client Handler ===
def handle_client(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected.")

    try:
        conn.send("Enter ICAO airport code (e.g. EGLL for Heathrow): ".encode())
        airport_code = conn.recv(1024).decode().strip()
        print(f"[REQUEST] {addr} requested data for airport: {airport_code}")

        flights = get_flight_data(airport_code)

        if not flights:
            conn.send("No data found or API error.\n".encode())
            conn.close()
            return

        while True:
            menu = """
Choose an option:
1. View Arrived Flights
2. View Delayed Flights
3. Search by Flight IATA code
4. Exit
Your choice: 
"""
            conn.send(menu.encode())
            choice = conn.recv(1024).decode().strip()

            if choice == '1':
                arrived = [f for f in flights if f['arrival']['actual'] is not None]
                conn.send(format_flights(arrived).encode())
            elif choice == '2':
                delayed = [f for f in flights if f['departure']['delay']]
                conn.send(format_flights(delayed).encode())
            elif choice == '3':
                conn.send("Enter Flight IATA Code: ".encode())
                iata = conn.recv(1024).decode().strip()
                result = [f for f in flights if f['flight']['iata'] == iata]
                conn.send(format_flights(result).encode())
            elif choice == '4':
                conn.send("Goodbye!\n".encode())
                break
            else:
                conn.send("Invalid choice.\n".encode())

    except Exception as e:
        print(f"[ERROR] {e}")
    finally:
        conn.close()

# === Flight Data Fetcher ===
def get_flight_data(airport_code):
    try:
        response = requests.get(BASE_URL + f"&dep_icao={airport_code}&limit=20")
        data = response.json()
        return data.get('data', [])
    except Exception as e:
        print(f"[API ERROR] {e}")
        return []

# === Format Function ===
def format_flights(flights):
    if not flights:
        return "No matching flights found.\n"
    output = ""
    for f in flights:
        output += f"Flight: {f['flight']['iata']} | From: {f['departure']['airport']} | To: {f['arrival']['airport']} | Status: {f['flight_status']}\n"
    return output

# === Main Server Loop ===
def start():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen()
    print(f"[LISTENING] Server running on {HOST}:{PORT}")

    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 1}")

# === Run Server ===
if __name__ == "__main__":
    start()
