# Library Book Data Log System

## Overview
This project implements a **client–server library management system** written in C.

- The **server** manages access to library book records and enforces all business logic.
- The **client** allows users to view available books, check out books, and check books back in.

The two processes communicate using **TCP/IP sockets**, making this project a practical demonstration of networking, backend state management, and modular system design in C.

---

## Features
- Client–server architecture with a dedicated server managing all library state
- TCP/IP socket–based request–response communication
- View available books stored on the server
- Check books in and out with validation and error handling
- Defensive handling of invalid, missing, or unavailable book requests

---

## Architecture Overview
This system follows a client–server architecture:

- The server maintains all library state and enforces business rules.
- The client acts as a lightweight interface that sends structured requests to the server.
- Communication occurs over TCP/IP sockets using a simple request–response protocol.
- Book records are initialized from a structured data file and managed in memory.

This design emphasizes **separation of concerns**, **clear state ownership**, and **defensive error handling**, mirroring patterns used in backend and web-based systems.

---


## Installation & Compilation
### Windows:
1. Open **Command Prompt** or **PowerShell**.
2. Compile the project:
   ```sh
   mingw32-make
   ```
   or 
   ```sh
   make
   ```
3. Run the server:
   ```sh
   ./server.exe
   ```
4. Run the client:
   ```sh
   ./client.exe
   ```

### Linux/macOS:
1. Open Terminal.
2. Compile the project:
   ```sh
   make
   ```
3. Run the server:
   ```sh
   ./server &
   ```
4. Run the client:
   ```sh
   ./client
   ```

---
 
## Troubleshooting

### Common Issues:

- **"Client cannot connect to server"**  
  - Solution: Ensure the server is running before starting the client.

- **"Port binding error"**  
  - Solution (Linux/macOS):  
    ```sh
    fuser -k 60002/tcp
    ```

---

## Source Files

- `books.c` - Handles book data creation, formatting, and list operations.
- `client.c` - Implements client-side interaction and user input handling.
- `connect.c` - Manages TCP socket setup and communication utilities.
- `defs.h` - Contains global definitions and cross-platform adjustments.
- `lib.c` - Implements library initialization and book state management logic.
- `server.c` - Implements server-side request handling and application control flow.

---

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
