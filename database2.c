#include "database_main.h"

void menu_get_book_details(void){	/* function prints the details of a book entered by the user from the database array */
	int i, found = 0;
	char Query[100000];
	fprintf(stderr,"\nChoice: Print details of book\n\n");

	fprintf(stderr,"Enter the title of the Book \n");
	fgets(Query,MAX_TITLE_LENGTH,stdin);
	sscanf(Query, "%100[^\n]", Query);	/* Asks the user to input the name of the book they want and stores it under Query */

	for (i = 0; i < MAX_BOOKS; i++){
		if (strcmp(book_array[i].title, Query) == 0 && book_array[i].year > 0){
			/* searches each title in the the array to find a match to the title input by the user,
			 if a match is found the details will be printed in the format below */
			printf("Title: %s\n", book_array[i].title);
			printf("Author: %s\n", book_array[i].author);
			printf("Year: %d\n\n", book_array[i].year);
			found = 1;
		}	
	}
	if (found == 0){
		/* if a match is not found the error will be given below */
		fprintf(stderr, "The book you entered was not found\n");
	}
}


void menu_delete_book(void){	/* function deletes the book entered by the user from the database */
	int i, found = 0;
	char del[100000];
	fprintf(stderr,"\nChoice: Delete book\n\n\n");

	fprintf(stderr,"Enter the title of the Book you want to delete \n");
	fgets(del,MAX_TITLE_LENGTH,stdin);
	sscanf(del, "%100[^\n]", del);	/* Asks the user to input the name of the book they want to delete and stores it under del */

	for (i = 0; i < MAX_BOOKS; i++){
		/* searches the array for the book entered and if a match is found sets its date to 0,
		this will emulate its deletion as the menu_print_database() function will only print books whose dates are greater than 0 */
		if (strcmp(book_array[i].title, del) == 0 && book_array[i].year > 0){
			book_array[i].year = 0;
			found = 1;
			fprintf(stderr, "%s has been deleted\n", del);
		}
	}
	if (found == 0){
		/* if a match is not found the error will be given below */
		fprintf(stderr, "The book you entered was not found\n");
	}
}

