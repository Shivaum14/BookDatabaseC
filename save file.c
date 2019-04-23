#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 9

//struct for node
struct node {
    char *value;            // all void* types replaced by char*
    struct node *p_left;
    struct node *p_right;
};

//use typedef to make calling the compare function easier
typedef int (*Compare)(const char *, const char *);

//inserts elements into the tree
void insert(char* key, struct node** leaf, Compare cmp)
{
    int res;
    if( *leaf == NULL ) {
        *leaf = (struct node*) malloc( sizeof( struct node ) );
        (*leaf)->value = malloc( strlen (key) +1 );     // memory for key
        strcpy ((*leaf)->value, key);                   // copy the key
        (*leaf)->p_left = NULL;
        (*leaf)->p_right = NULL;
        //printf(  "\nnew node for %s" , key);
    } else {
        res = cmp (key, (*leaf)->value);
        if( res < 0)
            insert( key, &(*leaf)->p_left, cmp);
        else if( res > 0)
            insert( key, &(*leaf)->p_right, cmp);
        else                                            // key already exists
            printf ("Key '%s' already in tree\n", key);
    }
}

//compares value of the new node against the previous node
int CmpStr(const char *a, const char *b)
{
    return (strcmp (a, b));     // string comparison instead of pointer comparison
}

char *input( void )
{
    static char line[MAXLEN+1];       // where to place key    
    printf("Please enter a string : ");
    fgets( line, sizeof line, stdin );
    return ( strtok(line, "\n" ));    // remove trailing newline
}

//recursive function to print out the tree inorder
void in_order(struct node *root)
{
    if( root != NULL ) {
        in_order(root->p_left);
        printf("   %s\n", root->value);     // string type
        in_order(root->p_right);
    }
}

//searches elements in the tree
void search(char* key, struct node* leaf, Compare cmp)  // no need for **
{
    int res;
    if( leaf != NULL ) {
        res = cmp(key, leaf->value);
        if( res < 0)
            search( key, leaf->p_left, cmp);
        else if( res > 0)
            search( key, leaf->p_right, cmp);
        else
            printf("\n'%s' found!\n", key);     // string type
    }
    else printf("\nNot in tree\n");
    return;
}

void delete_tree(struct node** leaf)
{
    if( *leaf != NULL ) {
        delete_tree(&(*leaf)->p_left);
        delete_tree(&(*leaf)->p_right);
        free( (*leaf)->value );         // free the key
        free( (*leaf) );
    }
}

//displays menu for user
void menu()
{
    printf("\nPress 'i' to insert an element\n");
    printf("Press 's' to search for an element\n");
    printf("Press 'p' to print the tree inorder\n");
    printf("Press 'f' to destroy current tree\n");
    printf("Press 'q' to quit\n");
}

int main()
{
    struct node *p_root = NULL;
    char *value;
    char option = 'x';

    while( option != 'q' ) {
        //displays menu for program
        menu();

        //gets the char input to drive menu
        option = getch();           // instead of two getchar() calls

        if( option == 'i') {
            value = input();
            printf ("Inserting %s\n", value);
            insert(value,  &p_root, (Compare)CmpStr);
        }
        else if( option == 's' ) {
            value = input();
            search(value, p_root, (Compare)CmpStr);     // no need for **
        }
        else if( option == 'p' ) {
            in_order(p_root);
        }
        else if( option == 'f' ) {
            delete_tree(&p_root);
            printf("Tree destroyed");
            p_root = NULL;
        }
        else if( option == 'q' ) {
            printf("Quitting");
        }
    }
return 0;
}























////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include "database_main.h"

int title_cmp(char existing, char new){
	return (strcmp(existing, new));
}

Book* insert(struct Book* book_tree,struct Book new){
	new -> left = new -> right = NULL;
	if (book_tree == NULL){		/* if the tree is empty */
		book_tree = new;
	} else if(title_cmp(book_tree -> author, new -> author) == 1){
		book_tree -> left = insert(book_tree -> left, new);
	} else if(title_cmp(book_tree -> author, new -> author) == -1){
		book_tree -> right = insert(book_tree -> right, new);
	}
	return book_tree;
}
/* menu_add_book():
 *
 * Add new book to database
 */
void menu_add_book(void)
{
	fprintf(stderr,"ADDING BOOK\n");

	struct Book *new;
	char new_title[MAX_TITLE_LENGTH], new_author[MAX_AUTHOR_LENGTH];
	int new_year;

	/* create book */
	new = (struct Book *) malloc(sizeof(struct Book));
	fprintf(stderr, "enter the title of the book\n");
	scanf("%s", new_title);
	strcpy(new -> title, new_title);

	fprintf(stderr, "enter the auther of the book\n");
	scanf("%s", new_author);
	strcpy(new -> author, new_author);

	fprintf(stderr, "enter the year of publication\n");
	scanf("%d", &new_year);
	new -> year = new_year;

	/* add book to binary tree */
	book_tree = insert(book_tree, new);

   /* fill in the code here in part 1, and add any extra functions you need */
}

/* menu_print_database():
 *
 * Print database of books to standard output in alphabetical order of title.
 */
void menu_print_database(void)
{
	printf("PRINTING DATABASE\n");
   /* fill in the code here in part 1, and add any extra functions you need */
}	    
