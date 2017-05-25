/* 6. fold.c: fold long input lines after the last non-blank character
			  before nth column or input.   */


# include <stdio.h>
# include <stdlib.h>

main (int argc, char *argv []) {
	int n, m, c, collect, pos;
	char * word;
//	char * malloc (int);

	if (argc != 3) {
		fprintf (stderr, "Usage: a.out <width> <tabstop>\n");
		exit (1);
	}
	sscanf (argv [1], "%d", &n);
	if (n < 10 || n > 70) {
		fprintf (stderr, "width range should be between 10 - 70\n");
		exit (2);
	}
	sscanf (argv [2], "%d", &m);
	if (m < 2 || m >10) {
		fprintf (stderr, "Tabstops in range 2,3..10\n");
		exit (3);
	}

	word = (char *) malloc (n + 1);
	collect = 0;
	pos = 0;
	
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			word [collect] = '\0';
			printf ("%s\n", word);
			collect = 0;
			pos = 0;
			continue;
		}

		if (c == '\t') {
			do pos ++;
			while (pos % m);
		}
		else 
			pos ++;
			

		if (pos >= n+1) {					// boundary condition
			word [collect] = '\0';
			printf ("\n%s", word);
			pos = collect;
			collect = 0;
		}
		
		else if (c == ' '|| c == '\t') {
			word [collect] = '\0';
			printf ("%s", word);
			collect = 0;
			putchar (' ');
			continue;
		}

		word [collect ++] = c;
	}
/*	if (collect) {					
		word [collect] = '\0';
		printf ("%s", word);
	} */
	exit (0);
}
