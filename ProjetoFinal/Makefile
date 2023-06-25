all: prog.e

prog.e: algoritmo1.o algoritmo2.o
	gcc -o prog.e algoritmo1.o algoritmo2.o

algoritmo1.o: algoritmo1.c
	gcc -o algoritmo1.o -c algoritmo1.c

algoritmo2.o: algoritmo2.c 
	gcc -o algoritmo2.o -c algoritmo2.c

clean:
	rm -f *.o prog.e		
	
