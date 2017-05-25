/* 13. Program that sorts a list of integers in ascending order. Use descending
		order if -r switch is specified in command line.  */


# include <stdio.h>

# define MAX 40

void bubble_sort (int *, int);
void bubble_rsort (int *, int);
void display(int *, int );

main(int argc, char** argv){
	int *ints = NULL;
	int nints = 0;
	int i;

	char line [MAX];
	char *p;
	char *item;
	char save;
	
	printf ("Enter integers:\n");

	while (fgets (line, MAX, stdin)){
	p = line;
		while (1){
			while (*p == ' ' || *p == '\t' || *p == '\n')
				p++;				// skip leading spaces

			if (!*p)
				break;

			item = p;
			while (*p != ' ' && *p != '\t' && *p != '\n')
				p++;	

			save = *p;
			*p = '\0';

				ints = (int *) realloc (ints, ++nints * sizeof (int));
				ints [nints -1] = atoi (item);
			
			*p = save;
				
		}
	}

	if (argv [1] != NULL && !strcmp (argv[1], "-r"))
		bubble_rsort (ints, nints);
	
	else
		bubble_sort (ints, nints);

	printf ("******** OUTPUT *********\n");
	display(ints, nints);
		
}

void bubble_sort ( int * ints, int nints){
	
	int i, j, temp;

	for (i = 0; i < nints - 1; i++){
		for (j = i+1; j < nints; j++){
			if (ints [i] > ints[j]){
				temp = ints [i];
				ints [i] = ints [j];
				ints [j] = temp;
			}
		}
	}
}


void bubble_rsort ( int * ints, int nints){
	
	int i, j, temp;


	for (i = 0; i < nints - 1; i++){
		for (j = i+1; j < nints; j++){
			if (ints [i] < ints[j]){
				temp = ints [i];
				ints [i] = ints [j];
				ints [j] = temp;
			}
		}
	}
}

void display(int *ints, int nints){
int i;
	for (i = 0; i < nints; i++)
			printf ("%d\n", ints[i]);
		
}
