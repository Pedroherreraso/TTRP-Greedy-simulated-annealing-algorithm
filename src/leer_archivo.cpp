#include "leer_archivo.h"
using namespace std;
void leer_archivo (string filename){
    ifstream archivo(filename.c_str());
    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
     for(int i = 0; i < 1; i++){
   	    getline(archivo, linea);
        cout << linea[3];
        // tomar los datos de la primera linea del archivo
        // falta separar los datos
        
   }
    while (getline(archivo, linea)) {
        // tomar los datos del resto del archivo
    }

}