#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>

anfitrion::anfitrion(){
    cout<<"instancias"<<endl;
    anularReserva();
    consultarReserva();
    updateHistorial();
}

void anfitrion::cargaUpdateData(const string& nomArchivoE){

    ifstream fin(nomArchivoE, ios::out | ios::app);

    if (!fin.is_open()) {
        cout << "Falla abriendo archivo." << endl;
    }

    //cargando información

}

bool anfitrion::loginA(const string& username, const string& pass){
    string user, passw;
    ifstream fin("sudo.txt");
    if (!fin.is_open()) {
        cout << "Falla abriendo archivo sudo.txt" << endl;
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

