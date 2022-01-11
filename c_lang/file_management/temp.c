# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

main () {
	int fd;
	char str[] = "Hello world";

	fd = open ("file.dat", O_WRONLY | O_CREAT, 0777);
	if (fd < 0) {
		printf ("file cannot open...");
		exit (1);
	}
	write ( fd, str, sizeof ( str ));
	close (fd);
}
