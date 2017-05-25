BIN = ../bin

all : server shutdown client deposit windup clean 

shutdown 	: 	shutdown.c 
					cc -o $(BIN)/shutdown shutdown.c

server		: 	server.c dbase.h libsb.a 
					cc -o $(BIN)/server server.c -L. -lsb 

client 		:  	client.c dbase.h  
					cc -o $(BIN)/client client.c -L. -lsb 

windup		: 	windup.c dbase.h 
					cc -o $(BIN)/windup windup.c -L. -lsb 

deposit 	:	deposit.c sb.h  
					cc -o $(BIN)/deposit deposit.c -L. -lsb 

libsb.a		:	sb.o dynamic.o get_spid.o semaphore.o lockf.o
					ar crsv libsb.a sb.o dynamic.o get_spid.o semaphore.o lockf.o

dynamic.o 	: 	dbase.h 

sb.o		: 	sb.h

get_spid.o	:	 

semaphore.o	: 

lockf.o 	: 

clean		:
				@-rm lockf.o
				@-rm semaphore.o
				@-rm sb.o
				@-rm get_spid.o
				@-rm dynamic.o
