/* 4. 	A program that replaces tabs from the input by proper number of spaces
			till next  tab stop.
		version (a): assume fixed set of tab stops, every n columns.
					 n can be
					  (i)	symbolic literal
					  (ii)	an argument to main	*/


# include <stdio.h>
# include <stdlib.h>

main(int argc, char **argv){

	int c, col, n = 2;

	if (argc < 2){
		fprintf (stderr, "Usage: a.out <tabstop> \n");
		exit (1);
	}
	sscanf (argv[1], "%d", &n);

	if ( n < 2 || n > 10){
		fprintf (stderr, "Tabstops in range 2,3,.., 10 \n");
		exit (2);
	}	
	col = 0;
	while ((c = getchar ()) != EOF){
		if (c == '\t'){
			do{
				putchar (' ');
				col++;
			}while (col % n);
		}
		else{
			putchar (c);
			col++;
			if (c == '\n')
				col = 0;
		}
	}
}
	
