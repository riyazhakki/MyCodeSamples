# include <stdio.h>
# include <signal.h>

void handler () {
	printf ( "Cought Signal...\n" );
}

main () {
	signal ( SIGUSR1, handler );

	while (1)
		pause ( );
}


