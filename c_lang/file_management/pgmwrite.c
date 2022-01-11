/* Benchmark the buffering effect of fwrite(3) versus the unbuffered write (2)*/

/* pgmwrite.c: open(2) with O_CREAT & O_TRUNC write 10,000 bytes one byte at a      time. 
		time the program: 
				time a.out <CR>
*/

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

main () {
	int fd;
	int i = 0;
	char c = 'R';

	fd = open ( "pgmwrite.dat", O_WRONLY | O_CREAT | O_TRUNC, 0777 );

	if ( fd < 0 ) {
		printf ("File cannot open\n");
		exit (1);
	}
	while (i++ < 10000) {
		write ( fd, c, sizeof ( c ) ); 
	}
	close (fd);
}

