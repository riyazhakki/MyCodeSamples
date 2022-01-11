/* 5. entab.c: (approximate converse of ex04.c(detab.c)).
	  To replace a seres of spaces (and tabs) by the minimum number
	  of tab characters and spces.	

  NOTE: If a series of spaces does not reach the next tabstop 
  		cannot be replaced by <TAB>.  Any trailing tabs and 
		spaces on a line can probably be ignored. */

# include <stdio.h>
# include <stdlib.h>

main(int argc, char *argv[]){
	int n, c, in_pos, out_pos;


	if (argc < 2){
		fprintf (stderr, "Usage a.out <tab stop> \n");
		exit (1);
	}

	sscanf (argv[1], "%d", &n);

	if ( n < 2 || n > 10 ){
		fprintf (stderr, "Tabstops in range 2,3,...10 \n");
		exit (2);
	}

	in_pos = out_pos = 0;
	
	while ((c = getchar()) != EOF){
		if ( c == '\n'){
		putchar ('\n');
		in_pos = out_pos = 0;
		continue;
		}
		if (c == ' ')
			in_pos ++;

		else if (c == '\t'){
			do
				in_pos++;
			while ( in_pos % n);
		}
		else{
			//printf("in_pos / n * n)=> %d\n", in_pos / n * n);
			while (out_pos < in_pos / n * n){
				putchar ('\t');
				do
					out_pos++;
				while ( out_pos % n);
			}

			while ( out_pos < in_pos){
				putchar (' ');
				out_pos ++;
			}
			putchar (c);
			in_pos++;
			out_pos++;
		}
	}
	exit (0);
}
