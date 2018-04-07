
all: serv clie

serv: udp_server.o
	gcc -o $@ $<

clie: udp_client.o
	gcc -o $@ $<

clean:
	-rm -f *.o
	-rm -f serv clie
