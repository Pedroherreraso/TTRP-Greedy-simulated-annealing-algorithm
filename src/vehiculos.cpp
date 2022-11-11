#include <iostream>
#include "vehiculos.h"

void Camion::add_node(Nodo *a, double** matrix){
    tour.push_back(*a);
    carga_actual += a -> demanda;
    cliente_actual = a -> id;
    a -> visited = true;
}

bool Camion::ok_capacity(Nodo a) const{
    if (carga_actual + a.demanda <= capacidad_camion){
        return true;
    }
    else{
        return false;
    }
}