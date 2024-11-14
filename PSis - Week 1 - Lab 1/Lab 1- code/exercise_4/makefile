prg: lib1.so lib2.so main.o
	gcc -o prg lib1.so lib2.so main.o -ldl

main.o: main.c
	gcc -c main.c

lib1.so: lib1.c lib.h
	gcc lib1.c -o lib1.so -ldl -shared -fPIC

lib2.so: lib2.c lib.h
	gcc lib2.c -o lib2.so -ldl -shared -fPIC

clean:
	rm -f *.o *.so prg