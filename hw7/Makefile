main: main.c libcalc.so
	gcc -o main.o -fPIC -c main.c
	gcc -shared main.o -o libcalc.so	
	gcc main.c -o main -ldl
	LD_LIBRARY_PATH=$PWD ./main
	rm -rf main.o
	



