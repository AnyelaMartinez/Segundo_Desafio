#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>

alojamiento::alojamiento(){
    cout<<"instancias"<<endl;
}

void alojamiento::cargaUpdateDataAj() {
    ifstream fin("alojamientos.txt");
    if (!fin.is_open()) {
        cout << "Error abriendo el archivo alojamientos.txt" << endl;
        return;
    }

    getline(fin, nombre, '|');
    string id;
    getline(fin, id, '|');
    idAlojamiento = stoi(id);

    getline(fin, anfitrion, '|');
    getline(fin, departamento, '|');
    getline(fin, municipio, '|');
    getline(fin, tipoAlojamiento, '|');
    getline(fin, direccion, '|');

    string precio;
    getline(fin, precio, '|');
    precioNoche = stol(precio);

    getline(fin, amenidades, '|');
    getline(fin, fechaReserva);

    fin.close();
}


void alojamiento::aljDisponible(){

}
