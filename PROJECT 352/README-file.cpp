# Multithreaded Flight Arrival Client/Server Information System

## Project Description
This project focuses on building a client-server system using Python to exchange flight information for a specified airport[cite: 3]. The system emphasizes client/server architecture, network communication, multithreading, API integration, and good coding practices[cite: 4]. It comprises two Python scripts: a server and a client[cite: 5].

The server is responsible for retrieving flight data from aviationstack.com via its API, extracting relevant information, managing connections with multiple simultaneous clients, and responding to their requests[cite: 6]. The client script connects to the server, offers various request types (e.g., arrived flights, delayed flights, specific flight details), displays the received responses, and remains active until the user chooses to disconnect[cite: 20, 21, 22, 24].

## Semester
S2 2024-2025 [cite: 1]

## Group
* **Course Code:** ITCE320 [cite: 1]
* **Section:** [Your Section Here]
* **Student Name:** [Student 1 Name], [Student 2 Name]
* **Student ID:** [Student 1 ID], [Student 2 ID]

## Table of Contents
1.  Requirements
    * Setting up the Environment
    * How to Run the System
2.  The Scripts
    * Server Script (`server.py`)
    * Client Script (`client.py`)
3.  Additional Concept
4.  Acknowledgments
5.  Conclusion
6.  Resources

## 1. Requirements

### Setting up the Environment
To set up and run this project in your local environment, follow these steps:

1.  **Python Installation:** Ensure you have Python 3 installed on your system.
2.  **Required Dependencies:** Install the `requests` library, which is used for making API calls.
    ```bash
    pip install requests
    ```
    Other necessary libraries like `socket`, `threading`, and `json` are built into Python.
