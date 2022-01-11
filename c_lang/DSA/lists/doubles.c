/*Exercise 51: 
doubles.c :  A sorted list based on some property of data 
Additional report : print in ascending order.

	We need an enhanced user interface and let us use:
		<Number> <cr>	: to enter a number into the list
		s <cr>			: read smallest number from the list
		n <cr>			: read next number from the list
		b <cr>			: read biggest number from the list
		p <cr>			: read previous number from the list
		h <cr> 			: display help message
		e <cr>			: exit			***********/

# include <stdio.h>
# include <stdlib.h>
# include "nlist.h"
# define LENGTH	50	

char line [LENGTH];
LIST *ld;
static int number;

int compare_int (char * data1, char * data2);
static void help (void);
static void do_insert_in_list (void);
static void do_delete (void);
static void do_read_smallest(void);
static void do_read_bigger (void);
static void do_read_biggest (void);
static void do_read_smaller (void);
static void do_close_list (void);

main () {
	register char *p;
	
	ld = open_list (sizeof number, compare_int ); 	//integer linked list
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
				do_insert_in_list ();
				break;
			case 's': case 'S': do_read_smallest (); break;
			case 'b': case 'B': do_read_biggest (); break;
			case 'n': case 'N': do_read_bigger (); break;
			case 'p': case 'P': do_read_smaller (); break;
			case 'd': case 'D': do_delete (); break;
			case 'e': case 'E': 
						reset_transferred(ld);
						printf ("Still in list \n");
						while (read_bigger (ld, (char *)&number ) == L_SUCCESS )
							printf ("\t %d\n", number );
						
						exit (0);
		}
	}
}

static void help () {
	printf ("Use the following \n\n");
	printf ("	<number> <cr> to append \n");
	printf ("	e <cr> to exit from program \n");
	printf ("	h <cr> to print this help message\n");
	if (list_empty(ld)) return;
	printf (" s <cr> to read smallest number\n");
	printf (" b <cr> to read biggest number\n");
	printf (" n <cr> to read next number\n");
	printf (" p <cr> to read previous nubmer\n");
	printf (" d <cr> to delete a number\n");
}

static void do_insert_in_list (){
	if (insert_in_list (ld, (char *) &number) == L_SUCCESS)
		printf ("ok\n");
	else printf ("Cannot append\n");
}

static void do_read_smallest() {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_smallest (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_read_bigger () {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_bigger (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_read_biggest() {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_biggest (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_read_smaller() {
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if (read_smaller (ld, (char *) & number) == L_SUCCESS)
		printf ("%d\n", number);
	else printf ("something wrong! no more items \n");
}

static void do_delete () {
	if (list_empty(ld)) printf ("empty list \n");
	else if (delete (ld) == L_SUCCESS)
		printf ("ok\n");
	else printf ("you have to read item before delete \n");
}

int compare_int ( char *data1, char *data2 ) {
	return (*((int *)data1)) - (*((int *)data2));
}
