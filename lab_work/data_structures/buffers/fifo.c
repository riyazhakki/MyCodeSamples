/* fifo.c : 	Layered version of crclar buffer
	Modules: buffer.c buffer.h
	Application : fifo.c
*/


# include <stdio.h>
# include <stdlib.h>
# include "buffer.h"

# define NBYTES 50

char line [100];
BUFFER *bd;

main () {
	int size;
	register char *p;
	char data;
	int num;

	bd = create_buf ( NBYTES );
	if ( bd == BUF_FAIL )  exit (1);

	while (1) {

		printf ("\n\nUse E to exit; \nO<num><CR> to Read num chars; \nChars to Write;");
		if (fgets (line, 100, stdin) == NULL )
			exit (2);
		
		for (p = line; *p == ' ' || *p == '\t'; p++); // trim white spaces

		switch (*p) {
			default:
				if ( buf_full(bd) ){
					printf ("\nBuffer Full....!\n");
					continue;
				}
				while (*p) {
					while( *p == ' ' || *p == '\t'|| *p == '\n' )
						p++; 

					if(*p != '\n')
					write_buf ( bd, *p );
					p++;
				}
				break;

			case 'o': case 'O':
				++p;
				for (; *p == ' ' || *p == '\t'; p++); // trim white spaces
				if ( isdigit(*p) )
					num = atoi (p);
				else{
					printf ("usage: O<num> <CR>\n");
					exit (3);
				}

				while(num){
					if (buf_empty(bd)){ 
						printf ("\nBuffer Empty....!\n");
						break;
					}
					data = read_buf ( bd );
					printf ("%c\n", data);
					num--;
				}
				break;

			case 'e' : case 'E':
				while (!buf_empty(bd)){
					data = read_buf ( bd );
					printf ("%c\n", data);
				}
			
				exit (0);
		}
	}
}

