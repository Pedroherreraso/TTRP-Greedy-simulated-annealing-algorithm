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
	int posicion_actual;
	double capacidad_trailer,cargar_actual_trailer;
	std::vector <Cliente> tour; 
	void anadir_cliente_trailer(Cliente*,double**);
	bool capacidad_ok(Cliente) const;
};
#endif