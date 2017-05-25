
BIN = ../bin

all : startup shutdown server client deposit windup clean

deposit :	 deposit.c sb.h msg.o
				cc -o $(BIN)/deposit deposit.c msg.o

startup	:	startup.c
				cc -o $(BIN)/startup startup.c

shutdown : 	shutdown.c 
				cc -o $(BIN)/shutdown shutdown.c

server	: 	server.c dbase.h msg.o dynamic.o sem.o
			cc -o $(BIN)/server server.c msg.o dynamic.o sem.o

client :  	client.c dbase.h msg.o
				cc -o $(BIN)/client client.c msg.o

dynamic.o : dynamic.c dbase.h msg.o sem.o
				cc -c dynamic.c msg.o sem.o

windup	: 	windup.c dbase.h msg.o
				cc -o $(BIN)/windup windup.c msg.o

msg.o	:	msg.c msg.h
				cc -c msg.c

sem.o	: 	sem.c sem.h
				cc -c sem.c

clean	:
