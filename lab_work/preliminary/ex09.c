# include <stdio.h>
# include <stdlib.h>

main(int argc, char **argv){

	char *month [] = {"January", "Febaruary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	char *week [] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
	int month_days [2][13] = {
							{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
						 	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
						  };

	int i, j;
	int m_no;				 			// month number
	int year = 0;							// year
	int day;  							// day of month
	int position;						// position the cursor
	int days_count = 6;					// count no. of days for position
	int leap = 0;						// indicate leap year

	m_no = atoi(argv[1]); 			// red from command line arg
	year = atoi(argv[2]);			 //  and converted string to integer 
	
	// input validation
	if (argc != 3 || m_no < 1 || m_no > 12 || year < 1) {
		printf ("Invalid date...!\n");
		exit (0);
	}

			// count no. of days
		for ( i = 1; i <= year; i++ ){

			if ( i <= 1752 )
				leap = (i % 4 == 0);
			else
				leap = (i % 4 == 0 && i % 100 != 0) || (i % 400 == 0);

			if ( i == year ) // don't count days for current year
				break;

			for ( j = 1; j <= 12; j++ )
	 			days_count += month_days [leap] [j];
			
			if ( i == 1752 ){
				days_count -= 11;
				//printf ("Testing 2\n+++++++++++++++\n");
			}

		}

		// days_count for current year

		 	for ( i = 1; i < m_no; i++ ){
				if ( year == 1752 && i == 9 ){  // exe only when a.out 10 1752
					days_count -= 11;
				
				}
				B
	 			days_count += month_days [leap] [i];
			}

		// print header MMMMM YYYY
		printf ("\n--< %s%5d >--\n", month[m_no - 1], year );
				
		// find cursor position
		position = days_count % 7;

		// print day's names 
		for ( i = 0; i < 7; i++ )
			printf ("%3s", week[i]);  
		printf ("\n");

		// position cursor
		for	( i = 0; i < position; i++ )
			printf ("%3c", ' ');
	
		// print days of month
		for ( day = 1; day <= month_days[leap][m_no]; day++ ){

			if (year == 1752 && m_no == 9 && day > 2 && day < 14)
				continue;

			position++;
			printf ("%3d", day);
			
			// new line afer every 7 days
			if ( position % 7 == 0 )
				printf ("\n");
		}
		printf ("\n\n");
	
}
