#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>

alojamiento::alojamiento(){
    cout<<"instancias"<<endl;
}

void alojamiento::cargaUpdateDataAj(){
    string campo;
    ifstream fin("alojamientos.txt", ios::out | ios::app);
    if (!fin.is_open()) {
        cout << "Falla abriendo archivo alojamientos.txt" << endl;
    }
    while (getline(fin, campo, '|')) {
        size_t nombre = campo.find('|');
        size_t idAlojamiento = campo.find('|');
        size_t anfitrion = campo.find('|');
        size_t departamento = campo.find('|');
        size_t minucipio = campo.find('|');
        size_t tipoAlojamiento = campo.find('|');
        size_t direccion = campo.find('|');
        size_t precioNoche = campo.find('|');
        size_t amenidades = campo.find('|');
        size_t fechaReserva = campo.find('|');
    }
    fin.close();
};

void alojamiento::aljDisponible(){
    //Tomar la fecha y comparar en el archivo de alojamientos con el ID si el alojamiento esta disponibles

}