3.  **API Key:** Obtain an API key from [aviationstack.com](https://aviationstack.com/). You will need this key for the server to retrieve flight data[cite: 6].
4.  **Development Environment Configuration (GitHub):**
    * Create a new GitHub repository called "ITNE352 Project - Group X" (replace `X` with your assigned group letter)[cite: 84].
    * Ensure both group members are in that repository[cite: 84].
    * Add `malmeer@uob.edu.bh` as a collaborator to the repository[cite: 84].
    * Collaborate and update the repository step-by-step using proper Git commands, ensuring participation from both members[cite: 84].

### How to Run the System
This section provides clear instructions on how to interact with the server and run the system[cite: 67].

#### Running the Server Script (`server.py`)
1.  **Open a terminal or command prompt.**
2.  **Navigate to the directory** where your `server.py` file is located.
3.  **Execute the server script:**
    ```bash
    python server.py
    ```
4.  **Enter Airport ICAO Code:** Upon startup, the server should ask the user to enter the airport code (arr\_icao)[cite: 7, 10].
5.  **Data Retrieval:** The server will use the proper API to retrieve 100 records of flights at the specified airport (using avaitionstack.com)[cite: 11]. It will then store the retrieved data in a JSON file called "group\_ID.json" (for testing and evaluation purposes)[cite: 12].
6.  **Server Output:** The server screen should clearly display:
    * The acceptance of a new connection with the client's name[cite: 18].
    * The requester name, type of request, and request parameters[cite: 19].
    * The disconnection of a client with its name[cite: 19].

#### Running the Client Script (`client.py`)
1.  **Open a separate terminal or command prompt.**
2.  **Navigate to the directory** where your `client.py` file is located.
3.  **Execute the client script:**
    ```bash
    python client.py
    ```
4.  **Connect and Identify:** The client script should connect to the server and send the client's username to identify itself[cite: 20, 25].
5.  **Interactive Menu:** The client should present multiple options for the user; different request types and a quit option[cite: 21]. The client should be user-friendly and display the options and results neatly[cite: 23].
6.  **Send Requests:** The client should send different types of requests[cite: 22].
    * **Arrived flights:** The client should display the flight code (IATA), departure airport, arrival time, arrival terminal, and arrival gate[cite: 27].
    * **Delayed flights:** The client should display the flight code (IATA), departure airport, departure time, estimated arrival time, delay, terminal, and gate[cite: 28].
    * **Details of a particular flight:** The client should display flight code (IATA), departure (airport, gate, and terminal), arrival (airport, gate, and terminal), status, scheduled departure time, and scheduled arrival time[cite: 29].
7.  **Display Results:** The client should receive and display the responses[cite: 22]. The retrieved information should be displayed clearly and neatly[cite: 31].
8.  **Stay Connected:** The client should stay connected and ready to send new requests until the user chooses to quit[cite: 24].
9.  **Quit Option:** When the user selects the Quit option, the connection should be closed, and the client should leave[cite: 30].

## 2. The Scripts

### Server Script (`server.py`)
This script acts as the central hub for flight information[cite: 6].
* **Main Functionalities:**
    * Starts by asking about the target airport (ICAO code) and retrieves the information about flights at the specified airport over an API[cite: 7].
    * Uses the proper API to retrieve 100 records of flights at the specified airport (using avaitionstack.com)[cite: 11].
    * Stores the retrieved data in a JSON file called "group\_ID.json" (for testing and evaluation purposes)[cite: 12].
    * Waits for clients' requests to connect (should accept at least three connections simultaneously)[cite: 12].
    * Accepts the connection and stores the client's name, displaying it on the terminal[cite: 13].
    * Waits for clients' requests, searches the retrieved data for matching, and sends a reply with the matching information[cite: 14]. This includes:
        * All arrived flights (return flight IATA code, departure airport name, arrival time, arrival terminal number, and arrival gate)[cite: 15].
        * All delayed flights (return flight IATA code, departure airport, original departure time, the estimated time of arrival), arrival terminal, delay, and arrival gate[cite: 16].
        * Details of a particular flight (return flight IATA code; departure airport, gate, and terminal; arrival airport, gate, and terminal; status; scheduled departure time; and scheduled arrival time)[cite: 17].
    * Displays the acceptance of a new connection with the client's name, the requester name, type of request, request parameters, and the disconnection of a client with its name[cite: 18, 19].
* **Utilized Packages:** `socket`, `threading`, `json`, `requests`.
* **Key Functions/Classes (Example Structure):**
    ```python
    import socket
    import threading
    import json
    import requests

    # Function to fetch flight data from aviationstack API
    def fetch_flight_data(icao_code, api_key):
        # API request logic, data parsing, and saving to group_ID.json
        pass

    # Function to handle individual client connections
    def handle_client(client_socket, client_address, client_name, flight_data):
        # Logic to receive client requests, process them, and send responses
        pass

    # Main server function
    def main():
        # Server setup: socket creation, bind, listen
        # Loop to accept incoming connections and create a new thread for each
        pass

    if __name__ == "__main__":
        main()
    ```

### Client Script (`client.py`)
This script enables users to connect to the server and query flight information[cite: 20].
* **Main Functionalities:**
    * Establishes a connection with the server and sends the client's username to identify itself[cite: 25].
    * Sends one of the following three request types[cite: 27]:
        * Arrived flights: displays the flight code (IATA), departure airport, arrival time, arrival terminal, and arrival gate[cite: 27].
        * Delayed flights: displays the flight code (IATA), departure airport, departure time, estimated arrival time, delay, terminal, and gate[cite: 28].
        * Details of a particular flight: displays flight code (IATA), departure (airport, gate, and terminal), arrival (airport, gate, and terminal), status, scheduled departure time, and scheduled arrival time[cite: 29].
    * Closes the connection and leaves when the user selects the Quit option[cite: 30].
    * Displays the retrieved information clearly and neatly[cite: 31].
* **Utilized Packages:** `socket`, `json`.
* **Key Functions/Classes (Example Structure):**
    ```python
    import socket
    import json

    # Function to connect to the server
    def connect_to_server(server_ip, server_port, username):
        # Socket creation and connection logic
        pass

    # Function to display options and get user input
    def display_menu():
        # Present interactive menu
        pass

    # Function to send requests to the server
    def send_request(client_socket, request_type, flight_code=None):
        # Format request and send
        pass

    # Function to receive and display server responses
    def receive_response(client_socket):
        # Receive and parse data, then display
        pass

    # Main client function
    def main():
        # Connection establishment, then loop for user interaction
        pass

    if __name__ == "__main__":
        main()
    ```

## 3. Additional Concept
(Choose ONE of the following and describe your implementation and findings in detail. Include relevant code snippets and screenshots where applicable.) [cite: 76]

1.  **TLS/SSL (Security):**
    * **Description:** Should secure all your packet transactions[cite: 77]. This ensures data confidentiality and integrity.
    * **Implementation:** Detail how `ssl` module (or equivalent) was integrated into both server and client scripts.
    * **Verification:** Use Wireshark to examine the exchanged packets. You must show that it is working during the demonstration and include pieces of evidence in your report (screenshots of the packet data)[cite: 78].
    * **Code Snippets:** Include relevant code portions showcasing SSL context creation and socket wrapping.

2.  **Object-Oriented Programming (OOP):**
    * **Description:** Use object-oriented programming in your coding[cite: 79].
    * **Python OOP Basics:** Describe, in your report, the basics of OO in Python, and your classes[cite: 79].
    * **Implemented Classes:** Describe the classes designed for this project (e.g., `Flight`, `ClientHandler`, `Server`) and their attributes and methods.
    * **Code Snippets:** Provide excerpts demonstrating class definitions and their usage.

3.  **GUI (Graphical User Interface):**
    * **Description:** Use a graphical user interface for the client[cite: 80]. It should be easy to use and clear to read[cite: 80].
    * **Framework Used:** Specify the GUI library used (e.g., Tkinter, PyQt, Kivy).
    * **Design and Functionality:** The user should send all requests using the GUI[cite: 81]. Describe the layout of the GUI, how users select request types, input flight codes, and how results are displayed.
    * **Screenshots:** Include screenshots of the client GUI in action.
    * **Code Snippets:** Showcase key parts of the GUI implementation, such as window creation, widget placement, and event handling.

## 4. Acknowledgments
We would like to express our sincere gratitude to Dr. Mohammed Almeer for his guidance and support throughout this project. His expertise and insights were invaluable in the development of this client-server system.

## 5. Conclusion
This project provided a comprehensive learning experience in building a multithreaded, connection-oriented client/server application using Python and an external API[cite: 32]. We successfully implemented core networking concepts, data retrieval, and multithreading to handle simultaneous client requests. While the system provides a functional framework, we also gained insights into the limitations of such basic frameworks and potential areas for future enhancement, such as advanced error handling and scalability[cite: 34]. The project reinforced the importance of good design, code quality, and collaborative development using Git[cite: 52, 53].

## 6. Resources
* IEEE Explore: http://ieeexplore.ieee.org/Xplore/dynhome.jsp
* ACM Digital Library: http://portal.acm.org/dl.cfm
* Elsevier Science Direct: http://www.sciencedirect.com/
* Google Scholar: http://scholar.google.com/
* aviationstack.com (for flight data API)