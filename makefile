programa: main.o leer_archivo.o
	g++ -o programa main.o leer_archivo.o

main.o: 
	g++ -c main.cpp

leer_archivo.o: 
	g++ -c -Iinclude src/leer_archivo.cpp

run: 
	./programa
clean:
	rm -f programa *.o
