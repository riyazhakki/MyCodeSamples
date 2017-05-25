
# include <stdio.h>
# include <curses.h>
# include <ncurses.h>


main () {
initscr ( );
printw ("Hellow World" );
refresh ( );
endwin ( );
}
