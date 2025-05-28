#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>
#include <cstring>

anfitrion::anfitrion(){
    cout<<"instancias anitrion"<<endl;
}

bool anfitrion::loginA(const string& username, const string& pass){
    ifstream fin("usuariosA.txt");
    if (!fin.is_open()) {
        cout << "Error abriendo usuariosA.txt" << endl;
        return false;
    }

    string linea;
    while (getline(fin, linea)) {
        char buffer[256];
        strcpy(buffer, linea.c_str());

        char* idStr = strtok(buffer, "|");
        char* user = strtok(nullptr, "|");
        char* passw = strtok(nullptr, "|");
        char* ant = strtok(nullptr, "|");
        char* punt = strtok(nullptr, "|");

        if (user == username && passw == pass) {
            idAnfitrion = atoi(idStr);
            antiguedad = atoi(ant);
            puntuacion = atof(punt);
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}

void anfitrion::anularReserva() {
    ifstream fin("reservas.txt");
    ofstream fout("temp_r.txt");

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
    rename("temp_r.txt", "reservas.txt");

    if (encontrada)
        cout << "Reserva anulada correctamente." << endl;
    else
        cout << "No se encontro una reserva con ese ID." << endl;
}

void anfitrion::consultarReserva() {
    ifstream fin("reservas.txt");
    if (!fin.is_open()) {
        cout << "Error abriendo reservas.txt" << endl;
        return;
    }

    string fechaIni, fechaFin;
    cout << "Ingrese fecha inicial (YYYY-MM-DD): ";
    cin >> fechaIni;
    cout << "Ingrese fecha final (YYYY-MM-DD): ";
    cin >> fechaFin;

    fecha desde, hasta;
    desde.leerDesdeCadena(fechaIni.c_str());
    hasta.leerDesdeCadena(fechaFin.c_str());

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
    string fechaAct;
    cout << "Ingrese la fecha actual (YYYY-MM-DD): ";
    cin >> fechaAct;

    fecha hoy;
    hoy.leerDesdeCadena(fechaAct.c_str());

    ifstream fin("reservas.txt");
    ofstream foutAct("temp_r.txt");
    ofstream foutHist("Historico.txt", ios::app);

    if (!fin.is_open() || !foutAct.is_open() || !foutHist.is_open()) {
        cout << "Error abriendo archivos para actualizar historico" << endl;
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
    rename("temp_r.txt", "reservas.txt");

    cout << "Historico actualizado correctamente." << endl;
}

anfitrion::~anfitrion() {
    // Destructor
}

