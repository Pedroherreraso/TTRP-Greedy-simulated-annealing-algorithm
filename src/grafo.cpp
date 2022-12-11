#include <iostream>
#include <vector>
#include <string>
#include <cmath> // sqrt, pow
#include <iomanip> // std::setprecision
#include "include/grafo.h"
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
					if (trailer_idx < numero_traileres){// me aseguro que se encargue de primero asignar las rutas de traileres
						if(traileres[trailer_idx].posicion_actual == 0){
							if (clientes[node_idx].tipo_cliente == 0){
								if(traileres[trailer_idx].capacidad_trailer_ok(clientes[node_idx])){
									double tmp_distance = distancia_matriz[traileres[trailer_idx].posicion_actual][node_idx];
									if(tmp_distance < min_distance){
										min_distance = tmp_distance;
										is_return_depot = false;
										best_node_idx = node_idx;
									}
								}
							}
						}else{
							if(identificador_subtour == 0){
								if(clientes[node_idx].tipo_cliente == 0){// verifico si es un cliente que el trailer puede atender
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
						}
					}else{//En caso de que no queden traileres asigno los camiones restantes
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
			if (trailer_idx < numero_traileres){
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
							}
						}
					}else{
						if(!is_return_depot){
							camiones[car_idx].anadir_cliente(&clientes[best_node_idx],distancia_matriz,1);
							identificador_subtour = 1;
						}else{
							camiones[car_idx].anadir_cliente(&clientes[traileres[trailer_idx].posicion_actual],distancia_matriz,0);
							identificador_subtour = 0;
							if (quedan() == true){
								if (le_cabe_uno_mas(traileres[trailer_idx]) == false ){
									if (traileres[trailer_idx].posicion_actual != 0){
										traileres[trailer_idx].anadir_cliente_trailer(&clientes[0],distancia_matriz,camiones[car_idx]);
										camiones[car_idx].anadir_cliente(&clientes[0],distancia_matriz,1);
									}car_idx +=1;
									trailer_idx +=1;
								}
							}else{
								traileres[trailer_idx].anadir_cliente_trailer(&clientes[0],distancia_matriz,camiones[car_idx]);
								camiones[car_idx].anadir_cliente(&clientes[0],distancia_matriz,1);
								car_idx +=1;
								trailer_idx +=1;
							}
						}
					}
				}else{
						if(!is_return_depot){
							camiones[car_idx].anadir_cliente(&clientes[best_node_idx],distancia_matriz,1);
						}else{
							camiones[car_idx].anadir_cliente(&clientes[traileres[trailer_idx].posicion_actual],distancia_matriz,0);
							identificador_subtour = 0;
						}
				}
			}else{
				if(camiones[car_idx].tour.empty()){
					camiones[car_idx].anadir_cliente(&clientes[0], distancia_matriz,1);// nodes[0] is depot
				}
				if(!is_return_depot){
					camiones[car_idx].anadir_cliente(&clientes[best_node_idx],distancia_matriz,1);
				}else{
					if (car_idx + 1 < numero_camion){
						if (camiones[car_idx].id_posicion != 0){
							camiones[car_idx].anadir_cliente(&clientes[0],distancia_matriz,1);
						}
						car_idx += 1;
					}else{
						break;
					}
				}
			}
		}
		if (camiones[car_idx].id_posicion != 0){camiones[car_idx].anadir_cliente(&clientes[0],distancia_matriz,1);}
		

}
//algoritmo que se encarga de calcular la distancia total del tour(es la funcion evaluacion)
void Grafo::calculo_distancia_tour(std::vector<Cliente>tour, double &tour_distance) const
{
	if(tour.size() > 2){
		for(double j = 0; j < tour.size() - 1; j++){
			tour_distance += distancia_matriz[tour[j].id][tour[j+1].id];
		}
	}
}
//muestra los vehiculos utilizados y por que nodo pasaron
void Grafo::show_each_car_tour() const
{
	double total_tour_distance = 0.0;
	for(int i = 0; i < numero_camion; i++){
		if(camiones[i].tour.size() > 1){
			std::cout << "vehicle " << " tour: ";
			double tour_distance = 0.0;
			for(double j = 0; j < camiones[i].tour.size(); j++){
				std::cout << camiones[i].tour[j].id << " ";
			}
			calculo_distancia_tour(camiones[i].tour, tour_distance);
			total_tour_distance += tour_distance;
			std::cout << " " << std::fixed << std::setprecision(1) << tour_distance << "km\n";
		}
		else{
			
		}
	}
	double total_tour_distance_trailer = 0.0;
		for(int i = 0; i < numero_traileres; i++){
		if(traileres[i].tour_trailer.size() > 1){
			std::cout << "trailer " << " tour: ";
			double tour_distance_trailer = 0.0;
			for(double j = 0; j < traileres[i].tour_trailer.size(); j++){
				std::cout << traileres[i].tour_trailer[j].id << " ";
			}
			calculo_distancia_tour(traileres[i].tour_trailer, tour_distance_trailer);
			total_tour_distance_trailer += tour_distance_trailer;
			std::cout << " " << std::fixed << std::setprecision(1) << tour_distance_trailer << "km\n";
		}
		else{
			
		}
}
	std::cout << "Costo/Distancia total de viaje:" << total_tour_distance + total_tour_distance_trailer << "km \n" << std::endl;
	for(int n;n <= numero_cliente;n++){
		if (clientes[n].visitado == false){
			std::cout << clientes[n].id;
		}
	}
}
//funcion que sigue con los camiones que no fueron utilizados para responder a los clientes que quedaron
void Grafo::calcular_distancias_totales(double &distancia_total)
{
	for(int i = 0; i < numero_camion; i++){
		if(camiones[i].tour.size() > 1){
			double tour_distance = 0.0;
			for(double j = 0; j < camiones[i].tour.size(); j++){
			}
			calculo_distancia_tour(camiones[i].tour, tour_distance);
			distancia_total += tour_distance;
		}
	}
			for(int i = 0; i < numero_traileres; i++){
			if(traileres[i].tour_trailer.size() > 1){
				double tour_distance_trailer = 0.0;
				for(double j = 0; j < traileres[i].tour_trailer.size(); j++){
				}
				calculo_distancia_tour(traileres[i].tour_trailer, tour_distance_trailer);
				distancia_total += tour_distance_trailer;
			}
		}	
}
// se encarga de revisar si le de los nodos disponibles para el trailer alguno cumple con la restriccion de carga
bool Grafo::le_cabe_uno_mas(Trailer a)
{
	bool valor = false;
	for(int i; i < numero_cliente; i++){
		if (clientes[i].tipo_cliente == 0){
			if(a.cargar_actual_trailer + clientes[i].demanda < a.capacidad_trailer ){
				valor = true;
			}
		}
	}
	return valor;
}
// revisa si es que quedan clientes disponibles para ruta de trailer
bool Grafo::quedan(){
	for(int i; i < numero_cliente; i++){
		if (clientes[i].tipo_cliente == 0 && clientes[i].visitado == false){
			return true;
		}
	}
	return false;
}
// algoritmo simulated annealing
void Grafo::sa(int iteraciones_maximas, int temperatura_maxima, int &valor,int &iteraciones_programa){
	std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0, 1);
	int iteraciones_sa = 0;
	int cantidad_de_iteraciones_para_bajar = 1 + rand()%(20 - 1);
	int iteraciones_ultima_bajada = 0;
	int bajada = 1 + rand()%(50 - 1);
	double distancia_greedy,distancia_sa,distancia_cambiante;
	calcular_distancias_totales(distancia_greedy);
	calcular_distancias_totales(distancia_sa);
	Cliente almacenador;
	while (iteraciones_sa < iteraciones_maximas){
		if (cantidad_de_iteraciones_para_bajar = iteraciones_ultima_bajada){
			temperatura_maxima = temperatura_maxima - bajada;
			if (temperatura_maxima <= 0){
				break;
			}
			iteraciones_ultima_bajada = 0;
		}
		if (distr(eng) > 0.5){
			int camion1 = rand()%numero_camion;
			int camion2 = rand()%numero_camion;
			int b = camiones[camion1].tour.size();
			int c = camiones[camion2].tour.size();
			if (camiones[camion1].tour.size() > 3 && camiones[camion2].tour.size()>3){
				int cliente1 = 1 + rand()%(b - 1);
				int cliente2 = 1 + rand()%(c - 1);
				if (cliente1 != 0 && cliente2 != 0){
					almacenador = camiones[camion1].tour[cliente1];
					camiones[camion1].tour[cliente1] = camiones[camion2].tour[cliente2];
					camiones[camion2].tour[cliente2] = almacenador;
					calcular_distancias_totales(distancia_cambiante);
					if (distancia_cambiante < distancia_sa){
						distancia_sa = distancia_cambiante;
						iteraciones_sa+=1;
					}else{
						if(exp(-((distancia_cambiante - distancia_sa)/temperatura_maxima)) < distr(eng)){
							almacenador = camiones[camion1].tour[cliente1];
							camiones[camion1].tour[cliente1] = camiones[camion2].tour[cliente2];
							camiones[camion2].tour[cliente2] = almacenador;
							iteraciones_sa +=1;
						}else{							
							iteraciones_ultima_bajada += 1;
							iteraciones_sa +=1;
						}
					}
				}
			}
		}else{
			int trailer1 = rand()%numero_traileres;
			int trailer2 = rand()%numero_traileres;
			int b = traileres[trailer1].tour_trailer.size();
			int c = traileres[trailer2].tour_trailer.size();
			if (traileres[trailer1].tour_trailer.size() > 3 && traileres[trailer2].tour_trailer.size() > 3){
				int cliente1 = 1 + rand()%(b-1);
				int cliente2 = 1 + rand()%(c-1);
				if(cliente1 != 0 && cliente2 != 0){
					almacenador = traileres[trailer1].tour_trailer[cliente1];
					traileres[trailer1].tour_trailer[cliente1] = traileres[trailer2].tour_trailer[cliente2];
					traileres[trailer2].tour_trailer[cliente2] = almacenador;
					calcular_distancias_totales(distancia_cambiante);
					if(distancia_cambiante < distancia_sa){
						iteraciones_sa +=1;
						iteraciones_ultima_bajada +=1;
					}
					else{
						if(exp(-((distancia_cambiante - distancia_sa)/temperatura_maxima)) < distr(eng)){
							almacenador = traileres[trailer1].tour_trailer[cliente1];
							traileres[trailer1].tour_trailer[cliente1] = traileres[trailer2].tour_trailer[cliente2];
							traileres[trailer2].tour_trailer[cliente2] = almacenador;
							iteraciones_sa +=1;
						}else{							
							iteraciones_ultima_bajada += 1;
							iteraciones_sa +=1;
						}
					}
				}
			}
		}
	}
	if (distancia_sa < distancia_greedy){
		valor = 1;
	}
	iteraciones_programa += iteraciones_sa;
}
	
