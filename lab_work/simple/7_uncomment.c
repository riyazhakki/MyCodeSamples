/* 7.  To remove all comments from a C program.
		Usage: a.out < x.c > y.c  */


# include <stdio.h>
# include <stdlib.h>

main () {

	int c;
	int inside_string, inside_comment, slash_read, star_read;

	inside_string = inside_comment = slash_read = star_read = 0;

	while ((c = getchar ()) !=EOF) {
		if (inside_string) {
			if (c == '"' && slash_read == 0)
				inside_string = 0;

			putchar (c);
			if (c == '\\')
				slash_read = 1;
			else
				slash_read = 0;
			continue;
		}

		if (c == '"') {
			inside_string = 1;
		   	slash_read = 0;
			putchar (c);
			continue;
		}

		if (inside_comment) {
			if (c == '/' && star_read)
				inside_comment = 0;
			else if (c == '*')
				star_read = 1;
			else 
				star_read = 0;
			continue;
		}
		
		if (c == '*' && slash_read) {
			inside_comment = 1;
			star_read = 0; 
			slash_read = 0;
			continue;
		}

		if (slash_read) 
			putchar ('/');
		if (c == '/')
			slash_read = 1;
		else {
			putchar (c);
			slash_read = 0;
		}
	}
	if (inside_comment || inside_string) {
		fprintf (stderr, "Syntax Error...\n");
	}
	exit (0);
}
