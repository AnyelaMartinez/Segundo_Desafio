#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>

huesped::huesped(){
    cout<<"instancias"<<endl;
}

bool huesped::loginH(const string& username, const string& pass){
    string user, passw;
    ifstream fin("sudoH.txt");
    if (!fin.is_open()) {
        cout << "Falla abriendo archivo sudoH.txt" << endl;
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


void huesped::reservarAlojamiento(){};
void huesped::anularReserva(){};
void huesped::cargaUpdateDataH(){};

huesped::~huesped() {
    // Destructor
}

