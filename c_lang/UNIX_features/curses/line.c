# include <stdio.h>
# include <stdlib.h>
# include <curses.h>
# include <unistd.h>

main () {

if ( (initscr()) == NULL ){
	fprintf (stderr, "Error in initializing curses...!\n");
	exit (1);
}

hline ('-', 90);

refresh ();
endwin ();
setvbuf ( stdout, NULL, _IOLBF, 0 );

}


