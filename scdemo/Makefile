
OBJS = tcp_process.o tcp_client.o tcp_server.o
CC = gcc
CFLAGS = -D__FOR_FILE
TARGET = tcp_client tcp_server

all:tcp_client tcp_server

tcp_client:tcp_process.o tcp_client.o
	${CC} -o $@ $^

tcp_server:tcp_process.o tcp_server.o
	${CC} -o $@ $^

clean:
	-rm -f *.o

realclean: clean
	-rm -f ${TARGET}
