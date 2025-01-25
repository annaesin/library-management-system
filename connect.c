#include "defs.h"

void setupServerSocket(int *s)
{
  struct sockaddr_in serverAddr;
  int i;

#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

  // Creates the listening server socket
  *s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (*s < 0) {
    printf("Could not open socket\n");
    exit(-1);
  }

  // Setup server address
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons((unsigned short) SERVER_PORT);

  // Bind listen socket 
  i = bind(*s, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if (i < 0) {
    printf("Could not bind socket\n");
    exit(-1);
  }

  // Listen on socket 
  i = listen(*s, 5);
  if (i < 0) {
    printf("Could not setup listening on socket\n");
    exit(-1);
  }
}

void acceptConnection(int lSock, int *cSock)
{
  struct sockaddr_in clientAddr;
  socklen_t addrSize;

  // Wait for connection request 
  addrSize = sizeof(clientAddr);

  *cSock = accept(lSock, (struct sockaddr *) &clientAddr, &addrSize);
  if (*cSock < 0) {
    printf("Could not accept the connection\n");
    exit(-1);
  }
}

void setupClientSocket(int* clientSocket)
{
    struct sockaddr_in serverAddr;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed: %d\n", WSAGetLastError());
        exit(1);
    }
#endif

    * clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (*clientSocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(*clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection to server failed");
#ifdef _WIN32
        printf("Error code: %d\n", WSAGetLastError());
#endif
        CLOSESOCKET(*clientSocket);
        exit(1);
    }

    printf(GREEN "\n\nConnected to the server successfully.\n"RESET);
}


void sendData(int s, char *buffer)
{
  send(s, buffer, strlen(buffer), 0);
}

void rcvData(int s, char *buffer)
{
  char tmpBuff[MAX_BUFF];
  int bytesRcv;

  // Read message from client
  bytesRcv = recv(s, tmpBuff, sizeof(tmpBuff)-1, 0);
  tmpBuff[bytesRcv] = 0;
  strcpy(buffer, tmpBuff);
}


