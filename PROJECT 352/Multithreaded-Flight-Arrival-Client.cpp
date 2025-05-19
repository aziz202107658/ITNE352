import socket
import threading
import requests
import json
import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext

# API Settings
API_KEY = 'YOUR_API_KEY'  # Replace with your aviationstack API key
HOST = '127.0.0.1'
PORT = 12345

# Shared flight data
flight_data = []

# Server thread
class FlightServer:
    def __init__(self):
        self.clients = {}
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def fetch_data(self, icao):
        url = f"http://api.aviationstack.com/v1/flights?access_key={API_KEY}&arr_icao={icao}&limit=100"
        response = requests.get(url)
        data = response.json()
        with open("group_ID.json", "w") as file:
            json.dump(data, file, indent=4)
        global flight_data
        flight_data = data.get("data", [])

    def handle_client(self, client_socket, addr):
        client_name = client_socket.recv(1024).decode()
        print(f"[Connected] {client_name} from {addr}")
        self.clients[addr] = client_name

        while True:
            try:
                request = client_socket.recv(1024).decode()
                print(f"[Request] From {client_name}: {request}")
                if request == "1":
                    msg = ""
                    for f in flight_data:
                        if f["arrival"].get("actual"):
                            msg += f'{f["flight"]["iata"]} | {f["departure"]["airport"]} | {f["arrival"].get("actual", "N/A")} | Terminal: {f["arrival"].get("terminal", "N/A")} | Gate: {f["arrival"].get("gate", "N/A")}\n'
                    client_socket.send(msg.encode())
                elif request == "2":
                    msg = ""
                    for f in flight_data:
                        if f["arrival"].get("delay"):
                            msg += f'{f["flight"]["iata"]} | {f["departure"]["airport"]} | {f["departure"].get("scheduled", "N/A")} | ETA: {f["arrival"].get("estimated", "N/A")} | Delay: {f["arrival"].get("delay")} min | Terminal: {f["arrival"].get("terminal", "N/A")} | Gate: {f["arrival"].get("gate", "N/A")}\n'
                    client_socket.send(msg.encode())
                elif request.startswith("3"):
                    iata = request.split()[1].strip()
                    f = next((f for f in flight_data if f["flight"]["iata"] == iata), None)
                    if f:
                        msg = (
                            f'Flight {iata} | Status: {f["flight_status"]}\n'
                            f'Departure: {f["departure"]["airport"]}, Terminal {f["departure"].get("terminal", "N/A")}, Gate {f["departure"].get("gate", "N/A")}, Scheduled: {f["departure"].get("scheduled", "N/A")}\n'
                            f'Arrival: {f["arrival"]["airport"]}, Terminal {f["arrival"].get("terminal", "N/A")}, Gate {f["arrival"].get("gate", "N/A")}, Scheduled: {f["arrival"].get("scheduled", "N/A")}\n'
                        )
                    else:
                        msg = "Flight not found."
                    client_socket.send(msg.encode())
                elif request == "q":
                    print(f"[Disconnected] {client_name}")
                    client_socket.close()
                    break
            except Exception as e:
                print(f"Error with {client_name}: {e}")
                break

    def run(self):
        arr_icao = input("Enter the ICAO code: ").upper()
        self.fetch_data(arr_icao)
        self.server_socket.bind((HOST, PORT))
        self.server_socket.listen(5)
        print(f"[Server] Listening on {HOST}:{PORT}")
        while True:
            client, addr = self.server_socket.accept()
            thread = threading.Thread(target=self.handle_client, args=(client, addr))
            thread.start()

# GUI Client
class FlightClientApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Flight Info Client")

        ttk.Label(root, text="Your Name:").grid(row=0, column=0)
        self.name_entry = ttk.Entry(root)
        self.name_entry.grid(row=0, column=1)

        self.connect_button = ttk.Button(root, text="Connect", command=self.connect)
        self.connect_button.grid(row=0, column=2)

        self.options = ttk.Combobox(root, values=["Arrived Flights", "Delayed Flights", "Details (IATA)", "Quit"])
        self.options.grid(row=1, column=0, columnspan=2)
        self.send_button = ttk.Button(root, text="Send Request", command=self.send_request)
        self.send_button.grid(row=1, column=2)

        self.text_area = scrolledtext.ScrolledText(root, width=80, height=20)
        self.text_area.grid(row=2, column=0, columnspan=3, pady=10)

    def connect(self):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((HOST, PORT))
            self.sock.send(self.name_entry.get().encode())
            messagebox.showinfo("Connection", "Connected to server")
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def send_request(self):
        try:
            option = self.options.get()
            if option == "Quit":
                self.sock.send("q".encode())
                self.root.quit()
                return
            elif option == "Arrived Flights":
                self.sock.send("1".encode())
            elif option == "Delayed Flights":
                self.sock.send("2".encode())
            elif option == "Details (IATA)":
                iata = tk.simpledialog.askstring("Flight Code", "Enter IATA Code:")
                self.sock.send(f"3 {iata}".encode())
            result = self.sock.recv(4096).decode()
            self.text_area.delete('1.0', tk.END)
            self.text_area.insert(tk.END, result)
        except Exception as e:
            messagebox.showerror("Error", str(e))

if __name__ == '__main__':
    # Run server in background
    server_thread = threading.Thread(target=lambda: FlightServer().run())
    server_thread.daemon = True
    server_thread.start()

    # Start GUI client
    root = tk.Tk()
    app = FlightClientApp(root)
    root.mainloop()
