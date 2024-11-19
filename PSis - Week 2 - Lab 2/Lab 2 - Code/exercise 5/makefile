make: server client

server: server.o funcs.so
	gcc -o server server.o -ldl

client: client.o
	gcc -o client client.o

server.o: server.c data_struct.h
	gcc -c server.c

client.o: client.c data_struct.h
	gcc -c client.c

funcs.so: funcs.c
	gcc funcs.c -o funcs.so -ldl -shared -fPIC

clean:
	rm -f *.o *.so client server