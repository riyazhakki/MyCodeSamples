# include <stdio.h>
# include <stdlib.h>
# include <string.h>
main(int argc, char **argv){

	 
	 
	 char week[7][3] = {"Su", "Mo", "Tu", "We", "Tu", "Fr", "Sa"	};
	

	//char *week [] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
	int month_days [] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i;
	int year;
	int m_no = atoi(argv[1]); 			// month number
	int day;  							// day of month
	int position = 6;
	int days_count = 0;

	// input validation
	if( argc < 1 || argc > 3){
		printf ("Invalid date...!\n");
		exit (0);
	}

	 if ( m_no >= 1 && m_no <= 12 ){
		if ( m_no > 1 ){

			// count no. of days
	 		for ( i = 1; i < m_no; i++ ) 
	 			days_count += month_days [i - 1];

			// find cursor position
			days_count += position;
			position = days_count % 7;
		}

		// print day's names 
		for ( i = 0; i < 7; i++ )
			printf ("%5s", week[i]);  
		printf ("\n");

		// position cursor
		for	( i = 0; i < position; i++ )
			printf ("%5c", ' ');
		
		// print days of month
		for ( day = 1; day <= month_days[m_no - 1]; day++ ){
			position++;
			printf ("%5d", day);

			if ( position % 7 == 0 )
				printf ("\n");
		}
		printf ("\n");
	}
	else
		printf ("Invalid month...!\n");
}
