// TUNEABLE ARRAY

# include <stdio.h>

extern int nums[];
extern int nmax;

print_nums(int n);

main(){
	int next, n = 0;
	int place;

	for (place = 0; place < nmax; place++){
		printf ("Enter %dth number", place);
		if (scanf ("%d", nums + place) != 1 )
			break;
	}
	n = place;
	print_nums(n);
}

print_nums(int n){
	int place;

	for (place = 0; place < n; place++) 
		printf ("\nyour %dth number = %d", place, nums [place]); 
}
