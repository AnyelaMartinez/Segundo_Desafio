#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>
#include <cstring>

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

void anfitrion::anularReserva() {
    ifstream fin("reservas.txt");
    ofstream fout("temp.txt");

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Error abriendo archivos para anular reserva" << endl;
        return;
    }

    string linea;
    string idBuscar;
    cout << "Ingrese el ID de la reserva que desea anular: ";
    cin >> idBuscar;

    bool encontrada = false;
    while (getline(fin, linea)) {
        if (linea.find("|" + idBuscar + "|") == string::npos) {
            fout << linea << endl;
        } else {
            encontrada = true;
        }
    }

    fin.close();
    fout.close();

    remove("reservas.txt");
    rename("temp.txt", "reservas.txt");

    if (encontrada)
        cout << "Reserva anulada correctamente." << endl;
    else
        cout << "No se encontró una reserva con ese ID." << endl;
}

void anfitrion::consultarReserva() {
    ifstream fin("reservas.txt");
    if (!fin.is_open()) {
        cout << "Error abriendo reservas.txt" << endl;
        return;
    }

    string desdeStr, hastaStr;
    cout << "Ingrese fecha inicial (YYYY-MM-DD): ";
    cin >> desdeStr;
    cout << "Ingrese fecha final (YYYY-MM-DD): ";
    cin >> hastaStr;

    fecha desde, hasta;
    desde.leerDesdeCadena(desdeStr.c_str());
    hasta.leerDesdeCadena(hastaStr.c_str());

    string linea;
    while (getline(fin, linea)) {
        char buffer[1024];
        strcpy(buffer, linea.c_str());

        char* fechaEntradaStr = strtok(buffer, "|");
        char* nochesStr = strtok(nullptr, "|");
        char* idReservaStr = strtok(nullptr, "|");
        char* idAlojamientoStr = strtok(nullptr, "|");

        if (atoi(idAlojamientoStr) != idAlojamiento) continue;

        fecha entrada;
        entrada.leerDesdeCadena(fechaEntradaStr);
        if (entrada.esMenor(desde) || hasta.esMenor(entrada)) continue;

        cout << "Reserva encontrada -> " << linea << endl;
    }

    fin.close();
}

void anfitrion::updateHistorial() {
    string hoyStr;
    cout << "Ingrese la fecha actual (YYYY-MM-DD): ";
    cin >> hoyStr;

    fecha hoy;
    hoy.leerDesdeCadena(hoyStr.c_str());

    ifstream fin("reservas.txt");
    ofstream foutAct("temp.txt");
    ofstream foutHist("reservas_historicas.txt", ios::app);

    if (!fin.is_open() || !foutAct.is_open() || !foutHist.is_open()) {
        cout << "Error abriendo archivos para actualizar histórico" << endl;
        return;
    }

    string linea;
    while (getline(fin, linea)) {
        char buffer[1024];
        strcpy(buffer, linea.c_str());

        char* fechaEntradaStr = strtok(buffer, "|");
        fecha entrada;
        entrada.leerDesdeCadena(fechaEntradaStr);

        if (entrada.esMenor(hoy)) {
            foutHist << linea << endl;
        } else {
            foutAct << linea << endl;
        }
    }

    fin.close();
    foutAct.close();
    foutHist.close();

    remove("reservas.txt");
    rename("temp.txt", "reservas.txt");

    cout << "Histórico actualizado correctamente." << endl;
}


anfitrion::~anfitrion() {
    // Destructor
}

