# include <stdio.h>
# include <sys/ipc.h>
# include <sys/msg.h>

# include "dbase.h"

main ( ) {
	int msgd;
	int size;

	union msg msgp;
	struct msqid_ds arg;

		
	size = sizeof (msgp) - sizeof (msgp.type);

		msgd =	msgget ( KEY_MSGQ, IPC_CREAT );

		//msgrcv ( msgd, &msgp, sizeof (msgp)  -20, IPC_NOWAIT ); 
		msgrcv ( msgd, &msgp, size, 0, IPC_NOWAIT );

		msgctl ( msgd, IPC_STAT, &arg );

		printf ("last msgsnd pid: %d\n", arg.msg_lspid );

		printf ( "msgp.type: %d\n", msgp.type );
		printf ( "message: %d\n", msgp.message.transaction.type );
}
