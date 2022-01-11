/* Read an input file one byte at a time and display on the standard output */

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

main (int argc, char* argv[]) {

	int fd;
	char c;

	if ( argc >= 2)
		fd = open (argv[1], O_RDONLY);
	else
		fd = open ("../temp.c", O_RDONLY);

	if (fd == -1){
		printf ("can't open a file\n");
		exit (1);
	}

	while (read (fd, &c, 1) == 1)
		write (0, &c, 1);
	
	close (fd);
	
}
