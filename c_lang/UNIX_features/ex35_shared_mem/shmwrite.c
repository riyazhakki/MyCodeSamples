# include <stdio.h>
# include <sys/shm.h>
# include <string.h>

int main ( ) {
	int id;

	id = shmget ( (key_t) getuid(), 100, 0600 | IPC_CREAT );

	if ( id >= 0 )
		strcpy ( shmat ( id, 0, 0 ), "Hello World\n" );
	else
		printf ( "Cannot create shared memory \n" );
}
