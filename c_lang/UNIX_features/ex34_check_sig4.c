# include <stdio.h> 
# include <unistd.h> 
# include <signal.h>
# include <setjmp.h>

jmp_buf main_place;

void handler ( int signo ) {
	printf ( "Caught a signal\n" );
	longjmp ( main_place, 1 );
}

int main () {
	char x;
	int ret;

	signal ( SIGALRM, handler );
	alarm ( 3 );

	// Do Something
	if ( setjmp ( main_place ) == 0 ) {
		ret = read ( 0, &x, 1 );
		printf ( "ret = %d\n", ret );
		// this message NEVER gets printed
		// if no KB CHARACTERS ARE TYPED
	}

	printf ( "Got longjmp \n" );
}
