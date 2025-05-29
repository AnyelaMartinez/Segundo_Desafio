#include "UdeAStayhead.h"
#include "globales.h"
#include <iostream>
#include <fstream>

reservacion::reservacion() {}
void reservacion::cargaUpdateDataR() {
    std::ifstream fin("reservas.txt");
    if (!fin.is_open()) {
        std::cout << "Error al abrir reservas.txt\n";
        return;
    }
    string linea;
    while (getline(fin, linea)) {
        contador_iteraciones++;
        std::cout << "Reserva: " << linea << std::endl;
    }
    fin.close();
    std::cout << "Iteraciones: " << contador_iteraciones << "\n";
}
reservacion::~reservacion() {}
