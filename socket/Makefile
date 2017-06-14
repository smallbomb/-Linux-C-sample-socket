CC = g++
CFLAGS = -g -Wall -ansi


all: clientsocket serversocket

clientsocket: clientsocket.c
	$(CC) $(CFLAGS) clientsocket.c -o clientsocket
serversocket: serversocket.c
	$(CC) $(CFLAGS) serversocket.c -o serversocket

clean:
	rm -f clientsocket serversocket

