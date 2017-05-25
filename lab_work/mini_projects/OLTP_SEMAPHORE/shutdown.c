# include "sem.h"

main () {
	int semd;
	semd = semget ( KEY, 1, 0777 );
	if ( ( semctl ( semd, 0, IPC_RMID) ) != -1 ) 
		printf ("Semaphore removed...\n");
}
