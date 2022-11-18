#include <iostream>
#include "vehiculos.h"

void Camion::anadir_cliente(Cliente *a, double** matriz)
{
	tour.push_back(*a);
	carga_actual += a->demanda;
	id_posicion = a->id;
	a->visitado= true;
}

bool Camion::capacidad_ok(Cliente a) const
{
	if(carga_actual + a.demanda <= capacidad_camion){
		return true;
	}
	else{
		return false;
	}
}