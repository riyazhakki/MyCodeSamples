
all : startup shutdown dynamic server client deposit windup clean

deposit : deposit.c sb.h
			cc -o deposit deposit.c 

startup	:	startup.c
			cc -o startup startup.c

shutdown : shutdown.c 
			cc -o shutdown shutdown.c

server	: server.c dbase.h msg.o
			cc -o server server.c msg.o

client : client.c dbase.h
			cc -o client client.c

dynamic : dynamic.c dynamic.h dbase.h 
			cc -o dynamic  dynamic.c

msg.o	:	msg.c dbase.h sb.h msg.h
			cc -c msg.c

windup	: windup.c dbase.h
			cc -o windup windup.c
clean	:
