/* runls.c : Program to rn ls -l as a child process  */


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

main ()
{
	switch (fork () ) {
		case 0 : printf ( "Child...\n");
				 execl ("/bin/ls", "ls", "-l", NULL );
				 fprintf ( stderr, "can't exec \n");
				 exit (0);
	}
		printf ("Parent...\n");
}
