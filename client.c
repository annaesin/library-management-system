#include "defs.h"

int main()
{
  int  choice = -1; 
  int clientSocket;
  setupClientSocket(&clientSocket);//creates scoket to connect to the server 

  int ID,action;
  char request[MAX_ARR];
  char string[MAX_BUFF];
  char str[MAX_STR];
  
  while (1) {
   clientMenu(&choice);
   switch(choice) {
      case 1: ;  // Print books
      	//Fomulates request string containing REQ_RET_BOOKS request type
		sprintf(request, "%d", 0);
		sendData(clientSocket, request);
		rcvData(clientSocket,string);
		printf("%s ", string);
        break;

      case 2:   // Check out a book
      	//Fomulates request string containing REQ_CHECK_OUT request type AND book ID
        printf("Please enter the book id: ");
      	fgets(str, sizeof(str), stdin);
      	sscanf(str, "%d", &ID);
      	sprintf(request, "%d %d", 1, ID);
		sendData(clientSocket, request);
		rcvData(clientSocket,string);
		sscanf(string,"%d", &action);
		//Prints confirmation messages on the success or failure of operation
		if(action == 0){
			printf(GREEN"\nSuccess! Book has been checked out.\n" RESET);
		}
		else if(action == -1){
			printf(RED"\nSorry, it seems like this book has already been checked out!\n" RESET);
		}
		else if(action == -2){
			printf(RED"\nSorry, this book doesnt exist!\n"RESET);
		}
		else if(action == -3){
			printf(RED"\nSorry, this book is either under repair or lost at the moment.\n" RESET);
		}
			break;

      case 3:   // Check in a book
      //Fomulates request string containing REQ_CHECK_IN request type AND book ID
		printf("Please enter the book id: ");
      	fgets(str, sizeof(str), stdin);
      	sscanf(str, "%d", &ID);
      	sprintf(request, "%d %d", 2, ID);
		sendData(clientSocket, request);
		rcvData(clientSocket,string);
		sscanf(string,"%d", &action);
		//Prints confirmation messages on the success or failure of operation
		if(action == 0){
			printf(GREEN"\nSuccess! Book has been checked in.\n"RESET);
		}
		else if(action == -1){
			printf(RED"\nSorry, it seems like this book has already been checked in!\n" RESET);
		}
		else if(action == -2){
			printf(RED"\nSorry, this book doesnt exist!\n" RESET);
		}
		else if(action == -3){
			printf(RED"\nSorry, this book is under repair and has not be checked out.\n" RESET);
		}
			break;

      case 0:   // Close everything
		printf(GREEN"\nThank you for using our Library System! Come again soon :)\n\n"RESET);
		sprintf(request, "%d", 3);
		sendData(clientSocket, request);
		CLOSESOCKET(clientSocket);
		exit(-1);
        break;

      default:
        printf(RED"ERROR:  invalid option\n"RESET);
    }
  }

  return 0;
}

void clientMenu(int* choice)
{
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  printf("\n\n===============================\n");
  printf("MAIN MENU\n");
  printf("===============================\n");
  printf("  (1) View available books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n");
  printf("===============================\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}

