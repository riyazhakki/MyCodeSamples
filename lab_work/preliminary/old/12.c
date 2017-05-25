/* 12. Write the program 'last.c' that prints the last 'n' lines of a file.
		By default 'n' should be 5. But your program should accept an 
		optional argument (like -8). Use standard input if input file name
		is not specified.	*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void read_file(char *, int);
void read_stdin (int);

main (int argc, char** argv){
	int nlines = 5;
	char **p = argv;
	char filename [50]; 


	while(*p){
		p++;	 				// move to next word (after a.out)
		if (!*p)
			break;				// end of input when end of rows

		while (**p == ' ' || **p == '\t' || **p == '\n')
			++*p;               	// skip white spaces 

		if (!**p)
			p++;	               // move to next word when end of word

		if (**p == '-'){
			++*p;							// move to next letter
			if (isdigit (**p)){
				nlines = atoi (*p);
				*++p; 						// move to next word
			}
			if (!*p)
				read_stdin (nlines);
			else if (**p != '-'){
				strcpy (filename, *p);	// copy a word next to -xx to filename	
				read_file(filename, nlines);   // read a file and display
			}
		}
		else { 
			strcpy (filename, *p);		// copy a word to filename (when no -)	
			read_file(filename, nlines);   // read a file and display
		}
	}
}

void read_file (char *filename, int nlines)
{
	int c, t, line_count= 0;
	int errno;

	FILE *fp = NULL;

	fp = fopen (filename, "r");
	if (fp == NULL){
		printf ("Error in opening file %s.\n", filename);
		exit (1);
	}

	printf("---------------------------------\n");
	printf ("File: %s\t\t No. of lines: %d\n", filename,nlines);
	printf("---------------------------------\n");

	fseek (fp, -2, SEEK_END);
	t = ftell (fp);

										// Position file pointer
	while (1){
		c = getc (fp);  
		if (c == '\n'){
			line_count++;
		}
		if (line_count >= nlines || t == 0)	
			break;

		fseek (fp, --t, SEEK_SET);
		t = ftell (fp);
	}
										// Display file
	while((c = getc (fp)) != EOF)
		putchar (c);

	fclose (fp);
}

void read_stdin (int nlines){
	int c;
	FILE *fp;

	fp = fopen ("temp", "w");

	while ((c = getchar()) != EOF){
		putc (c, fp);	
	}
	fclose (fp);
	read_file ("temp", nlines);
}

