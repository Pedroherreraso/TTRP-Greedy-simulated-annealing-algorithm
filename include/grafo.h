#include <vector>
#include <unordered_map>
#include "vehiculos.h"
#ifndef GRAFO_H
#define GRAFO_H

class Grafo{
public:
    int camiones, clientes;
    Camion* camion;
    Nodo* clientes;
    double** matrix_distancia;
    void calculo_distancia_nodo();
    void calculo_distancia_tour(std::vector<Nodo>, double&)const;
    Grafo(std::vector<std::vector<int> >,int,int);
    virtual ~Grafo();
    void muestra_matrix_distancia();
    bool todos_son_visitados() const;
    void run_AlgoritmoGreedy();
    void mostrar_cada_tour_camion() const;
    void mostrar_informacion_nodo() const;
};
#endif