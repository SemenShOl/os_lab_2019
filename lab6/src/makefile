CC=gcc
CFLAGS=-pthread

all: server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c 2>/dev/null >/dev/null

client: client.c
	$(CC) $(CFLAGS) -o client client.c 2>/dev/null >/dev/null

clean_ports:
	fuser -k 8000/tcp && fuser -k 8001/tcp && fuser -k 8002/tcp

clean:
	rm -rf server client 2>/dev/null >/dev/null
start_server: 
	./server --port 8000 --tnum 2 & ./server --port 8001 --tnum 2 & ./server --port 8002 --tnum 2
start_client: 
	./client --k 15 --mod 1000  --servers ./servers.txt