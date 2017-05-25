# include "sem.h"

main () {
	extern int errno;
	int semd;

	union semun arg;

	semd = semget ( KEY, 1, IPC_CREAT | IPC_EXCL | 0777 );
	if ( semd != -1 )
		printf ( "%d: Semaphore %d created successfully...\n",getpid(), semd);

	else if ( errno == EEXIST ) {
		fprintf ( stderr, "Semaphore already exist...\n" );	
		exit ( 1 );
	}
	
	arg.val = 1;
	if ( ( semctl ( semd, 0, SETVAL, arg ) ) == 0 ) 
		printf ("Semaphore Initialized...\n" );
}

