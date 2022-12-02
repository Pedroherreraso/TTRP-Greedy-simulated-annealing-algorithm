#include "Sa.h"
#include <random>

void simulated_annealing(Camion camion,int iteraciones,double temperatura){
    int iteraciones_algoritmo = 0;
    while( iteraciones_algoritmo <= iteraciones){
        iteraciones += 1;
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<float> distr(0, 1);
        //si es mejor se toma la nueva solucion mejor
        if(){
          
        }else{
            if(eng < exp(/temperatura)){}
        }

    } 

}