#include <vector>
#include <unordered_map>
#include "vehiculos.h"
#ifndef GRAFO
#define GRAFO

class Grafo{
public:
	int numero_camion, numero_cliente,numero_traileres;
	Camion* camiones;
	Cliente* clientes;
	Trailer* traileres;
	double** distancia_matriz;
	void calculo_distancia_nodos();
	void calculo_distancia_tour(std::vector<Cliente>, double&) const;
	Grafo(std::vector<std::vector<int> >, double, int,double,int);
	virtual ~Grafo();
	void mostrar_distancias() const;
	bool is_all_visited() const;
	void GreedyAlgorithm();
	void greedyonlyvehicles(int car_idx,int iteraciones);
	void show_each_car_tour() const;
	void show_node_info() const;
};

#endif