
# HTTP Client in C for Communicating with Existing Servers

This project implements a simple yet functional **HTTP client in C** that connects to existing web servers, sends HTTP requests, and receives their responses. It demonstrates how HTTP communication works at a low level by using raw TCP sockets, without relying on any external libraries.

The project provides hands-on experience with **network programming**, **socket APIs**, and **application-layer protocols**, allowing a deeper understanding of how browsers and network clients interact with servers.

---

## 🔧 Features

- Establishes a **TCP connection** with a remote server.
- Performs **DNS lookup** to resolve hostname to IP address.
- Constructs and sends **HTTP GET requests** manually.
- Receives complete HTTP responses including:
  - Status line  
  - Headers  
  - Body (HTML, JSON, etc.)
- Handles partial reads using loops with `recv()`.
- Prints the server's response to the terminal.

---

## 🧠 What This Project Demonstrates

- How HTTP/1.0 and HTTP/1.1 requests are structured.
- How to open and manage sockets using:
  - `socket()`
  - `connect()`
  - `send()`
  - `recv()`
  - `close()`
- Understanding of IP networking and TCP communication.
- The foundation of how modern web clients (browsers, cURL, Postman) work internally.

---

## 📂 Technologies Used

- **C Programming Language**
- **POSIX Sockets**
- **TCP/IP Networking**
- **DNS Resolution (`gethostbyname` or `getaddrinfo`)**

---

## ▶️ How to Run

1. **Compile the client:**
   ```bash
   gcc assign.c -o http_client

	2.	Run the client with server details:

./http_client <hostname> <path>

Example:

./http_client www.example.com /


	3.	The entire HTTP response will be printed to your terminal.

⸻

📁 Example Request Sent

GET / HTTP/1.0
Host: www.example.com


⸻

📘 Learning Outcomes

By completing this project, you will understand:
	•	How HTTP requests travel from client to server.
	•	How responses are structured (status, headers, body).
	•	How to manually work with network buffers.
	•	The basics of building your own custom network clients.

⸻

👤 Author
Ashfaaq Feroz Muhammad
