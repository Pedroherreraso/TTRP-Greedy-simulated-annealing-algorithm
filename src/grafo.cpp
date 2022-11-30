#include <iostream>
#include <vector>
#include <string>
#include <cmath> // sqrt, pow
#include <iomanip> // std::setprecision
#include "grafo.h"
// se calcula la distancia entre los nodos(clientes)
void Grafo::calculo_distancia_nodos()
{
	for(int i = 0; i < numero_cliente; i++){
		for(int j = i + 1; j < numero_cliente; j++){
			distancia_matriz[i][j] = distancia_matriz[j][i] = sqrt(pow(clientes[i].x - clientes[j].x, 2) + pow(clientes[i].y - clientes[j].y, 2));

		}
}
}

Grafo::Grafo(std::vector<std::vector<int> > param,
				double car_capacity, int num_car)
{
	this->numero_camion = num_car;
	this->numero_cliente = param.size(); 

	std::cout << " numero camiones:" << num_car << " capacidad camiones:" \
		<< car_capacity << " numero_clientes(deposito + clientes):" << numero_cliente << std::endl;

	clientes = new Cliente[numero_cliente];
	camiones = new Camion[num_car];

	for(int i = 0; i < numero_cliente; i++){
		clientes[i].id = param[i][0]; 
		clientes[i].x = param[i][1];
		clientes[i].y = param[i][2];
		clientes[i].demanda = param[i][3];
		clientes[i].visitado = false;
	}

	for(int i = 0; i < num_car; i++){
		camiones[i].capacidad_camion = car_capacity;
		camiones[i].carga_actual = 0;
		camiones[i].id_posicion = 0;
	}

	distancia_matriz= new double* [numero_cliente]; 
	for(int i = 0; i < numero_cliente; i++){
		distancia_matriz[i] = new double [numero_cliente];
		for(int j = 0; j < numero_cliente; j++){
			distancia_matriz[i][j] = 0;// inicialización de todos los elementos en una fila
		}
	}
	calculo_distancia_nodos();
}

Grafo::~Grafo()
{ 
	std::cout << "destructor!" << std::endl;
	delete[] clientes;
	clientes = nullptr;
	delete[] camiones;
	camiones = nullptr;
	for(int i = 0; i < numero_cliente ;i++){
		delete[] distancia_matriz[i];
		distancia_matriz[i] = nullptr;
	}
	delete[] distancia_matriz;
	distancia_matriz = nullptr;
}
// funcion que se encarga de mostrar la matriz de distancias
void Grafo::mostrar_distancias() const
{
	std::cout << numero_cliente << "*" << numero_cliente << " distance matrix." << std::endl;
	for(int i = 0; i < numero_cliente; i++){
		for(int j = 0; j < numero_cliente; j++){
			std::cout << std::fixed << std::setprecision(1) << distancia_matriz[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
// Funcion que se encarga de revisar si todos los clientes fueron visitados
bool Grafo::is_all_visited() const
{
	for(int i = 1; i < numero_cliente; i++){
		if(!clientes[i].visitado){
			return false;
		}
	}
	return true;
}
// por ahora solo funciona con camiones ignora los trailers
void Grafo::GreedyAlgorithm()
{
		int car_idx = 0;
	while(!is_all_visited()){
		int best_node_idx;
		double min_distance = 100000;
		bool is_return_depot = true;
		
		if(camiones[car_idx].tour.empty()){
			camiones[car_idx].anadir_cliente(&clientes[0], distancia_matriz);// nodes[0] is depot
		}

		for(int node_idx = 1; node_idx < numero_cliente; node_idx++){
			if(!clientes[node_idx].visitado){
				if(camiones[car_idx].capacidad_ok(clientes[node_idx])){
						double tmp_distance =distancia_matriz[camiones[car_idx].id_posicion][node_idx];
						if(tmp_distance < min_distance){
							min_distance = tmp_distance;
							is_return_depot = false;
							best_node_idx = node_idx;
					}
				}
			}
		}

		if(!is_return_depot){
			camiones[car_idx].anadir_cliente(&clientes[best_node_idx], distancia_matriz);
		}
		else{// if edges are not found, return depot
			if(car_idx + 1 < numero_camion){// check if the rest of vehicles exists
				if(camiones[car_idx].id_posicion != 0){// in case the vehicle did not return back to the depot
					camiones[car_idx].anadir_cliente(&clientes[0], distancia_matriz);
				}
				car_idx += 1;// assign next vehicle
			}
			else{
				std::cout << "Cannot solve this by Greedy algorithm." << std::endl;
				break;// std::exit(0);
			}
			
		}
	}//while loop done
	if(camiones[car_idx].id_posicion != 0){// in case the vehicle did not return back to the depot
				camiones[car_idx].anadir_cliente(&clientes[0], distancia_matriz);
	}
	std::cout << "algorithm done." << std::endl;
}
void Grafo::calculo_distancia_tour(std::vector<Cliente>tour, double &tour_distance) const
{
	if(tour.size() > 2){
		for(int j = 0; j < tour.size() - 1; j++){
			tour_distance += distancia_matriz[tour[j].id][tour[j+1].id];
		}
	}
}

void Grafo::show_each_car_tour() const
{
	double total_tour_distance = 0.0;
	int total_visited_customer = 0;
	for(int i = 0; i < numero_camion; i++){
		if(camiones[i].tour.size() > 1){
			std::cout << "vehicle" << i << " tour: ";
			double tour_distance = 0.0;
			for(int j = 0; j < camiones[i].tour.size(); j++){
				std::cout << camiones[i].tour[j].id << " ";
			}
			calculo_distancia_tour(camiones[i].tour, tour_distance);
			total_tour_distance += tour_distance;
			std::cout << " " << std::fixed << std::setprecision(1) << tour_distance << "km";
			std::cout << ", visited customer:" << camiones[i].tour.size()-2;
			std::cout << ", now_load:" << camiones[i].carga_actual << "/" << camiones[i].capacidad_camion << std::endl;
			total_visited_customer += camiones[i].tour.size()-2;
		}
		else{
			std::cout << "vehicle" << i << ": not used" << std::endl;
		}
	}
	std::cout << "total visited customer:" << total_visited_customer << "/" << numero_cliente - 1 << std::endl;// -1 denotes not counting the depot
	std::cout << "total distance:" << total_tour_distance << "km" << std::endl;
}

void Grafo::show_node_info() const
{
	std::cout << std::endl << "idx,x,y,demand,tw_open,tw_close,unload_time" << std::endl;
	for(int i = 0; i < numero_cliente; i++){
		std::cout << clientes[i].id << " " << clientes[i].x << " " << clientes[i].y << " " << clientes[i].demanda << \
			" " << std::endl;
	}
}

