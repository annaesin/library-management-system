#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  loadBooks
  Purpose:   reads in all data from file and add each book info to book list
   in-out:   book file, book elements
*/
void loadBooks(BookListType*books){
	FILE *infile;
	BookType *b;
	char str[MAX_ARR];
  	int ID=1001; 
  	char title[MAX_STR];
  	char author[MAX_STR];
  	int year;
  	int status;
	 
  	infile = fopen("booksData.txt", "r");
  	if (!infile) {
    		printf("Error: could not open file\n");
    		exit(1);
  	}
  	while (1){
  	  fgets(title,sizeof(title), infile);
  	  title[strlen(title)-1] = '\0';
  	  fgets(author,sizeof(author), infile);
  	  author[strlen(author)-1] = '\0';
  	  fgets(str,MAX_ARR, infile);
  	  sscanf(str,"%d", &year);
  	  fgets(str, MAX_ARR, infile);
  	  sscanf(str,"%d", &status);
  	  initBook(ID,title,author,year,status, &b);
  	  ID+=1;
 
    	  if (feof(infile))
      	    break;
      	  addBook(books, b);
     	}
  	fclose(infile);
}

/*
  Function:  initLibrary
  Purpose:   dynamically alloactes the memory for a new library, intitialises parameters, loads book data from file, them prints it 
   in-out:  library collection
*/
void initLibrary(LibraryType **library, char *n){
	char lstring[MAX_BUFF];
	LibraryType *newLib= malloc(sizeof(LibraryType));
	strcpy(newLib->name,n);
	initList(&newLib->books);
	loadBooks(&newLib->books);
	formatBooks(&newLib->books, lstring);
	
	printf("\nBOOKS:\n");
  printf("------------------------------------------------------------------------------------------------\n");
	printf("%s", n);
	printf("%s", lstring);
	printf("\n");
	printf("------------------------------------------------------------------------------------------------\n");
	*library= newLib;
}

/*
  Function:  checkoutBook
  Purpose:   finds book id, checks status and updates it by checking it out
   in-out:  library collection, book ID, status
    return:   C_OK for success, C_BAD_STATUS for failure with status, C_BOOK_NOT_FOUND for missing book
*/
int checkOutBook(LibraryType *lib, int bookId){
	BookType *b;
	if(findBook(&lib->books,bookId,&b)==0){
		if(b->status == CHECKED_IN){
			b->status = 1;
			return C_OK;
		}
		else if((b->status == UNDER_REPAIR) || (b->status== LOST)){
			return C_BAD_STATUS;
		}
		else if(b->status == CHECKED_OUT){
			return C_NOK;
		}
	}
	return C_BOOK_NOT_FOUND;
	
}

/*
  Function:  checkInBook
  Purpose:   finds book id, checks status and updates it by checking it in
   in-out:  library collection, book ID, status
    return:   C_OK for success, C_BAD_STATUS for failure with status, C_BOOK_NOT_FOUND for missing book
*/
int checkInBook(LibraryType *lib, int bookId){
	BookType *b;
	if(findBook(&lib->books,bookId,&b)==0){
		if(b->status == CHECKED_OUT){
			b->status = 0;
			return C_OK;
		}
		else if(b->status == UNDER_REPAIR){ 
			return C_BAD_STATUS;
		}
		else if (b->status == LOST){ 
			b->status = 0;
			return C_OK;
		}
		else if(b->status == CHECKED_IN){
			return C_NOK;
		}
	}
	return C_BOOK_NOT_FOUND;
}

/*
  Function:  cleanupLibrary
  Purpose:   deallocates the memory for library
   in-out:   Library collection
*/
void cleanupLibrary(LibraryType *lib){
	cleanupList(&lib->books);
	free(lib);
}
