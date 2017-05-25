# include <stdio.h>
# include <sys/shm.h>

int main ( ) {

	int id;

	id = shmget ( (key_t) getuid ( ) + 1, 100, 0600 );

	if ( id >= 0 )
		printf ( "%s\n", shmat (id, 0, 0600 ) );
	else 
		printf ( "Cannot acess shared memory\n" );
}
