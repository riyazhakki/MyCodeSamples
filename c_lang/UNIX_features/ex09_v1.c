// v1.c : accept and print numbers 
// A very simple program

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define RC_FILE	"ex09_myrc_test"

int int_size;
int clear_flag;

# define LINE_SIZE	200
# define INT_MAX	 10

void print_int ( int val );
void read_rc ( void );

int main ( ) {
	int * num; int n;
	int place;

	read_rc ( );	// read profile script

	if ( clear_flag )
		system ( "clear" );
	
	printf ( "Enter no. of numbers :");
	scanf ( "%d", &n );
	if ( n < 1 || n > 1000 ) {
		fprintf ( stderr, "out of range \n" );
		exit ( 1 );
	}

	num = malloc ( sizeof (int) * n );
	place = 0;
	while ( place < n ) {
		printf ("Enter next : " );
	    if ( scanf ( "%d", num + place ) != 1 ) break;
		place++;
	}
	printf ( "Your numbers\n" );
	for ( place = 0; place < n; place++ ) 
		print_int ( num [place] );
	putchar ('\n');
}

void print_int ( int val ) {
	int len;

	len = printf ( "%d", val );
	while ( len <= int_size ) {
		putchar (' ');
		len++;
	}
}

void read_rc ( ) {
	char * home, * file, * line, * p;
	int len; FILE *rc;

	clear_flag = 0;
	int_size = 5;
	home = getenv ( "HOME" );
	if ( home == NULL )
		return;
	len = strlen ( home ) + strlen ( RC_FILE ) + 2;
	file = malloc ( len );
	strcpy ( file, home );
	strcat ( file, "/" );
	strcat ( file, RC_FILE );
	rc = fopen ( file, "r" );
	if ( rc == NULL )
		return;
	line = malloc ( LINE_SIZE );
	while ( fgets ( line, LINE_SIZE, rc ) != NULL ) {
		for ( p = line; *p == ' ' || *p == '\t'; p++ ) ;
		if ( *p == '\n' || *p == '#' ) continue;
		if ( *p == 'i' && *(p+1) == 'n' && *(p+2) == 't' ) {
			p += 3;
			while ( *p == ' ' || *p == '\t' ) p++;
			if ( *p != '=' ) continue;
			p++;
			int_size = atoi ( p );
			if ( int_size < 1 || int_size > INT_MAX )
				int_size = INT_MAX;
			continue;
		}
		if ( !strncmp (p, "clear", 5) ) {
			p += 5;
			for ( ; *p == ' ' || *p == '\t'; p++ );
			if ( *p != '=' ) continue;
			p++;
			while ( *p == ' ' || *p == '\t' ) p++;
			if ( *p != 'y' && *p != 'Y' ) continue;
			clear_flag = 1;
		}
	}
	free ( line );
}
