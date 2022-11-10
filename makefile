programa: main.o leer_archivo.o
	g++ -o programa main.o leer_archivo.o

main.o: main.cpp leer_archivo.h
	g++ -c main.cpp

leer_archivo.o: leer_archivo.cpp leer_archivo.h
	g++ -c leer_archivo.cpp

run: 
	./programa
clean:
	rm -f *.o
