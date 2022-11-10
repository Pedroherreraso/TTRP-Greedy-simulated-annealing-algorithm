#include "leer_archivo.h"

void leer_archivo (string filename){
    ifstream archivo(filename.c_str());
    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {
        // Lo vamos imprimiendo
        cout << "Una línea: ";
        cout << linea << endl;
    }
}