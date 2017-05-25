/* nums.c : 
	Layered version of binary ordered treee
		Modules : tree.c tree.h
		Application : nums.c
*/

# include <stdio.h>
# include <stdlib.h>
# include "tree.h"
# define LENGTH	50	

char line [LENGTH];
TREE *td;
static int number;

void print_leaves (TREE * td);
void print_leaf ( char *data, void * app_data);
int find_total (TREE *td);
void add_to_total ( char * data, void *app_data );
int compare_int (char * data1, char * data2);
static void help (void);
static void do_insert_in_tree ();

main () {
	register char *p;
	
	td = open_tree (sizeof number, compare_int ); 

	if (td == T_FAIL){
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
			default :
				help ();
				break;
			case '0':case '1':case '2':case '3':case '4':
			case '5':case '6':case '7':case '8':case '9':
				number = atoi(p);
				do_insert_in_tree ();
				break;
			case 'f': case 'F': read_first (td, (char *)&number );
								printf ("%d\n", number );
								break;
			case 'n': case 'N': read_next (td, (char *)&number );
								printf ("%d\n", number );
								break;
			case 'p': case 'P': print_leaves (td); break;
			case 't': case 'T': 
					printf ("Total: %d\n", find_total (td));
					break;
		case 'e': case 'E': exit (0);
		}
	
	}
}

static void help () {
	printf ("Use the following \n\n");
	printf ("	<number> <cr> insert leaf \n");
	printf ("	e <cr> to exit from program \n");
	printf (" 	f <cr> to read first\n");
	printf (" 	n <cr> to read next\n");
	printf (" 	t <cr> to print total\n");
	printf (" 	p <cr> to print leaves\n");
	printf ("	h <cr> to print this help message\n");
}

static void do_insert_in_tree (){
	if (add_leaf (td, (char *) &number) == T_SUCCESS)
		printf ("ok\n");
	else printf ("Cannot append\n");
}


void print_leaves (TREE * td){
	void print_leaf (char *, void*);
	navigate ( td, print_leaf, (void *)td );
}

void print_leaf ( char *data, void *app_data ){
	printf ("%d\n", *(int *) data );
}

int find_total (TREE *td){
	int total = 0;
	void add_to_total (char *, void *);
	navigate (td, add_to_total, (void *) &total );
	return total;
}

void add_to_total ( char * data, void *app_data ){
	*(int *) app_data += * (int *)data;
}

int compare_int ( char *data1, char *data2 ) {
	return (*((int *)data1)) - (*((int *)data2));
}
