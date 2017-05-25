/* assorted.c: Exercise 46.  Layered ver of assorted queue on array 
	Modules: aqueue.c aqueue.h
	Application: assorted.c
	uses cut piece data movement */

# include <stdio.h>
# include <stdlib.h>
# include "aqueue.h"

# define NBYTES 50

char line [100];
AQUEUE *aqd;
union data data;

main () {
	int size;
	char * item;
	int flag;
	register char *p;

	aqd = openQa ( NBYTES );
	if ( aqd == AQ_FAIL )  exit (1);

	while (1) {

		printf ("Use E to exit; D to DeQueue; Number to EnQueue; ");
		if (fgets (line, 100, stdin) == NULL )
			exit (2);
		
		for (p = line; *p == ' ' || *p == '\t'; p++); // trim white spaces

		item = p;

		flag = 0;
		while (( *p != '\0') && (*p != ' ' || *p != '\t' || *p != '\n') ){
			if (*p == '.' )
				flag = DOUBLE;
			p++;
		}

		p = item;

		switch (*p) {
			case '0' : case '1': case '2': case '3': case '4':
			case '5' : case '6': case '7': case '8': case '9':

				if (flag == DOUBLE){
					data.Double.type = DOUBLE;
					data.Double.value = atof (p);
					size = sizeof (data);
				}

				else if (atol(p) <= 32767 && atol(p) >= -32768 ){
						data.Short.type = SHORT;
						data.Short.value = (short) atol (p);
						size = sizeof (data);
					}
				else {
					data.Long.type = LONG;
					data.Long.value = atol (p);
					size = sizeof (data);
				}
					

				if (Qfull(aqd)){
					printf ("Queue Full....!\n");
					//continue;
				}

				enQa ( aqd, (char * )&data, size);
				break;

			case 'd': case 'D':
				if (Qempty(aqd)){ 
					printf ("Queue Empty....!\n");
					break;
				}
		
				deQa ( aqd, (char *) & data);
				display (&data);

				break;

			case 'e' : case 'E':
				while (!Qempty(aqd)){
					deQa (aqd, (char *)& data);
					display (&data);
				}
			
				exit (0);
		}
	}
}

