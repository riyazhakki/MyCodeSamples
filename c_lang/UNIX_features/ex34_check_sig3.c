
# include <stdio.h>
# include <unistd.h>
# include <signal.h>

void handler ( int signo  ) {
	printf ( "Caught a signal\n" );
}

int main () {
	char x;

	signal ( SIGALRM, handler );

	/* First param is signal number. 
		second param is a pointer to function */
		
		alarm ( 3 );

		// Do Something
		read ( 0, &x, 1 );
}
