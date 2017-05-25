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
	int i, j, flag = 0;
	char filename [50] = "NULL"; 

	for (i = 1; i < argc; i++){

		strcpy (filename, "NULL");

		if ( argv[i][0] == '-' ){
			if (argv[i][1] == '\0'){
				read_stdin(nlines);
				flag = 1;
			}
			else {
				nlines = atoi (argv[i]) * -1;
				continue;
			}
		}
		else {
			strcpy (filename, argv[i]);
			read_file (filename, nlines);
		}
	}

	if (!strcmp (filename, "NULL") && argv[i] == NULL && !flag)
		read_stdin (nlines);
}

void read_file (char *filename, int nlines)
{
	int c, t, line_count= 0;

	FILE *fp;

	fp = fopen (filename, "r");
	if (fp == NULL){
		printf ("Error in opening file %s.\n", filename);
		exit (1);
	}

	printf("------------------------------------------\n");
	printf ("File: %s\t\t No. of lines: %d\n", filename,nlines);
	printf("------------------------------------------\n");

	fseek (fp, -2, SEEK_END);
	t = ftell (fp);

										// Position file pointer
	while (1){
		c = getc (fp);  

		if (c == '\n')
			line_count++;
		
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
	char filename [20];

	FILE *fp;

	sprintf (filename, "file%d", getpid());
	fp = fopen (filename, "w");

	while ((c = getchar()) != EOF)
		putc (c, fp);	
	
	fclose (fp);
	read_file (filename, nlines);
}

