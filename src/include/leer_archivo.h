#ifndef LEER_ARCHIVO
#define LEER_ARCHIVO
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
void leer_archivo (const char *archivo,std::vector<std::vector<int> >&param,int &camiones,double &capacidad_camiones,int &traileres, double &capacidad_traileres, int &clientes);
#endif