# include <stdio.h>
# include <unistd.h>
# include <string.h>


struct chan {
	char tty [50];
	int to_server;
	int from_server;
};

main ( ) {

	int c;
	int found = 0;
	struct chan chan, chan1;
	FILE *fptr;
	fptr = fopen ( "sb_conf", "a+" ); 

	fseek ( fptr, 0 , SEEK_SET );

	printf ( "ttyname\t    to_server \t from_server \n" );
	while (1){
		c = fscanf  ( fptr, "%s%d%d", 
					chan1.tty, &chan1.to_server, &chan1.from_server );
		if ( strcmp ( chan1.tty, ttyname(1) ) == 0 )
			found = 1;
		if ( c == EOF )
			break;
		printf  ( "%s\t%d\t\t%d\n", chan1.tty, chan1.to_server, chan1.from_server );
	}

	if ( !found ){
		strcpy ( chan.tty, ttyname ( 1 ) );  //or ttyname( STDOUT_FILENO )
		chan.to_server 	 = 2 * chan1.to_server + 1;
		chan.from_server = 2 * chan1.from_server + 2;

		fprintf ( fptr, "%s\t%d\t%d\n", 
								chan.tty, 
								chan.to_server, 
								chan.from_server );
	}
}
