
struct record {
	char 	name [20];   /* 0 - 19 */
 	char 	phone [10];  /* 20 - 29 */
	int		flag:1;		/*30 - 31*/
	int 	balance;	/*32 - 35*/
};

# define INACTIVE	0
# define ACTIVE 	1

# define KEY 12345

# define TOTAL_REC lseek ( fd, 0, SEEK_END ) / sizeof (rec) 
