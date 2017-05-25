
struct chan_request {
	long type;
	int message;
};

struct chan_reply {
	long type;
	int result;
	int to_server;
	int from_server;
	int server_pid;
};

struct windup {
	long type;
	int message;
	int to_server;
	int from_server;
};

struct windup_reply{
	long type;
	int result;
};

struct deposit {
	long type;
	int message;
	int acc_no;
	int amount;
};

struct deposit_reply {
	long type;
	int result;
};


struct withdraw {
	long type;
	int message;
	int acc_no;
	int amount;
};

struct withdraw_reply {
	long type;
	int result;
};

struct balance {
	long type;
	int message;
};

struct balance_reply {
	long type;
	int result;
};

struct change {
	long type;
	int message;
	char phone [11];
};

struct change_reply {
	long type;
	int result;
};

union transaction {
	long type;
	struct chan_request chan_request;
	struct windup windup;
	struct deposit deposit;
};

struct message {
	long type;  // for channel
	union transaction transaction;
};

union msg {
	long type;
	struct message message;
};


# define KEY_MSGQ getuid()+1
# define KEY_SEM  getuid()+2

# define BUSY 	1
# define IDLE	0

# define CHAN_REQUEST			1
# define MASTER_REQUEST			1
# define MASTER_REPLY 			2

# define CREATE					3
# define CREATE_REPLY 			4
# define DEPOSIT				5
# define DEPOSIT_REPLY 			6
# define BALANCE				7
# define BALANCE_REPLY 			8
# define CHANGE					9
# define CHANGE_REPLY 			10	
# define WINDUP					11	
# define WINDUP_REPLY			12
# define WINDUP_SUCCESS			13
# define WINDUP_FAIL			14

# define SUCCESS				15
# define FAIL					16
# define CHAN_FULL				17	
# define WAIT					18

# define BIG					100
