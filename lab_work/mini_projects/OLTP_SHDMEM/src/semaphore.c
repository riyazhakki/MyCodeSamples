# include <stdio.h>
# include <sys/ipc.h>
# include <sys/sem.h>

void sem_lock ( ) {

	struct sembuf sop;
	int semd;

	semd = semget ( (key_t) getuid ( ), 1 , IPC_CREAT | 0744 );

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

	struct sembuf sop;
	int semd;

	semd = semget ( (key_t) getuid ( ), 1, IPC_CREAT | 0744 );
	sop.sem_num = 0;
	sop.sem_op  = 1;
	sop.sem_flg = IPC_NOWAIT;

	semop ( semd, &sop, 1 );
}
