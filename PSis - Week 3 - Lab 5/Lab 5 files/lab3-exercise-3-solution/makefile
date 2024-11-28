all: player server remote-display-client

player: human-client.c
	gcc -g human-client.c -o player -lzmq -lncurses
	
server: server-exercise-3.c
	gcc -g server-exercise-3.c -o server -lzmq -lncurses

remote-display-client: remote-display-client.c
	gcc -g remote-display-client.c -o remote-display-client -lzmq -lncurses

clean:
	rm player server remote-display-client
