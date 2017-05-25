# include <stdio.h>
# include <stdlib.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <sys/types.h>
# include <errno.h>

# define KEY 12345

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};


