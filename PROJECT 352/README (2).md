# ITNE352 Project - Flight Information System (Client/Server)

## Project Description
This project is part of the ITNE352 Network Programming course. It involves building a client/server application using Python. The system uses the AviationStack API to retrieve live flight data for a specific airport, which is then processed and made available to multiple clients simultaneously through a socket-based server.

## Semester
Second Semester 2024-2025

## Group Information
- **Course**: ITNE352 - Network Programming
- **Section**: 24252
- **Students:**
  - Abdullaziz Nasser Alshallal - 202107658
  - Ahmed Salman Ahmed - 202104591

---

## Table of Contents
- Project Description
- Requirements
- Setup Instructions
- How to Use
- Code Explanation
- Extra Feature
- Credits
- Conclusion
- References

---

## Requirements
- Python 3.9 or higher
- `requests` library
- AviationStack API key

Install dependencies:
```bash
pip install requests
```

---

## Setup Instructions
1. Clone this repository:
```bash
git clone https://github.com/aziz202107658/ITNE352.git
```
2. Go to the project folder:
```bash
cd ITNE352
```
3. Run the server:
```bash
python server.py
```
4. Open new terminal windows for clients:
```bash
python client.py
```

---

## How to Use
- After launching the server, it will ask for an airport ICAO code (e.g., EGLL).
- The server fetches 100 flight records using the API and saves them to a JSON file.
- Clients connect to the server and send one of the following requests:
  - View all arrived flights
  - View all delayed flights
  - Get details of a specific flight
  - Quit

---

## Code Explanation

### server.py
- Prompts for airport ICAO code
- Fetches data from AviationStack
- Saves response as `group_X.json`
- Uses multithreading to manage multiple client connections
- Responds to client requests with filtered data

### client.py
- Connects to the server and sends the client’s name
- Offers a simple menu of options
- Sends a request based on user choice and displays the result

---

## Extra Feature
Multithreading is used on the server side. Each client connection is handled in a separate thread to support real-time interactions with multiple users.

---

## Credits
We thank Dr. Mohammed Almeer for providing us with clear instructions and support throughout the project.

---

## Conclusion
This project allowed us to practice key network programming concepts like sockets, threading, and API integration. It helped us understand how to manage concurrent client requests and display results in a user-friendly way.

---

## References
- AviationStack API: https://aviationstack.com/
- Python Docs: https://docs.python.org/
- Stack Overflow (for error troubleshooting)