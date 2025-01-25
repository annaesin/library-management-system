# Library Book Data Log System

## Author
**Annabel Esin**

## Overview
This project consists of:
- **Server:** Manages access to the library book data and processes client requests.
- **Client:** Allows users to interact with the library system to view, check-in, and check-out books.
  
The two processes communicate using **TCP/IP sockets**, making it an excellent demonstration of network programming in C.

---

## Features
- View available books
- Check out and check in books
- Server-client communication via TCP sockets

---

## Installation & Compilation
### Windows:
1. Open **Command Prompt/PowerShell**.
2. Compile the project:
   ```sh
   mingw32-make or make
   ```
3. Run the server:
   ```sh
   server.exe
   ```
4. Run the client:
   ```sh
   client.exe
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

- **"CLIENT COULDN'T CONNECT"**  
  - Solution: Restart the server process.

- **"COULD NOT BIND"**  
  - Solution (Linux/macOS):  
    ```sh
    fuser -k 60002/tcp
    ```

---

## Source Files

- `books.c` – Handles book data operations.
- `client.c` – Handles client-side interaction with the server.
- `connect.c` – Manages TCP socket communication.
- `defs.h` – Contains global definitions and cross-platform adjustments.
- `lib.c` – Handles book list operations.
- `server.c` – Implements the server logic.

---

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
