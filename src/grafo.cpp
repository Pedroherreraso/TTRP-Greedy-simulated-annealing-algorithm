#include <iostream>
#include <vector>
#include <string>
#include <cmath> // sqrt, pow
#include <iomanip> // std::setprecision
#include "grafo.h"
#include <cstdlib>
#include <random>
// se calcula la distancia entre los nodos(clientes)
void Grafo::calculo_distancia_nodos()
{
	for(int i = 0; i < numero_cliente; i++){
		for(int j = i + 1; j < numero_cliente; j++){
			distancia_matriz[i][j] = distancia_matriz[j][i] = sqrt(pow(clientes[i].x - clientes[j].x, 2) + pow(clientes[i].y - clientes[j].y, 2));

		}
}
}
//se rellenan las estructuras principales del grafo
Grafo::Grafo(std::vector<std::vector<int> > param,
				double car_capacity, int num_car,double trailer_capacity,int num_traileres)
{
	this->numero_camion = num_car;
	this->numero_traileres = num_traileres;
	this->numero_cliente = param.size(); 

	clientes = new Cliente[numero_cliente];
	camiones = new Camion[num_car];
	traileres = new Trailer[num_traileres];

	for(int i = 0; i < numero_cliente; i++){
		clientes[i].id = param[i][0]; 
		clientes[i].x = param[i][1];
		clientes[i].y = param[i][2];
		clientes[i].demanda = param[i][3];
		clientes[i].tipo_cliente = param[i][4];
		clientes[i].visitado = false;
	}

	for(int i = 0; i < num_car; i++){
		camiones[i].capacidad_camion = car_capacity;
		camiones[i].carga_actual = 0;
		camiones[i].id_posicion = 0;
	}

	for(int i = 0; i < num_traileres; i++){
		traileres[i].capacidad_trailer = trailer_capacity;
		traileres[i].cargar_actual_trailer = 0;
		traileres[i].posicion_actual = 0;
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
// se libera la memoria
Grafo::~Grafo()
{ 
	std::cout << "destructor!" << std::endl;
	delete[] clientes;
	clientes = nullptr;
	delete[] camiones;
	camiones = nullptr;
	delete[] traileres;
	traileres = nullptr;
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
// Algoritmo greedy de camiones con traileres(se denomina camiones al camion(solitario) mientras que se denomina trailer al camion acompañado de un trailer)
void Grafo::GreedyAlgorithm(int &iteraciones)
{
		int trailer_idx = 0;
		int car_idx = 0;
		int identificador_subtour = 0;
		int identificador_ruta_camion = 0;
		//si todos estan visitados
		while(!is_all_visited()){
			iteraciones +=1;
			int best_node_idx;
			double min_distance = 100000;
			bool is_return_depot = true;
			
			if(traileres[trailer_idx].tour_trailer.empty()){
					traileres[trailer_idx].anadir_cliente_trailer(&clientes[0], distancia_matriz,camiones[car_idx]);// nodes[0] is depot
					camiones[car_idx].anadir_cliente(&clientes[0], distancia_matriz,1);
			}
		// reviso el nodo mas cercano y los escojo
			for(int node_idx = 1; node_idx < numero_cliente; node_idx++){
				if(!clientes[node_idx].visitado){
					if (identificador_ruta_camion == 0){
						if(identificador_subtour == 0){
							if(clientes[node_idx].tipo_cliente == 0){
								if(traileres[trailer_idx].capacidad_trailer_ok(clientes[node_idx])){
									double tmp_distance = distancia_matriz[traileres[trailer_idx].posicion_actual][node_idx];
									if(tmp_distance < min_distance){
										min_distance = tmp_distance;
										is_return_depot = false;
										best_node_idx = node_idx;
									}
								}
							}else{
								if (camiones[car_idx].capacidad_ok(clientes[node_idx])){
									double tmp_distance = distancia_matriz[camiones[car_idx].id_posicion][node_idx];
									if(tmp_distance < min_distance){
										min_distance = tmp_distance;
										is_return_depot = false;
										best_node_idx = node_idx;
									}
								}
							}
						}else{
							if (camiones[car_idx].capacidad_ok(clientes[node_idx])){
								double tmp_distance = distancia_matriz[camiones[car_idx].id_posicion][node_idx];
								if(tmp_distance < min_distance){
									min_distance = tmp_distance;
									is_return_depot = false;
									best_node_idx = node_idx;
								}
							}
						}
					}else{
						if (camiones[car_idx].capacidad_ok(clientes[node_idx])){
							double tmp_distance = distancia_matriz[camiones[car_idx].id_posicion][node_idx];
							if(tmp_distance < min_distance){
								min_distance = tmp_distance;
								is_return_depot = false;
								best_node_idx = node_idx;
							}
						}
					}
				}
			}

			if (identificador_ruta_camion == 0){
				if (identificador_subtour == 0){
					if (clientes[best_node_idx].tipo_cliente == 0){
						if(!is_return_depot){
							traileres[trailer_idx].anadir_cliente_trailer(&clientes[best_node_idx],distancia_matriz,camiones[car_idx]);							
						}else{
							if (trailer_idx < numero_traileres){
								if (traileres[trailer_idx].posicion_actual != 0){
									traileres[trailer_idx].anadir_cliente_trailer(&clientes[0],distancia_matriz,camiones[car_idx]);
									camiones[car_idx].anadir_cliente(&clientes[0],distancia_matriz,1);
								}
								car_idx +=1;
								trailer_idx +=1;
							}else{
								identificador_ruta_camion = 1;
							}
						}
					}else{
						camiones[car_idx].anadir_cliente(&clientes[best_node_idx], distancia_matriz, 1);
						if(traileres[trailer_idx].posicion_actual == 0){
							identificador_ruta_camion = 1;
						}
						else{
							identificador_subtour = 1;
						}
					}
				}else{
					if(distancia_matriz[traileres[trailer_idx].posicion_actual][camiones[car_idx].id_posicion] > distancia_matriz[camiones[car_idx].id_posicion][best_node_idx]){
						if(!is_return_depot){
							camiones[car_idx].anadir_cliente(&clientes[best_node_idx],distancia_matriz,1);
						}else{
							camiones[car_idx].anadir_cliente(&clientes[traileres[trailer_idx].posicion_actual],distancia_matriz,0);
							identificador_subtour = 0;
						}
					}
					else{
						camiones[car_idx].anadir_cliente(&clientes[traileres[trailer_idx].posicion_actual],distancia_matriz,0);
						if (trailer_idx < numero_traileres){
							identificador_subtour = 0;
						}
					}
				}
			}else{
				if(!is_return_depot){
					camiones[car_idx].anadir_cliente(&clientes[best_node_idx],distancia_matriz,1);
				}else{
					if (car_idx < numero_camion){
						if (camiones[car_idx].id_posicion != 0){
							camiones[car_idx].anadir_cliente(&clientes[0],distancia_matriz,1);
						}
						identificador_ruta_camion = 0;
						car_idx += 1;
					}
					else{
						break;
					}
				}
			}
	}
}
//algoritmo que se encarga de calcular la distancia total del tour(es la funcion evaluacion)
void Grafo::calculo_distancia_tour(std::vector<Cliente>tour, double &tour_distance) const
{
	if(tour.size() > 2){
		for(int j = 0; j < tour.size() - 1; j++){
			tour_distance += distancia_matriz[tour[j].id][tour[j+1].id];
		}
	}
}
//muestra los vehiculos utilizados y por que nodo pasaron
void Grafo::show_each_car_tour() const
{
	double total_tour_distance = 0.0;
	int total_visited_customer = 0;
	for(int i = 0; i < numero_camion; i++){
		if(camiones[i].tour.size() > 1){
			std::cout << "vehicle " << i << " tour: ";
			double tour_distance = 0.0;
			for(int j = 0; j < camiones[i].tour.size(); j++){
				std::cout << camiones[i].tour[j].id << " ";
			}
			calculo_distancia_tour(camiones[i].tour, tour_distance);
			total_tour_distance += tour_distance;
			std::cout << " " << std::fixed << std::setprecision(1) << tour_distance << "km\n";
			total_visited_customer += camiones[i].tour.size()-2;
		}
		else{
			
		}
	}
	double total_tour_distance_trailer = 0.0;
	int total_visited_customer_trailer = 0;
		for(int i = 0; i < numero_traileres; i++){
		if(traileres[i].tour_trailer.size() > 1){
			std::cout << "trailer " << i << " tour: ";
			double tour_distance_trailer = 0.0;
			for(int j = 0; j < traileres[i].tour_trailer.size(); j++){
				std::cout << traileres[i].tour_trailer[j].id << " ";
			}
			calculo_distancia_tour(traileres[i].tour_trailer, tour_distance_trailer);
			total_tour_distance_trailer += tour_distance_trailer;
			std::cout << " " << std::fixed << std::setprecision(1) << tour_distance_trailer << "km\n";
			total_visited_customer_trailer+= traileres[i].tour_trailer.size()-2;
		}
		else{
			
		}
}
	std::cout << "total distance:" << total_tour_distance << "km \n" << std::endl;
	std::cout << "total distance trailer:" << total_tour_distance_trailer << "km\n" << std::endl;
	std::cout << "total visited customer:" << total_visited_customer << "/" << numero_cliente - 1 << std::endl;
}
//funcion que sigue con los camiones que no fueron utilizados para responder a los clientes que quedaron
void Grafo::greedyonlyvehicles(int car_idx,int iteraciones){
	int vehiculos = car_idx;
	int max_iteraciones = iteraciones;
	while(!is_all_visited()){
		max_iteraciones +=1;
		int best_node_idx;
		double min_distance = 100000;
		bool is_return_depot = true;
		
		if(camiones[vehiculos].tour.empty()){
			camiones[vehiculos].anadir_cliente(&clientes[0], distancia_matriz,1);// nodes[0] is depot
		}

		for(int node_idx = 1; node_idx < numero_cliente; node_idx++){
			if(!clientes[node_idx].visitado){
				if(camiones[vehiculos].capacidad_ok(clientes[node_idx])){
						double tmp_distance = distancia_matriz[camiones[vehiculos].id_posicion][node_idx];
						if(tmp_distance < min_distance){
							min_distance = tmp_distance;
							is_return_depot = false;
							best_node_idx = node_idx;
						}
					}
				}
			}

		if(!is_return_depot){
			camiones[vehiculos].anadir_cliente(&clientes[best_node_idx], distancia_matriz,1);
		}
		else{// si no hay caminos regresa al deposito
			if(vehiculos + 1 < numero_camion){// Chequea si existen mas vehiculos
				if(camiones[vehiculos].id_posicion != 0){
					camiones[vehiculos].anadir_cliente(&clientes[0],distancia_matriz,1);
				}
				vehiculos += 1;
			}
			else{
				break;
			}
			
		}
	}//ciclo while termina
	if(camiones[vehiculos].id_posicion != 0){
				camiones[vehiculos].anadir_cliente(&clientes[0], distancia_matriz,1);
	}
	std::cout << " Iteraciones realizadas por el algoritmo greedy: "<< max_iteraciones;
}

void Grafo::calcular_distancias_totales(double &distancia_total,double &distancia_total_trailer) const
{
	int total_visited_customer = 0;
	for(int i = 0; i < numero_camion; i++){
		if(camiones[i].tour.size() > 1){
			double tour_distance = 0.0;
			for(int j = 0; j < camiones[i].tour.size(); j++){
			}
			calculo_distancia_tour(camiones[i].tour, tour_distance);
			distancia_total += tour_distance;
			total_visited_customer += camiones[i].tour.size()-2;
		}
	}
	int total_visited_customer_trailer = 0;
			for(int i = 0; i < numero_traileres; i++){
			if(traileres[i].tour_trailer.size() > 1){
				double tour_distance_trailer = 0.0;
				for(int j = 0; j < traileres[i].tour_trailer.size(); j++){
				}
				calculo_distancia_tour(traileres[i].tour_trailer, tour_distance_trailer);
				distancia_total_trailer += tour_distance_trailer;
				total_visited_customer_trailer+= traileres[i].tour_trailer.size()-2;
			}
		}	
}

// algoritmo simulated annealing
void Grafo::sa(int iteraciones, int temperatura, int &valor,int &iteraciones_programa){

}