#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>
#include <cstring>

alojamiento::alojamiento(){
    cout<<"instancias alojamiento"<<endl;
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


void alojamiento::aljDisponible() {
    string fechaBuscada;
    cout << "Ingrese la fecha de entrada para verificar disponibilidad (YYYY-MM-DD): ";
    cin >> fechaBuscada;

    ifstream fin("reservas.txt");
    if (!fin.is_open()) {
        cout << "No se pudo abrir reservas.txt" << endl;
        return;
    }

    string linea;
    bool disponible = true;

    while (getline(fin, linea)) {
        char buffer[512];
        strcpy(buffer, linea.c_str());

        char* fechaEntrada = strtok(buffer, "|");
        char* nochesStr = strtok(nullptr, "|");
        char* idReservaStr = strtok(nullptr, "|");
        char* idAlojStr = strtok(nullptr, "|");

        int idAj = atoi(idAlojStr);
        if (idAj == idAlojamiento && fechaBuscada == fechaEntrada) {
            disponible = false;
            break;
        }
    }

    fin.close();

    if (disponible)
        cout << "El alojamiento " << idAlojamiento << " está disponible en la fecha indicada." << endl;
    else
        cout << "El alojamiento " << idAlojamiento << " ya está reservado en esa fecha." << endl;
}

void alojamiento::mostrarAlojamientosDisponibles() {
    string municipioBuscado, fechaBuscada;
    cout << "Ingrese el municipio donde desea alojarse: ";
    cin >> municipioBuscado;
    cout << "Ingrese la fecha deseada (YYYY-MM-DD): ";
    cin >> fechaBuscada;

    ifstream alojFile("alojamientos.txt");
    ifstream reservasFile("reservas.txt");

    if (!alojFile.is_open() || !reservasFile.is_open()) {
        cout << "Error abriendo los archivos de datos" << endl;
        return;
    }

    string linea;
    while (getline(alojFile, linea)) {
        char buffer[512];
        strcpy(buffer, linea.c_str());

        char* nombre = strtok(buffer, "|");
        char* idAlojStr = strtok(nullptr, "|");
        strtok(nullptr, "|"); // anfitrion
        strtok(nullptr, "|"); // departamento
        char* municipio = strtok(nullptr, "|");

        if (municipioBuscado != municipio) continue;

        // verificar disponibilidad en reservas.txt
        bool ocupado = false;
        string rline;
        reservasFile.clear();
        reservasFile.seekg(0);

        while (getline(reservasFile, rline)) {
            char buf[512];
            strcpy(buf, rline.c_str());

            char* fechaRes = strtok(buf, "|");
            strtok(nullptr, "|");
            strtok(nullptr, "|");
            char* idA = strtok(nullptr, "|");

            if (fechaRes == fechaBuscada && idAlojStr == idA) {
                ocupado = true;
                break;
            }
        }

        if (!ocupado) {
            cout << "Disponible: " << linea << endl;
        }
    }

    alojFile.close();
    reservasFile.close();
}

void alojamiento::mostrarAlojamientosFiltrados(long int precioMax, double puntuacionMinima) {
    ifstream aloj("alojamientos.txt");
    ifstream users("usuarios.txt");

    if (!aloj.is_open() || !users.is_open()) {
        cout << "Error abriendo archivos" << endl;
        return;
    }

    string linea;
    while (getline(aloj, linea)) {
        char buffer[512];
        strcpy(buffer, linea.c_str());

        char* nombre = strtok(buffer, "|");
        char* idAlojStr = strtok(nullptr, "|");
        char* idAnfitrion = strtok(nullptr, "|");
        strtok(nullptr, "|");
        strtok(nullptr, "|");
        strtok(nullptr, "|");
        strtok(nullptr, "|");
        char* precioStr = strtok(nullptr, "|");

        long int precio = atol(precioStr);

        // Buscar puntuación del anfitrión
        string uline;
        double puntuacion = 0;
        users.clear();
        users.seekg(0);
        while (getline(users, uline)) {
            if (uline.find(idAnfitrion) != string::npos) {
                char buf[256];
                strcpy(buf, uline.c_str());
                strtok(buf, "|");
                strtok(nullptr, "|");
                char* puntos = strtok(nullptr, "|");
                puntuacion = atof(puntos);
                break;
            }
        }

        if (precio <= precioMax && puntuacion >= puntuacionMinima) {
            cout << "Alojamiento válido -> " << linea << endl;
        }
    }

    aloj.close();
    users.close();
}

alojamiento::~alojamiento() {
    // Destructor
}

