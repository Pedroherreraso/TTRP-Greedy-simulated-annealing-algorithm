TTRP: main.o leer_archivo.o vehiculos.o grafo.o
	g++ -o TTRP main.o leer_archivo.o vehiculos.o grafo.o

main.o: 
	g++ -c main.cpp
	
leer_archivo.o: 
	g++ -c -Iinclude src/leer_archivo.cpp

vehiculos.o:
	g++ -c -Iinclude src/vehiculos.cpp

grafo.o:
	g++ -c -Iinclude src/grafo.cpp

run: 
	./TTRP
clean:
	rm -f TTRP *.o
