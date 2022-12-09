#include <iostream>
#include "include/vehiculos.h"

void Camion::anadir_cliente(Cliente *a, double** matriz, int c)
{
	if (c == 1){tour.push_back(*a);
		carga_actual += a->demanda;
		id_posicion = a->id;
		a->visitado= true;
	}else{
		id_posicion = a->id;
	}
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
void Trailer::anadir_cliente_trailer(Cliente *a, double** matriz, Camion b)
{
	tour_trailer.push_back(*a);
	cargar_actual_trailer += a->demanda;
	posicion_actual = a->id;
	a->visitado= true;
	b.anadir_cliente(a,matriz,0);
}
bool Trailer::capacidad_trailer_ok(Cliente a) const
{
	if(cargar_actual_trailer + a.demanda <= capacidad_trailer){
		return true;
	}
	else{
		return false;
	}
}