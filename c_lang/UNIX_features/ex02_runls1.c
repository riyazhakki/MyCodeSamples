/* runls.c : Program to rn ls -l as a child process  */


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

main ()
{
	char *str[] = {"ls","-l","-i",NULL};
	switch (fork () ) {
		case 0 : printf ( "Child...\n");
				// execl ("/bin/ls", "ls", "-l", NULL );
				 execvp (str[0], str);
				 fprintf ( stderr, "can't exec \n");
				 exit (0);
	}
	wait (NULL);

		printf ("Parent...\n");
}
