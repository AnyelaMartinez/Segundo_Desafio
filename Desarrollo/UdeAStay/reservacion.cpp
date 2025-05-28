#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>

reservacion::reservacion(){
    cout<<"instancias reserva"<<endl;
}

void reservacion::cargaUpdateDataR() {
    ifstream fin("reservas.txt");
    if (!fin.is_open()) {
        cout << "Error al abrir reservas.txt" << endl;
        return;
    }

    string linea;
    while (getline(fin, linea)) {
        cout << "Reserva: " << linea << endl;
    }

    fin.close();
}
