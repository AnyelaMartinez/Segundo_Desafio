#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>

huesped::huesped(){
    cout<<"instancias"<<endl;
}

bool huesped::loginH(const string& username, const string& pass){
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

