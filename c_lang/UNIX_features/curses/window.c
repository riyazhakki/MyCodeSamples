# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>

main ( ) {
WINDOW *mainwin, *childwin;
int ch;

int width = 23, height = 7;
int rows = 25, cols = 80;
int x = (cols - width)/2;
int y = (rows - height) / 2;

if ( (mainwin = initscr()) == NULL ){
	fprintf (stderr, "Error...\n");
	exit (1);
}

noecho ();
keypad (mainwin, TRUE);

childwin = subwin (mainwin, height, width, y, x);
box (childwin, 0, 0);
mvwaddstr (childwin, 1, 4, "Move the window");
mvwaddstr (childwin, 2, 2, "with the arrow keys");
mvwaddstr (childwin, 3, 6, "or HOME/END");
mvwaddstr (childwin, 5, 3, "Press q to quit");
refresh ();

while ( (ch = getch() ) != 'q' ) {
	switch ( ch ) {
		case KEY_UP: if ( y > 0 ) --y; break;
		case KEY_DOWN: if ( y < (rows - height ) ) ++y; break;
		case KEY_LEFT: if ( y > 0 ) --x; break;
		case KEY_RIGHT: if ( x < ( cols - width ) ) ++x; break;
	}
	mvwin(childwin, y, x);
}

delwin ( childwin );
delwin ( mainwin );
endwin();
refresh ();

}
