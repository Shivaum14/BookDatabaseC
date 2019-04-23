#include "database_main.h"
#include <ctype.h>

struct Book book_form(void){		/* function to effectively gather valid user inputs for a new book entry */
	struct Book sample;	/* creates a variable of book structure that is used to store correctly entered books within the function */
	char trial_year[64], input_string[100000];
	int temp_year, valid_year = 0, valid_title = 0, valid_author = 0;

	do{		/* takes the user input for the title of the book and checks its not empty as well as under 100 charectes and stores it */
		fprintf(stderr,"\nEnter the title of the Book \n");
		fgets(input_string,100000,stdin);
		if (strcmp(input_string,"\n") != 0){
			valid_title = 1;
			sscanf(input_string, "%100[^\n]", sample.title);
		} else {
			fprintf(stderr, "Nothing was input, try again \n");
		}
	} while (valid_title == 0);
	do{		/* takes the user input for the author of the book and checks its not empty as well as under 100 charectes and stores it under sample.author */
		fprintf(stderr,"\nEnter the name of the Author \n");
		fgets(input_string,100000,stdin);
		if (strcmp(input_string,"\n") != 0){
			valid_author = 1;
			sscanf(input_string, "%100[^\n]", sample.author);
		} else {
			fprintf(stderr, "Nothing was input, try again \n");
		}
	} while (valid_author == 0);
	do{		/* takes the user input for the publishing year of the book and checks if it is a valid year and if so stores it under sample.year*/
		fprintf(stderr,"\nEnter the year it was published \n");
		fgets(trial_year,6,stdin);
		if (sscanf(trial_year, "%d", &temp_year) == 1 && temp_year > 0 && temp_year < 10000){
			valid_year = 1;
			sample.year = temp_year;
		} else {
			fprintf(stderr, "The input was incorrect \n");
		}
	} while (valid_year == 0);
	

	return sample;		/* will return the valid entries in the book structure so they can be easily added by menu_add_book in one go */
}

void menu_add_book(void){
	static int position = 0;
	fprintf(stderr,"\nChoice: Add new book\n\n");
	book_array[position++] = book_form();		/* adds new book to global array (book_array) through book_form() which collects and validates user input */
}


char *lwr(char *str)	/* lwr() function takes a string and converts it fully to lower case */
{
  unsigned char *title = (unsigned char *)str;

  while (*title) {
     *title = tolower((unsigned char)*title);
      title++;
  }

  return str;
}

int title_cmp(char* first, char* second){		/* function fairly compares the two titles passed to it so they may be sorted alphabeticaly */
	lwr(first);
	lwr(second);
	/* because strcmp() compares ascii values both titles must be temporarily converted to lowercase so they can be ordered fairly */
	return (strcmp(first, second));	/* returns the comparison between the two strings */
}

void menu_print_database(void)
{
	int i, j, k, l;
	struct Book temp;
	fprintf(stderr,"\nChoice: Print database to screen\n\n");
	char first[MAX_TITLE_LENGTH],second[MAX_TITLE_LENGTH];

	for (j = 0; j < MAX_BOOKS; j++){
		for (i = 0; i < MAX_BOOKS; i++){	/* for loops itterate through each book in book_array */
			for (k = 0; k < MAX_BOOKS; k++){
				if (book_array[k].year > 0 && book_array[i].year > 0){	/* makes sure not to include deleted books */
					for (l = 0; l < MAX_TITLE_LENGTH; l++){
						first[l] = book_array[i].title[l];
						second[l] = book_array[k].title[l];
					}
					if (title_cmp((char*)first,(char*)second) < 0){		/* compares the titles of the adjacent book to check if they are in alphbetical order */
						/* if the books are not in the right order ther will be sorted using bubble sort */
						temp = book_array[k];
						book_array[k] = book_array[i];
						book_array[i] = temp;
					}

				}
			}
		}

	}

	for (i = 0; i < MAX_BOOKS; i++){
		if (book_array[i].year > 0){
			/* once they have been sorted they are printed in the following format */
			printf("Title: %s\n", book_array[i].title);
			printf("Author: %s\n", book_array[i].author);
			printf("Year: %d\n\n", book_array[i].year);
		}

	}
}	    

