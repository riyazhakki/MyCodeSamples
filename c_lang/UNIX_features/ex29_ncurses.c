# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>

main ( ) {

//WINDOW *mainwin;

if ( (initscr()) == NULL ){
	fprintf (stderr, "Error...\n");
	exit (1);
}


attron (A_BOLD);
mvaddstr(1,16, " Hello, World!");
attroff (A_BOLD);

attron (A_BLINK);
mvaddstr(2,33, " Hello, World!");
attroff (A_BLINK);

attron (A_UNDERLINE);
mvaddstr(3,33, " Hello, World!");
attroff (A_UNDERLINE);

attron (A_NORMAL);

//delwin ( mainwin );

refresh ();
endwin();
setvbuf ( stdout, NULL, _IOLBF, 0 );

}
