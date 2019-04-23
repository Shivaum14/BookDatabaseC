/*
 *                 DO NOT MODIFY
 * You will not submit this file on SurreyLearn, 
 * your code will be compiled against
 * the original version we provided you.
 */

#include "database_main.h"

/* tree of books, initialized to NULL. Ignore if using an array */
struct Book *book_tree = NULL;

/* array of books, and number of books stored initialized to zero. Ignore
 * if using a binary tree */
struct Book book_array[MAX_BOOKS];
int no_books = 0;


/* get_tree_depth():
 *
 * Recursive function to compute the number of levels in a binary tree.
 */
int get_tree_depth ( struct Book *book, int level )
{
	int level1, level2;

	/* return with the current level if we've reached the bottom of this
      branch */
	if ( book == NULL ) return level;

	/* we need to go to the next level down */
	level++;

	/* count the number of levels down both branches */
	level1 = get_tree_depth ( book->left,  level );
	level2 = get_tree_depth ( book->right, level );

	/* return the depth of the deepest branch */
	if ( level1 > level2 ) return level1;
	else return level2;
}

/* menu_print_tree():
 *
 * Print tree to standard output. You can use this function to print out the
 * tree structure for debugging purposes. It is also used by the testing
 * software to check that the tree is being built correctly.
 *
 * The first letter of the title of each book is printed. A "*" indicates
 * a NULL left or right pointer.
 */
void menu_print_tree(void)
{
	int no_levels, level, size, i, j, k;
	struct Book **row;

	/* find level of lowest node on the tree */
	no_levels = get_tree_depth ( book_tree, 0 );

	/* abort if database is empty */
	if ( no_levels == 0 ) return;

	/* compute initial indentation */
	assert ( no_levels < 31 );

	row = (struct Book **) malloc((1 << (no_levels-1))*sizeof(struct Book *));
	row[0] = book_tree;
	printf ( "\n" );
	for ( size = 1, level = 0; level < no_levels; level++, size *= 2 )
	{
		/* print books at this level */
		for ( i = 0; i < size; i++ )
		{
			if ( i == 0 )
				for ( j = (1 << (no_levels - level - 1)) - 2; j >= 0; j-- )
					printf ( " " );
			else
				for ( j = (1 << (no_levels - level)) - 2; j >= 0; j-- )
					printf ( " " );

			if ( row[i] == NULL )
				printf ( " " );
			else
				printf ( "%c", row[i]->title[0] );
		}

		printf ( "\n" );

		if ( level != no_levels-1 )
		{
			/* print connecting branches */
			for ( k = 0; k < ((1 << (no_levels - level - 2)) - 1); k++ )
			{
				for ( i = 0; i < size; i++ )
				{
					if ( i == 0 )
						for ( j = (1 << (no_levels - level - 1))-3-k; j >= 0; j-- )
							printf ( " " );
					else
						for ( j = (1 << (no_levels - level)) - 4 - 2*k; j >= 0; j-- )
							printf ( " " );

					if ( row[i] == NULL || row[i]->left == NULL )
						printf ( " " );
					else
						printf ( "/" );

					for ( j = 0; j < 2*k+1; j++ )
						printf ( " " );

					if ( row[i] == NULL || row[i]->right == NULL )
						printf ( " " );
					else
						printf ( "\\" );
				}

				printf ( "\n" );
			}

			/* adjust row of books */
			for ( i = size-1; i >= 0; i-- )
			{
				row[2*i+1] = (row[i] == NULL) ? NULL : row[i]->right;
				row[2*i]   = (row[i] == NULL) ? NULL : row[i]->left;
			}
		}
	}

	free(row);
}	    

/* codes for menu */
#define ADD_CODE     0
#define DETAILS_CODE 1
#define DELETE_CODE  2
#define PRINT_CODE   3
#define TREE_CODE    4
#define EXIT_CODE    5

int main ( int argc, char *argv[] )
{
	/* check arguments */
	if ( argc != 1 && argc != 2 )
	{
		fprintf ( stderr, "Usage: %s [<database-file>]\n", argv[0] );
		exit(-1);
	}

	/* read database file if provided, or start with empty database */
	if ( argc == 2 )
		read_book_database ( argv[1] );

	for(;;)
	{
		int choice, result;
		char line[301];

		/* print menu to standard error */
		fprintf ( stderr, "\nOptions:\n" );
		fprintf ( stderr, "%d: Add new book to database\n",      ADD_CODE );
		fprintf ( stderr, "%d: Get details of book\n",       DETAILS_CODE );
		fprintf ( stderr, "%d: Delete book from database\n",  DELETE_CODE );
		fprintf ( stderr, "%d: Print database to screen\n",    PRINT_CODE );
		fprintf ( stderr, "%d: Print tree\n",                   TREE_CODE );
		fprintf ( stderr, "%d: Exit database program\n",        EXIT_CODE );
		fprintf ( stderr, "\nEnter option: " );

		if ( fgets(line, 300, stdin) == 0 ) continue;

		result = sscanf ( line, "%d", &choice );
		if ( result != 1 )
		{
			fprintf ( stderr, "corrupted menu choice\n" );
			continue;
		}

		switch ( choice )
		{
		case ADD_CODE: /* add book to database */
			menu_add_book();
			break;

		case DETAILS_CODE: /* get book details from database */
			menu_get_book_details();
			break;

		case DELETE_CODE: /* delete book from database */
			menu_delete_book();
			break;

		case PRINT_CODE: /* print database contents to screen
			     (standard output) */
			menu_print_database();
			break;

		case TREE_CODE: /* print tree to screen (standard output) */
			menu_print_tree();
			break;

			/* exit */
		case EXIT_CODE:
			break;

		default:
			fprintf ( stderr, "illegal choice %d\n", choice );
			break;
		}

		/* check for exit menu choice */
		if ( choice == EXIT_CODE )
			break;
	}

	return 0;
}
