/* printpid.c:  simple program to create child process */
# include <stdio.h>

int main () {
	printf ( "Child\tParent\n--------------\n");
	printf ( "%d  %d\n", getpid(), getppid() ); 	fork( );
	printf ( "%d  %d\n", getpid(), getppid() ); 	fork( );
	printf ( "%d  %d\n", getpid(), getppid() ); 	fork( );
	printf ( "%d\n", getpid() ); 	
}

