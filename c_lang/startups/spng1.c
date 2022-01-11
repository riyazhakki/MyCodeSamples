# include <stdio.h>

int main ( ) {
	char num [5];

	num[4] = '\0';
	for ( num[0] = '1'; num[0] <= '9'; num[0]++ )
		for ( num[1] = '1'; num[1] <= '9'; num[1]++ )
			for ( num[2] = '1'; num[2] <= '9'; num[2]++ )
				for ( num[3] = '1'; num[3] <='9'; num[3]++ )
					printf ( "%s\n", num );
}
