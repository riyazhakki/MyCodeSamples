/* printpid.c:  simple program to create child process */
# include <stdio.h>

int main () {
	printf ( "%d\n", getpid() ); 	fork( );
	printf ("%d", getppid() );
	//__fpurge ( stdout );
	//fflush(stdout);
//	printf ( "%d\n", getpid() ); 	fork( );
//	printf ( "%d\n", getpid() ); 	fork( );
//	printf ( "%d\n", getpid() ); 	
}

