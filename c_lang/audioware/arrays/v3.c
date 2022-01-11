// STRETCHABLE ARRAY

# include <stdio.h>
# include <stdlib.h>

int *nums;
//char *malloc (int);

main(){
	int next;
	int *old;
	int n = 0;

	nums = (int*) malloc (sizeof *nums);
	while(1){
		printf ("Enter %dth number = ", n);
		if (scanf ("%d", nums + n) != 1 )
			break;
		old = nums;
		nums = (int*) malloc((++n + 1) * sizeof *nums);

		for (next = 0; next < n; next++)
			nums [next] = old [next];

		free (old);
	}
	printf_nums(n);
	exit (0);
}

printf_nums(int n){
	int place;

	for (place = 0; place < 0; place++)
		printf ("your %dth number = %d\n", place, nums[place]);
}
	

