import socket

HOST = '127.0.0.1'
PORT = 12345

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

name = input("Enter your name: ")
client_socket.send(name.encode())

def menu():
    print("\n--- Flight Info Client ---")
    print("1. Arrived Flights")
    print("2. Delayed Flights")
    print("3. Details of a Specific Flight")
    print("q. Quit")
    return input("Choose an option: ")

while True:
    opt = menu()
    if opt == "3":
        code = input("Enter flight IATA code: ")
        client_socket.send(f"3 {code}".encode())
    else:
        client_socket.send(opt.encode())
    if opt == "q":
        break
    data = client_socket.recv(4096).decode()
    print(f"\n[Response from Server]\n{data}")
