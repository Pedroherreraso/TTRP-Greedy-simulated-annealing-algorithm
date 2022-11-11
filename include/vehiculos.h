#include <vector>
#ifndef VEHICULOS_H
#define VEHICULOS_H

class Nodo {
    public:
        double x,y,demanda;
        int id,tipo;
        bool visited;
};

class Camion {
    public:
        double capacidad_camion,carga_actual;
        int cliente_actual;
        std::vector <Nodo> tour;
        void add_node(Nodo*, double**);
        bool ok_capacity(Nodo) const; 
    
};

class Trailer {
    public: 
        double capacidad_trailer,carga_actual,id_actual;
        void add_node(Nodo*, double**);
        
        
};
#endif