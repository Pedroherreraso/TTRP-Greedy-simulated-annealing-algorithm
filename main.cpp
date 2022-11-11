#include <iostream>
#include "include/leer_archivo.h"
#include <vector>
#include <sstream>
using namespace std;
int main(int argc, char *argv[]){
    int iteraciones = atoi(argv[2]);
    std::vector<std::vector<int> > param;
    int camiones, traileres, clientes;
    double capacidad_camiones, capacidad_traileres;
    camiones = 0;
    capacidad_camiones = 0.0;
    traileres = 0;
    capacidad_traileres = 0.0;
    clientes = 0;
    leer_archivo(argv[1],param,camiones,capacidad_camiones, traileres, capacidad_traileres, clientes);
    return 0;
}