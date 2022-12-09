#include "include/leer_archivo.h"

void leer_archivo (const char *archivo,std::vector<std::vector<int> >&param,int &camiones,double &capacidad_camiones,int &traileres, double &capacidad_traileres, int &clientes){
    std::ifstream ifs(archivo, std::ios::in);
    std::string linea;
    std::getline(ifs, linea);
    std::stringstream ss(linea);
    ss >> camiones >> capacidad_camiones >> traileres >> capacidad_traileres >> clientes;
    while (std::getline(ifs,linea))
    {
        std::stringstream ss(linea);
	        std::vector<int> datos_cliente;
	        int tipo_cliente;
	        while (ss >> tipo_cliente){
	      	    datos_cliente.push_back(tipo_cliente);
	        }
	        param.push_back(datos_cliente);
	   }
ifs.close();

}
