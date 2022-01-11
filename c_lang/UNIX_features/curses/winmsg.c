# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>

main ( ) {
WINDOW *mainwin, *childwin;
int ch;

int width = 33, height = 7;
int rows = 25, cols = 80;
int x = (cols - width)/2;
int y = (rows - height) / 2;

if ( (mainwin = initscr()) == NULL ){
	fprintf (stderr, "Error...\n");
	exit (1);
}

noecho ();
childwin = subwin (mainwin, height, width, y, x);
box (childwin, 0, 0);
mvwaddstr (childwin, 1, 2, "User of this terminal is");
mvwaddstr (childwin, 3, 6, "coming soon...");
mvwaddstr (childwin, 5, 3, "Press q to continue...");
refresh ();

while ( (ch = getch() ) != 'q' ) { };

delwin ( childwin );
delwin ( mainwin );
endwin();
refresh ();
return 0;
}
