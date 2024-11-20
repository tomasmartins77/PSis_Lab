make: server human-control-client

server: server.o FIFOUtils.o
	gcc -o server server.o FIFOUtils.o -lncurses

human-control-client: human-control-client.o  FIFOUtils.o
	gcc -o human-control-client human-control-client.o FIFOUtils.o -lncurses

server.o: server.c remote-char.h
	gcc -c server.c

human-control-client.o: human-control-client.c remote-char.h
	gcc -c human-control-client.c

FIFOUtils.o: FIFOUtils.c FIFOUtils.h
	gcc -c FIFOUtils.c -o FIFOUtils.o

clean:
	rm -f *.o *.so human-control-client server