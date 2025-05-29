#include "UdeAStayhead.h"
#include "globales.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

anfitrion::anfitrion() : idAnfitrion(0), antiguedad(0), puntuacion(0.0), numAlojamientos(0) {}

bool anfitrion::loginA(const string& username, const string& pass) {
    std::ifstream fin("usuariosA.txt");
    if (!fin.is_open()) {
        std::cout << "Error abriendo usuariosA.txt\n";
        return false;
    }
    string linea;
    while (getline(fin, linea)) {
        contador_iteraciones++;
        char buffer[256];
        strcpy(buffer, linea.c_str());
        char* idStr = strtok(buffer, "|");
        char* user = strtok(NULL, "|");
        char* passw = strtok(NULL, "|");
        char* ant = strtok(NULL, "|");
        char* punt = strtok(NULL, "|");
        char* alojamientosIds = strtok(NULL, "|");
        if (user && passw && username == user && pass == passw) {
            idAnfitrion = atoi(idStr);
            antiguedad = atoi(ant);
            puntuacion = atof(punt);
            // Parsear alojamientos
            numAlojamientos = 0;
            if (alojamientosIds) {
                char* token = strtok(alojamientosIds, ",");
                while(token && numAlojamientos < 10) {
                    idsAlojamientos[numAlojamientos++] = atoi(token);
                    token = strtok(NULL, ",");
                }
            }
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

void anfitrion::anularReserva() {
    std::ifstream fin("reservas.txt");
    std::ofstream fout("temp_r.txt");
    if (!fin.is_open() || !fout.is_open()) {
        std::cout << "Error abriendo archivos para anular reserva\n";
        return;
    }
    string linea, idBuscar;
    std::cout << "Ingrese el ID de la reserva que desea anular: "; std::cin >> idBuscar;
    bool encontrada = false;
    while (getline(fin, linea)) {
        contador_iteraciones++;
        if (linea.find("|" + idBuscar + "|") == string::npos)
            fout << linea << std::endl;
        else
            encontrada = true;
    }
    fin.close();
    fout.close();
    remove("reservas.txt");
    rename("temp_r.txt", "reservas.txt");
    if (encontrada) std::cout << "Reserva anulada correctamente.\n";
    else std::cout << "No se encontró una reserva con ese ID.\n";
    std::cout << "Iteraciones: " << contador_iteraciones << "\n";
}

void anfitrion::consultarReserva() {
    std::ifstream fin("reservas.txt");
    if (!fin.is_open()) {
        std::cout << "Error abriendo reservas.txt\n";
        return;
    }
    string fechaIni, fechaFin;
    std::cout << "Ingrese fecha inicial (YYYY-MM-DD): "; std::cin >> fechaIni;
    std::cout << "Ingrese fecha final (YYYY-MM-DD): "; std::cin >> fechaFin;
    fecha desde, hasta;
    desde.leerDesdeCadena(fechaIni.c_str());
    hasta.leerDesdeCadena(fechaFin.c_str());
    string linea;
    while (getline(fin, linea)) {
        contador_iteraciones++;
        char buffer[1024];
        strcpy(buffer, linea.c_str());
        char* fechaEntradaStr = strtok(buffer, "|");
        strtok(NULL, "|"); // noches
        strtok(NULL, "|"); // idReserva
        char* idAlojamientoStr = strtok(NULL, "|");
        if (!idAlojamientoStr) continue;
        int idAloj = atoi(idAlojamientoStr);
        // Comprobar si el alojamiento es de este anfitrión
        bool esDeEste = false;
        for (int i = 0; i < numAlojamientos; ++i) {
            if (idsAlojamientos[i] == idAloj) { esDeEste = true; break; }
        }
        if (!esDeEste) continue;
        fecha entrada;
        entrada.leerDesdeCadena(fechaEntradaStr);
        if (entrada.esMenor(desde) || hasta.esMenor(entrada)) continue;
        std::cout << "Reserva encontrada -> " << linea << std::endl;
    }
    fin.close();
    std::cout << "Iteraciones: " << contador_iteraciones << "\n";
}

void anfitrion::updateHistorial() {
    string fechaAct;
    std::cout << "Ingrese la fecha de corte para histórico (YYYY-MM-DD): "; std::cin >> fechaAct;
    fecha hoy;
    hoy.leerDesdeCadena(fechaAct.c_str());
    std::ifstream fin("reservas.txt");
    std::ofstream foutAct("temp_r.txt");
    std::ofstream foutHist("Historico.txt", std::ios::app);
    if (!fin.is_open() || !foutAct.is_open() || !foutHist.is_open()) {
        std::cout << "Error abriendo archivos para actualizar histórico\n";
        return;
    }
    string linea;
    while (getline(fin, linea)) {
        contador_iteraciones++;
        char buffer[1024];
        strcpy(buffer, linea.c_str());
        char* fechaEntradaStr = strtok(buffer, "|");
        fecha entrada;
        entrada.leerDesdeCadena(fechaEntradaStr);
        if (entrada.esMenor(hoy)) foutHist << linea << std::endl;
        else foutAct << linea << std::endl;
    }
    fin.close(); foutAct.close(); foutHist.close();
    remove("reservas.txt");
    rename("temp_r.txt", "reservas.txt");
    std::cout << "Histórico actualizado correctamente.\n";
    std::cout << "Iteraciones: " << contador_iteraciones << "\n";
}

int anfitrion::getId() const { return idAnfitrion; }
void anfitrion::mostrarAlojamientos() {
    std::cout << "Alojamientos del anfitrión: ";
    for (int i = 0; i < numAlojamientos; ++i) {
        std::cout << idsAlojamientos[i];
        if (i < numAlojamientos-1) std::cout << ", ";
    }
    std::cout << std::endl;
}
anfitrion::~anfitrion() {}
