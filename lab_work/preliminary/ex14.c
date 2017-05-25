/* 14. Replace a word in a file
	Ex.  all 'the' with 'and' */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX 30		

int match (char *, char *);
char * replace (char *, char *, int);
void display_file(char *);

main(){

	char line [MAX];
	char file_name [20];
	char old_pattern [] = "the";
	char new_pattern [] = "and";
	char *sptr;

	int c;
	int position;

	FILE *fpr, *fpw;

	fpr = fopen ("ex14.input", "r");

	//sprintf (file_name, "ex14_output_%d", getpid());
	strcpy (file_name, "ex14.output");

	fpw = fopen (file_name, "w");

	while (fgets (line, MAX, fpr) != NULL){
		sptr = line;
				// return -1 if not found.
				while ((position = match (sptr, old_pattern)) >= 0) 
					sptr = replace (sptr, new_pattern, position);
		
		fputs (line, fpw);
	}

	fclose (fpr);
	fclose (fpw);

	display_file ("ex14.input");
	display_file (file_name);
}

int match ( char in[], char pat []){
	int i, j, k;
	for (i = 0; in [i] != '\0'; i++){
		for ( j = i, k = 0;  pat [k] != '\0' && in [j] == pat [k]; j++, k++)	
						;
		if ( k > 0 && pat [k] == '\0' )
			return i;
	}
	return -1;
}

char * replace (char src[], char new_pat[], int pos){
	int i, k;
	for (i = pos, k = 0; new_pat[k] != '\0'; i++,k++)
		src [i] = new_pat [k];	
	return src + i;
}

void display_file(char * fname){
	int c;
	FILE *fp;
	printf ("\n\n************< %s  >****************\n", fname);
	fp = fopen (fname, "r");
	while ( (c = getc (fp)) != EOF )
		putchar (c);
	fclose (fp);
}
