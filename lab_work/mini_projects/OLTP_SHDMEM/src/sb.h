
struct record {
	char 	name [20];   /* 0 - 19 */
 	char 	phone [10];  /* 20 - 29 */
	int		flag:1;		/*30 - 31*/
	int 	balance;	/*32 - 35*/
};

# define INACTIVE	0
# define ACTIVE 	1

# define TOTAL_REC lseek ( fd, 0, SEEK_END ) / sizeof (rec) 

void create 	( int fd, int to_server );
void deposit 	( int fd, int to_server );
void withdraw	( int fd, int to_server );
void change 	( int fd, int to_server );
void balance 	( int fd, int to_server );


