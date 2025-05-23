# ITNE352 Project: Multithreaded Flight Arrival Client/Server Information System

## 📘 Project Description
This project is a multithreaded client/server system built in Python for ITNE352: Network Programming. The system allows multiple clients to retrieve real-time flight information from a selected airport using the AviationStack API. The system demonstrates socket programming, multithreading, API integration, and client-server communication.

## 📅 Semester
S2 2024-2025

## 👥 Group
- **Course**: ITNE352 - Network Programming
- **Section**: 24252
- **Group Members:**
  - Abdullaziz Nasser Alshallal (202107658)
  - Ahmed Salman Ahmed (202104591)

---

## 📂 Table of Contents
- [Project Description](#project-description)
- [Requirements](#requirements)
- [How to Run](#how-to-run)
- [Scripts Overview](#scripts-overview)
- [Additional Concept](#additional-concept)
- [Acknowledgments](#acknowledgments)
- [Conclusion](#conclusion)
- [Resources](#resources)

---

## 🛠️ Requirements
To run this project locally:
- Python 3.9+
- `requests` library
- Access to [aviationstack.com](https://aviationstack.com) with an API key

Install required packages:
```bash
pip install requests
```

---

## ▶️ How to Run
1. Clone the repository:
```bash
git clone https://github.com/aziz202107658/ITNE352.git
```
2. Change directory:
```bash
cd ITNE352
```
3. Run the server:
```bash
python server.py
```
4. Open multiple terminals and run clients:
```bash
python client.py
```

When prompted, enter your username and choose one of the available options:
- View all arrived flights
- View all delayed flights
- Get details of a particular flight
- Quit

---

## 📄 Scripts Overview
### server.py
- Requests ICAO code from user
- Retrieves flight data from AviationStack API
- Stores results in `group_X.json`
- Accepts multiple clients using `threading`
- Responds to three types of requests:
  - All arrived flights
  - All delayed flights
  - Particular flight details

### client.py
- Connects to the server and identifies user
- Displays request options and handles user input
- Sends request to server and prints response
- Allows repeated queries until user quits

---

## 💡 Additional Concept: Multithreading
The server script uses Python’s `threading` module to allow multiple clients to connect and interact concurrently. Each client is handled in a separate thread, enabling real-time communication without blocking other clients.

---

## 🙏 Acknowledgments
Special thanks to Dr. Mohammed Almeer for guidance and detailed project requirements.

---

## 📌 Conclusion
This project demonstrates a real-world use case of socket programming and multithreading in Python. It shows how to integrate APIs into client/server systems and handle multiple connections efficiently.

---

## 📚 Resources
- [aviationstack API](https://aviationstack.com/)
- Python Official Documentation
- Stack Overflow and Real Python tutorials