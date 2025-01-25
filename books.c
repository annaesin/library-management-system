#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

//initializes the required fields of the given book list
void initList(BookListType *list){
	list->head= NULL;
	list->tail=NULL;
}

//dynamically alloactes the memory for a new book and its elements
void initBook(int i, char*t, char*a, int y, BookStatusType st,BookType**book){
	BookType *newBook= malloc(sizeof(BookType));
	newBook->id= i;
	strcpy(newBook->title, t);
	strcpy(newBook->author, a);
	newBook->year=y;
	newBook->status= st;
	*book= newBook;
}

//adds new book to the list in alphabetical order by title
void addBook(BookListType*list, BookType*b){
	NodeType *currNode;
  	NodeType *prevNode;
  	NodeType *newNode;
  	
  	currNode = list->head;
  	prevNode = NULL;
  	
  	newNode = malloc(sizeof(NodeType));
  	newNode->data = b;
  	newNode->next = NULL;
  
  	while(currNode !=NULL){
  		if(strcmp(b->title,currNode->data->title)<0){
  			break;
  		}
  		prevNode= currNode;
  		currNode= currNode->next;	
  	}
  	
  	if(prevNode == NULL){
  		list->head= newNode;
    	}
  	else{
    		prevNode->next = newNode;
    	}
  	newNode->next = currNode;
  	
  	if(currNode == NULL){
  		list->tail=newNode;
  	}		
}
//finds the book with the given course id within the book list
int findBook(BookListType *list, int id, BookType **b){
	NodeType *current= list->head;
	
	if(current==NULL){
		return C_NOK;
	}
	
	while(current !=NULL){
		if(current->data->id == id){
			*b= current->data;
			return C_OK;
		}
		current = current->next;	
	}
	return C_NOK;	
}

//formats all info for a single book
void formatBook(BookType *b, char *outStr){
	char string[MAX_ARR];
	char status[MAX_STR];
	convertStatus(b->status, status);
	//sprintf(string,"\n%-5d|%-38s|%-20s|%-10d|%-5s", b->id, b->title, b->author, b->year,status);
	snprintf(string, sizeof(string), "\n%-5d|%-38s|%-20s|%-10d|%-5s", b->id, b->title, b->author, b->year, status);
	strcpy(outStr,string);	
}

//loops book list and formats books 
void formatBooks(BookListType *list, char *outStr){
	NodeType *current;
	current= list->head;
	
	char temp[MAX_ARR];
	char books[MAX_BUFF]={0};
	while(current != NULL){
		formatBook(current->data,temp);
		strcat(books,temp);
		current= current->next;
	} 
	strcpy(outStr,books);
	
	//Formats tail and head data and adds to booklist
	strcat(books, "\n-----HEAD");
	formatBook(list->head->data,temp);
	strcat(books,temp);
	strcpy(outStr,books);
	strcat(books, "\n-----TAIL");
	formatBook(list->tail->data,temp);
	strcat(books,temp);
	strcpy(outStr,books);
}	

//deallocates the dynamically allocated memory for the book collection
void cleanupList(BookListType *list){
	NodeType *currNode;
  	NodeType *nextNode=NULL;

  	currNode = list->head;
  	
  	while (currNode != NULL) {
    		nextNode = currNode->next;
    		free(currNode->data);
    		free(currNode);
    		currNode = nextNode;
  	}
}

//indicates the book status 
void convertStatus(BookStatusType st, char *s){
	if(st== CHECKED_IN){
		strcpy(s,"Checked In");
	}
	if(st== CHECKED_OUT){
		strcpy(s,"Checked Out");
	}
	if(st== UNDER_REPAIR){
		strcpy(s,"Under Repair");
	}
	if(st== LOST){
		strcpy(s,"Lost");
	}
}
