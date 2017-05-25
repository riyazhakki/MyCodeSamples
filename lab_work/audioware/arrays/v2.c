// DYNAMIC ARRAY

# include <stdio.h>
# include <stdlib.h>

# define HUGE 100	

int nmax;
int *nums;
int sum = 0;
//char * malloc( int );

main(){
	int place;
	int n;

	printf ("Enter max no. of numbers = ");
	if (scanf("%d", &nmax) != 1)
		exit (1);
	if (nmax <1 || nmax > HUGE){
		fprintf (stderr, "Enter no. properly\n");
		exit (2);
	}
	nums = (int *) malloc (nmax * sizeof *nums);
	place = 0;
	while (place < nmax){
		printf ("Enter %dth number =",place);
		if (scanf("%d", nums + place) != 1)
			break;
		place++;
	}
	n = place;
	print_nums(n);
	exit (0);
}

print_nums(int n){
	int place;

	for (place = 0; place < n; place++)
		printf ("your %dth number = %d\n", place, nums [place]);
}

