# include <sys/ipc.h>
# include <sys/sem.h>
# include <sys/unistd.h>
# include <stdio.h>
main () {
	int key;
	scanf ("%d", &key );
	semctl( key, 0, IPC_RMID );
}
