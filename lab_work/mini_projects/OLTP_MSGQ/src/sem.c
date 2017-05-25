# include <stdio.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include "sem.h"

struct sembuf sop;
static int semd;

void sem_lock ( ) {

	semd = semget ( (key_t)KEY_SEM, 1 , IPC_CREAT | 0744 );

	sop.sem_num = 0;
	sop.sem_op  = -1;
	sop.sem_flg = IPC_NOWAIT;

	while ( semop ( semd, &sop, 1 ) != 0 ){
		printf ( "\033[5m PLEASE WAIT...\033[0m\r" );
		fflush ( stdout );
	}
		printf ( "ACCESS GRANTED\n\n" );
}

void sem_unlock ( ) {

	semd = semget ( (key_t)KEY_SEM, 1, IPC_CREAT | 0744 );
	sop.sem_num = 0;
	sop.sem_op  = 1;
	sop.sem_flg = IPC_NOWAIT;

	semop ( semd, &sop, 1 );
}
