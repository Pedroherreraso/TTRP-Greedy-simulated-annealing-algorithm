#include <vector>
#ifndef VEHICULOS
#define VEHICULOS
class Cliente{
public:
	double x, y, demanda;
	int id;
	bool visitado;
    int tipo_cliente;
};

class Camion{
public:
	int id_posicion;
    double capacidad_camion,carga_actual;
	std::vector <Cliente> tour; 
	void anadir_cliente(Cliente*, double**);
	bool capacidad_ok(Cliente) const;
};

class Trailer{
public:
	int id_posicion;
	double capacidad_trailer,carga_actual;
	std::vector <Cliente> tour;
	void anadir_cliente(Cliente*, double**);
	 
};
#endif