#include <iostream>
#include "include/grafo.h"
#include "include/leer_archivo.h"
#include <vector>
#include <sstream>
using namespace std;
int main(int argc, char *argv[]){
    int iteraciones = atoi(argv[2]);
    int temperatura = atoi(argv[3]);
    std::vector<std::vector<int> > param;
    int camiones, traileres, clientes;
    double capacidad_camiones, capacidad_traileres;
    camiones = 0;
    capacidad_camiones = 0.0;
    traileres = 0;
    capacidad_traileres = 0.0;
    leer_archivo(argv[1],param,camiones,capacidad_camiones, traileres, capacidad_traileres, clientes);
   	Grafo* grafo = new Grafo(param, capacidad_camiones, camiones,capacidad_traileres,traileres);
	grafo->GreedyAlgorithm();
	grafo->show_each_car_tour();
	//grafo->show_node_info();
	//grafo->mostrar_distancias();
	delete grafo;
	grafo = nullptr;
    return 0;
}