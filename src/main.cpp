#include <iostream>
#include "include/grafo.h"
#include "include/leer_archivo.h"
#include <vector>
#include <sstream>
using namespace std;
int main(int argc, char*argv[]){
    int iteraciones_maximas = atoi(argv[2]);
    int temperatura_maxima = atoi(argv[3]);
    std::vector<std::vector<int> > param;
    int camiones, traileres, clientes;
    double capacidad_camiones, capacidad_traileres;
    camiones = 0;
    capacidad_camiones = 0.0;
    traileres = 0;
    capacidad_traileres = 0.0;
    int valor,iteraciones_programa = 0;
    leer_archivo(argv[1],param,camiones,capacidad_camiones, traileres, capacidad_traileres, clientes);
   	Grafo* grafo = new Grafo(param, capacidad_camiones, camiones,capacidad_traileres,traileres);
	grafo->GreedyAlgorithm(iteraciones_programa);
    grafo -> sa(iteraciones_maximas,temperatura_maxima, valor, iteraciones_programa);
    if (valor == 1){
        delete grafo;
	    grafo = nullptr;
        int iteraciones_falsas = 0;
        grafo->GreedyAlgorithm(iteraciones_falsas);
    }
    grafo->show_each_car_tour();
    std::cout << "iteraciones realizadas "<<iteraciones_programa;
    delete grafo;
	grafo = nullptr;
    return 0;
}