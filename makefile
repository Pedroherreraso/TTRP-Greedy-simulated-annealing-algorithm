TTRP: main.o leer_archivo.o
	g++ -o TTRP main.o leer_archivo.o

main.o: 
	g++ -c main.cpp

leer_archivo.o: 
	g++ -c -Iinclude src/leer_archivo.cpp

run: 
	./TTRP
clean:
	rm -f TTRP *.o
