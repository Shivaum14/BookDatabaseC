/*
 *                 DO NOT MODIFY
 * You will not submit this file on SurreyLearn, 
 * your code will be compiled against
 * the original version we provided you.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* maximum number of books that can be stored at once (relevant only
   to storage using an array) */
#define MAX_BOOKS 200

#define MAX_TITLE_LENGTH  100
#define MAX_AUTHOR_LENGTH 100

/* Book structure
 */
struct Book
{
	/* Book details */
	char title[MAX_TITLE_LENGTH+1];   /* name string */
	char author[MAX_AUTHOR_LENGTH+1]; /* job string */
	int  year;                        /* year of publication */

	/* pointers to left and right branches pointing down to next level in
      the binary tree (for if you use a binary tree instead of an array) */
	struct Book *left, *right;
};

/* tree of books, initialized to NULL. Ignore if using an array */
extern struct Book *book_tree;

/* array of books, and number of books stored initialized to zero. Ignore
 * if using a binary tree */
extern struct Book book_array[MAX_BOOKS];
extern int no_books;



/* Now the function definitions */
/* Functions for part 1 */
void menu_add_book(void);
void menu_print_database(void);

/* Functions for part 2 */
void menu_get_book_details(void);
void menu_delete_book(void);

/* Functions for part 3 */
void read_book_database ( char *file_name );

