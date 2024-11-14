prg: lib1.o prog1.o
	gcc -o prg lib1.o prog1.o

lib1.o: lib1.c lib.h
	gcc -c lib1.c

prog1.o: prog1.c
	gcc -c prog1.c

clean:
	rm -f *.o prg