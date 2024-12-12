all: human-client


human-client: human-client.c ../balls.pb-c.c
	gcc human-client.c ../balls.pb-c.c -o human-client -g -lzmq -lncurses -lprotobuf-c