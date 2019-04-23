#include "database_main.h"

void read_book_database ( char *file_name ){	/* Function reads file containing database of books and adds them all to Book_array */
	fprintf(stderr, "Reading file provided\n");
	struct Book local_book_array[MAX_BOOKS];
	FILE *file = fopen( file_name , "r");	/* opens file to read */

	char title[100000], author[100000], year_str[100000], singleline[150];
	char *ptr;
	static int count = 0;
	struct Book sample;		/* creates variable of book structure to store books before entry into array */
	int i, total_added = 0, year_int, corrupt = 0, title_form, author_form;

	while(!feof(file) && corrupt == 0){		/* loops through the file until the end or a invalid input */
		fgets(title, 100000, file);		/* reads the title line of the file and stores it under title */
		title_form = sscanf(title, "Title: %2000[^\n] ", title);		/* strips the read line of "Title: " */
		if (title_form != 0){		/* tests the file layout */
			sscanf(title, "%100[^\n]",sample.title);		/* saves the remains under sample.title */
		} else {		/* if the layout of the file does not match, it is marked corrupted */
			corrupt = 1;
		}
		
		fgets(author, 100000, file);		/* reads the author line of the file and stores it under author */
		author_form = sscanf(author, "Author: %2000[^\n] ", author);		/* strips the read line of "Author: " */
		if (author_form != 0){
			sscanf(author, "%100[^\n] ", sample.author);		/* saves the remains under sample.author */
		} else {
			corrupt = 1;
		}

		fgets(year_str, 100000, file);		/* reads the year line of the file and stores it under year_str */
		sscanf(year_str, "Year: %2000[^\n] ", year_str);		/* strips the read line of "Year: " */
		year_int = strtol(year_str, &ptr, 10);		/* converts the remains into an int and stores it under year_int */
		if (year_int > 0 && year_int < 10000 ){		/* checks if the year is valid */
			sample.year = year_int;		/* if valid assigns year to sample.year */
		} else {
			corrupt = 1;		/* if not it will set the file to corrupted and end the while loop */
		}
		fgets(singleline, 150, file);		/* reads line in between books */
		if (strcmp(singleline,"\n") != 0){
			corrupt = 1;		/* if this line is not empty the file is set to corrupt */
		}

		if (corrupt == 0){
			local_book_array[count++] = sample;		/* adds the book to the local array */
			total_added++;
		} else {
			fprintf(stderr, "File provided is corrupt\n");
		}
	}

	if (corrupt == 0){
		/* if the file is not corrupted all of the books from the file will be stored to the global array book_array */
		/* if the file is corrupted none of the books will be stored */
		for (i = 0; i <= total_added; i++){
			book_array[MAX_BOOKS - i] = local_book_array[i];
		}
	}

	fclose(file);		/* closes the file once we are done with it */
}

