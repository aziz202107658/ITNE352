import socket
import json

# Server configuration
HOST = '127.0.0.1'  # Server IP
PORT = 65432        # Port to connect to

def display_menu():
    print("\nAvailable Options:")
    print("1. View Arrived Flights")
    print("2. View Delayed Flights")
    print("3. Get Flight Details")
    print("4. Quit")


def main():
    client_name = input("Enter your name: ")
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(client_name.encode())

        while True:
            display_menu()
            option = input("Choose an option (1-4): ")

            if option == '1':
                s.sendall(json.dumps({"type": "arrived"}).encode())
                data = s.recv(8192).decode()
                print("\n--- Arrived Flights ---")
                flights = json.loads(data)
                for f in flights:
                    print(f"Flight: {f['flight_iata']} | From: {f['departure_airport']} | Arrival Time: {f['arrival_time']} | Terminal: {f['arrival_terminal']} | Gate: {f['arrival_gate']}")

            elif option == '2':
                s.sendall(json.dumps({"type": "delayed"}).encode())
                data = s.recv(8192).decode()
                print("\n--- Delayed Flights ---")
                flights = json.loads(data)
                for f in flights:
                    print(f"Flight: {f['flight_iata']} | From: {f['departure_airport']} | Departed At: {f['departure_time']} | ETA: {f['arrival_time']} | Delay: {f['delay']} | Terminal: {f['arrival_terminal']} | Gate: {f['arrival_gate']}")

            elif option == '3':
                flight_code = input("Enter Flight IATA Code: ")
                s.sendall(json.dumps({"type": "details", "flight_code": flight_code}).encode())
                data = s.recv(8192).decode()
                flight = json.loads(data)
                print("\n--- Flight Details ---")
                if flight:
                    print(f"Flight: {flight['flight_iata']}")
                    print(f"Departure: {flight['departure_airport']} | Terminal: {flight['departure_terminal']} | Gate: {flight['departure_gate']}")
                    print(f"Arrival: {flight['arrival_airport']} | Terminal: {flight['arrival_terminal']} | Gate: {flight['arrival_gate']}")
                    print(f"Status: {flight['status']}")
                    print(f"Scheduled Departure: {flight['departure_time']}")
                    print(f"Scheduled Arrival: {flight['arrival_time']}")
                else:
                    print("No details found for the specified flight.")

            elif option == '4':
                s.sendall(json.dumps({"type": "quit"}).encode())
                print("Exiting client.")
                break

            else:
                print("Invalid option. Please choose 1-4.")

if __name__ == '__main__':
    main()

