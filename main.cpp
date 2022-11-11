#include <iostream>
#include "include/leer_archivo.h"
#include <vector>
#include <sstream>
using namespace std;
int main(int argc, char *argv[]){
    leer_archivo(argv[1]);
    int iteraciones = atoi(argv[2]);
    return 0;
}