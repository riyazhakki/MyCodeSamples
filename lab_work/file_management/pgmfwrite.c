/* Benchmark the buffering effect of fwrite(3) versus the unbuffered write (2)*/

/* pgmwrite.c: fopen(3) with "w" fwrite 10,000 bytes one byte at a time. 
		time the program: 
				time a.out <CR>
*/

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

main () {
	FILE *fp;
	int i = 0;
	char c = 'R';

	fp = fopen ( "pgmfwrite.dat", "w");
	if ( fp == NULL ) {
		printf ("File cannot open\n");
		exit (1);
	}
	while (i++ < 1000) {
		fwrite ( &c, sizeof ( c ), 1, fp ); 
	}
	fclose (fp);
}

