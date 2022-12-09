#include <iostream>
#include "include/grafo.h"
#include "include/leer_archivo.h"
#include <vector>
#include <sstream>
#include <chrono>
using namespace std;
int main(int argc, char*argv[]){
    auto start = std::chrono::system_clock::now();
    int iteraciones_maximas = atoi(argv[2]);
    int temperatura_maxima = atoi(argv[3]);
    std::vector<std::vector<int> > param;
    int camiones, traileres, clientes;
    double capacidad_camiones, capacidad_traileres;
    camiones = 0;
    capacidad_camiones = 0.0;
    traileres = 0;
    capacidad_traileres = 0.0;
    int valor = 0;
    int iteraciones_programa = 0;
    leer_archivo(argv[1],param,camiones,capacidad_camiones, traileres, capacidad_traileres, clientes);
   	Grafo* grafo = new Grafo(param, capacidad_camiones, camiones,capacidad_traileres,traileres);
	grafo->GreedyAlgorithm(iteraciones_programa);
    grafo -> sa(iteraciones_maximas,temperatura_maxima, valor, iteraciones_programa);
    if (valor == 0){
        delete grafo;
	    grafo = nullptr;
	    Grafo* graf = new Grafo(param, capacidad_camiones, camiones,capacidad_traileres,traileres);
	    graf->GreedyAlgorithm(iteraciones_programa);
        graf->show_each_car_tour();
        delete graf;
	    graf = nullptr;
    }else{
        grafo->show_each_car_tour();
        delete grafo;
	    grafo = nullptr;
    }
    std::cout << "iteraciones realizadas "<<iteraciones_programa<<"\n";
    auto end = std::chrono::system_clock::now();
    
    std::chrono::duration<float,std::milli> duration = end - start;

    std::cout << duration.count()<< "ms";
    return 0;
}