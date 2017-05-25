/* 4. hexadecimal dump of a file. 
		Format needed:
			0000:	xx	xx	xx	xx	 xx	xx	xx	xx		xx	xx	..
			0010:	xx	xx	xx	xx	 xx	xx	xx	xx		xx	xx	..
			0020:	..	.. */

# include <stdio.h>
# include <stdlib.h>

main (int argc, char *argv[]) {
	int c, pos;
	FILE *fp;

	if (argc < 2) {
		fprintf (stderr, "Usage: a.out <filename>\n");
		exit (1);
	}

	while (--argc) {
		fp = fopen (*++argv, "r");
		if (fp == NULL){
			fprintf (stderr, "Cannot open file %s\n", *argv);
			exit (2);
		}
		printf ("Hex Dump for %s \n", *argv);

		for (pos = 0; (c = getc (fp)) != EOF; pos++){
			if (! (pos & 15))
				printf ("\n %04x:", (unsigned) pos);
			else if (! (pos &7))
				printf ("  ");
			else if (! (pos & 3))
				printf (" ");

			printf ("%02x ", (unsigned char) c);
		} 
		
		printf ("\n\n");
		fclose (fp);
	}
}

