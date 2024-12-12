all: machine-client


machine-client: machine-client.c ../balls.pb-c.c
	gcc machine-client.c ../balls.pb-c.c -o machine-client -g -lzmq -lprotobuf-c