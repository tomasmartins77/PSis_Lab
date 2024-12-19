all: client server

client: zmq-client.c
	gcc zmq-client.c -o client -lzmq -lpthread

server: zmq-mt-server.c
	gcc zmq-mt-server.c -o server -lzmq -lpthread
