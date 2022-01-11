# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>

main ( ) {
WINDOW *mainwin;
if ( (mainwin = initscr()) == NULL ){
	fprintf (stderr, "Error...\n");
	exit (1);
}


attron (A_BLINK);
mvaddstr(13,33, " Hello, World!");
refresh ();
sleep (3);


delwin ( mainwin );
endwin();
setvbuf ( stdout, NULL, _IOLBF, 0 );
refresh ();

}
