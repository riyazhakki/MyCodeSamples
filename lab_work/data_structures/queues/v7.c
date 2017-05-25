/* v7.c: Onle application that uses the queue library */

# include <stdio.h>
# include <stdlib.h>

//# include "queue.h"
//# include "queuea.h"		// using Ep & Dp Qfull, Qempty operations.

# include "squeue.h"		//for strechable queue

# define NITEMS 3

char line [100];
QUEUE *qd;

main () {
	int num;
	register char *p;

	qd = openQ ( NITEMS, sizeof (num) );
	if ( qd == Q_FAIL )  exit (1);

	while (1) {

		printf ("Use E to exit; D to dequeue; Number to enqueue; ");
		if (fgets (line, 100, stdin) == NULL )
			exit (2);
		
		for (p = line; *p == ' ' || *p == '\t'; p++);

		switch (*p) {
			case '0' : case '1': case '2': case '3': case '4':
			case '5' : case '6': case '7': case '8': case '9':
				if (Qfull(qd)){
					printf ("Queue Full....!\n");
					//continue;
				}

				num = atoi (p);
				enQ ( qd, (char * )&num );
				break;
			case 'd': case 'D':
				if (Qempty(qd)){ 
					printf ("Queue Empty....!\n");
					break;
				}
				deQ ( qd, (char *) &num);
				printf ("%d\n", num); 
				break;
			case 'e' : case 'E':
				while (!Qempty(qd)){
					deQ (qd, (char *)&num);
					printf ( "%d\n", num );
				}
			exit (0);
		}
	}
}

