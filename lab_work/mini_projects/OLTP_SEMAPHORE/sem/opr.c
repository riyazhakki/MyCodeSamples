# include "sem.h"
# include <errno.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <sys/types.h>
# include <sys/unistd.h>

main ( ) {
	int semd;
	extern int errno;

	struct sembuf sop;
	union semun arg;

	semd = semget ( KEY, 1, 0777 );
	if ( semd != -1 )
		printf ( "Semaphore %d created successfully...\n", semd);
	 printf ("%d : val: %d\n", getpid (), semctl (semd, 0, GETVAL)); 

	 if ( errno == EEXIST ){
			printf ("sem exist...\n");
	 }

	arg.val = 1;

	if ( ( semctl ( semd, 0, SETVAL, arg ) ) == 0 ) 
		printf ("Semaphore Initialized...\n" );

	 printf ("%d : val: %d\n", getpid (), semctl (semd, 0, GETVAL)); 

	/****** P **********/
	sop.sem_num = 0;
	sop.sem_op 	= -1;
	sop.sem_flg = IPC_NOWAIT;

	while (  semop (semd, &sop, 1 ) == -1 ){
		printf ("Waiting....\n");
		printf ("%d: val: %d\n",getpid (),  semctl (semd, 0, GETVAL)); 
		sleep (1);
	}
	printf ("semop P successfull...\n" );

	 printf ("%d val: %d\n",getpid (), semctl (semd, 0, GETVAL)); 
	/********* RMW Cycle ***********/	

	sleep (8);

	/****** V **********/

	sop.sem_num = 0;
	sop.sem_op 	= 1;
	sop.sem_flg = IPC_NOWAIT;
	if ( ( semop (semd, &sop, 1 ) ) == 0 )
		printf ("semop V successfull...\n" );

	 printf ("%d val: %d\n",getpid (), semctl (semd, 0, GETVAL)); 
}
