CC=gcc
CFLAGS=-pthread

all: tcpclient udpclient tcpserver udpserver

tcpclient: tcpclient.c
	$(CC) $(CFLAGS) -o tcpclient tcpclient.c 

udpclient: udpclient.c
	$(CC) $(CFLAGS) -o udpclient udpclient.c 

tcpserver: tcpserver.c
	$(CC) $(CFLAGS) -o tcpserver tcpserver.c

udpserver: udpserver.c
	$(CC) $(CFLAGS) -o udpserver udpserver.c

clean_ports:
	fuser -k 8000/tcp && fuser -k 8001/tcp && fuser -k 8002/tcp

start_tcpserver: tcpserver
	./tcpserver --bufsize 100 --port 10050
start_udpserver: udpserver
	./udpserver --bufsize 1024 --port 20001
start_tcpclient: tcpclient
	./tcpclient --bufsize 100 --ip 0.0.0.0 --port 10051
start_udpclient: udpclient
	./udpclient --bufsize 1024 --ip 0.0.0.0 --port 20002

remove: 
	rm -rf udpserver tcpserver udpclient tcpclient