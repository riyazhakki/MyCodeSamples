/* ex55_slist_converge_app.c: Check if two singly linked lists converge  */

# include <stdio.h>
# include <stdlib.h>
# include "ex55_slist.h"
# define LENGTH	50	

char line [LENGTH];
LIST *ld1;
LIST *ld2;

static int number;

void input_list (LIST * ld);
void display_lists (LIST *ld);
static void help (void);
static int do_isConverge (LIST *ld1, LIST *ld2);
int compare_int (char * data1, char * data2);
static void do_append (LIST *ld);
static void do_delete (LIST *ld);
static void do_read_first (LIST *ld);
static void do_read_next (LIST *ld);
static void do_read_last (LIST *ld);
static void do_close_list (LIST *ld);

main () {
	int choice;
	
	ld1 = open_list (sizeof number, compare_int ); 	//integer linked list
	if (ld1 == L_FAIL){
		fprintf (stderr, "Can't create list\n");
		exit (1);
	}
	
	ld2 = open_list (sizeof number, compare_int ); 	//integer linked list
	if (ld2 == L_FAIL){
		fprintf (stderr, "Can't create list\n");
		exit (1);
	}

	while (1) {
		printf ("1. List1 operations\n");
		printf ("2. List2 operations\n");
		printf ("3. Check Convergence\n");
		printf ("4. Display Lists1\n");
		printf ("5. Display Lists2\n");
		printf ("6. Exit \n");

		printf ("Enter the choice:");
		scanf ("%d", &choice);

		switch (choice) {
			case 1: input_list (ld1);
						break;
			case 2: input_list (ld2); 
						break;
			case 3: do_isConverge (ld1, ld2); 
						break;
			case 4: display_lists (ld1); 
						break;
			case 5: display_lists (ld2); 
						break;
			case 6: exit (0);

			default : printf ("Invalid choice...\n");
		}
	}
}

void input_list (LIST *ld) {
	register char *p;
	while (1){
		printf ("list option:");
		if (fgets (line, LENGTH, stdin) == NULL ) 
			exit (2);

		for ( p = line; *p == ' ' || *p == '\t'; p++ );

		if ( *p == 'e' )
			break;

		switch (*p) {
			case 'h': case'H':
				help ();
				break;
				/* these cases can droped! */
			default :
				help ();
				break;
			case '0':case '1':case '2':case '3':case '4':
			case '5':case '6':case '7':case '8':case '9':
				number = atoi(p);
				do_append(ld);
				break;
			case 'f': case 'F': do_read_first (ld); break;
			case 'l': case 'L': do_read_last (ld); break;
			case 'n': case 'N': do_read_next (ld); break;
			case 'd': case 'D': do_delete (ld); break;
		}
	}
}

void display_lists (LIST *ld ) {

	reset_transferred1(ld);

	while (read_next (ld, (char *)&number ) == L_SUCCESS )
		printf ("\t %d\n", number );

}
static void help () {
	printf ("Use the following \n\n");
	printf ("	<number> <cr> to append \n");
	printf ("	e <cr> to exit from program \n");
	printf ("	h <cr> to print this help message\n");
	printf (" f <cr> to read first number\n");
	printf (" l <cr> to read last number\n");
	printf (" n <cr> to read next number\n");
	printf (" d <cr> to delete a number\n");
}

static int do_isConverge (LIST *ld1, LIST *ld2){

	if ( isConverge (ld1, ld2) == 0 ) 
		printf ("*****Two lists are converge******\n");
	else
		printf ("*****Two lists are not converge*******\n");

}

int compare_int (char * data1, char * data2){
	return * ( int * ) data1 - * ( int * ) data2;
}

static void do_append (LIST *ld){
	if (append (ld, (char *) &number) == L_SUCCESS)
		printf ("ok\n");
	else printf ("Cannot append\n");
}

static void do_read_first(LIST *ld) {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_first (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_read_next(LIST *ld) {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_next (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_read_last(LIST *ld) {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_last (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_delete (LIST *ld) {
	if (list_empty(ld)) printf ("empty list \n");
	else if (delete (ld) == L_SUCCESS)
		printf ("ok\n");
	else printf ("you have to read item before delete \n");
}

