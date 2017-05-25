/* ex52_middle_app.c: singly-linked-list of chronological order  */

# include <stdio.h>
# include <stdlib.h>
# include "ex53_slist.h"
# define LENGTH	50	

char line [LENGTH];
LIST *ld;
static int number;

static void help (void);
static void do_append (void);
static void do_delete (void);
static void do_read_first (void);
static void do_read_middle (void);
static void do_read_next (void);
static void do_read_last (void);
static void do_close_list (void);

main () {
	register char *p;
	
	ld = open_list (sizeof number ); 	//integer linked list
	if (ld == L_FAIL){
		fprintf (stderr, "Can't create list\n");
		exit (1);
	}
	while (1){
		printf ("list option:");
		if (fgets (line, LENGTH, stdin) == NULL ) 
			exit (2);

		for ( p = line; *p == ' ' || *p == '\t'; p++ );

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
				do_append();
				break;
			case 'f': case 'F': do_read_first (); break;
			case 'm': case 'M': do_read_middle (); break;
			case 'l': case 'L': do_read_last (); break;
			case 'n': case 'N': do_read_next (); break;
			case 'd': case 'D': do_delete (); break;
			case 'e': case 'E': 
						reset_transferred(ld);
						printf ("Still in list \n");
						while (read_next (ld, (char *)&number ) == L_SUCCESS )
							printf ("\t %d\n", number );
						
						exit (0);
		}
	}
}

static void help () {
	printf ("Use the following \n\n");
	printf ("	<number> <cr> to append \n");
	printf ("	e <cr> to exit from program \n");
	printf ("	m <cr> to read middle number \n");
	printf ("	h <cr> to print this help message\n");
	if (list_empty(ld)) return;
	printf (" f <cr> to read first number\n");
	printf (" l <cr> to read last number\n");
	printf (" n <cr> to read next number\n");
	printf (" d <cr> to delete a number\n");
}

static void do_append (){
	if (append (ld, (char *) &number) == L_SUCCESS)
		printf ("ok\n");
	else printf ("Cannot append\n");
}

static void do_read_first() {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_first (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_read_middle () {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_middle (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}
static void do_read_next() {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_next (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_read_last() {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_last (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_delete () {
	if (list_empty(ld)) printf ("empty list \n");
	else if (delete (ld) == L_SUCCESS)
		printf ("ok\n");
	else printf ("you have to read item before delete \n");
}

