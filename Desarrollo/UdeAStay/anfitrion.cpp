#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>

anfitrion::anfitrion(){
    cout<<"instancias"<<endl;
    anularReserva();
    consultarReserva();
    updateHistorial();
}


void anfitrion::cargaUpdateDataA(){

    string campo;
    ifstream fin("usuarios.txt", ios::out | ios::app);
    if (!fin.is_open()) {
        cout << "Falla abriendo archivo usuarios.txt" << endl;
    }
    /*while (getline(fin, campo, '|')) {
        size_t id_an = campo.find('|');
        size_t nombre = campo.find('|');
        size_t antiguedad = campo.find('|');
        size_t puntos = campo.find('|');
        size_t id_Aj = campo.find('|');
    }*/
    fin.close();

}

bool anfitrion::loginA(const string& username, const string& pass){
    string user, passw;
    ifstream fin("sudoA.txt");
    if (!fin.is_open()) {
        cout << "Falla abriendo archivo sudoA.txt" << endl;
        return false;
    }
    getline(fin, user);
    getline(fin, passw);
    fin.close();
    if (user != username || passw != pass) {
        return false;
    }
    return true;
}

void anfitrion::anularReserva(){}
void anfitrion::consultarReserva(){}
void anfitrion::updateHistorial(){}

anfitrion::~anfitrion() {
    // Destructor vacío (por ahora)
}

