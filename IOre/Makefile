
CC = gcc
CFLAGS =
RM = rm -f

all:client server

client:client_framework.o process.o
	$(CC) -o $@ $^

server:server_framework.o process.o
	$(CC) -o $@ $^

clean:
	-${RM} *.o

realclean: clean
	-${RM} client server
