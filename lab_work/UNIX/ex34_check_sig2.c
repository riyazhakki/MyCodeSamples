
# include <stdio.h>
# include <unistd.h>
# include <signal.h>

int main () {
	signal ( SIGALRM, SIG_IGN );
	/* First param is signal number. ( Never SIGKILL )
		second param is a pointer to function */
		
		alarm ( 3 );

		// Do Something
	while ( 1 ) ;  // This is simply waiting
}
