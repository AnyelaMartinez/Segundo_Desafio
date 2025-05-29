#include "UdeAStayhead.h"
#include "globales.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

alojamiento::alojamiento() : nombre(""), idAlojamiento(0), idAnfitrion(0), departamento(""),
    municipio(""), tipoAlojamiento(""), direccion(""), precioNoche(0), numAmenidades(0) {}

void alojamiento::cargaUpdateDataAj() {
    contador_iteraciones = 0;
    std::ifstream fn("alojamientos.txt");
    if (!fn.is_open()) {
        std::cout << "Error abriendo alojamientos.txt\n";
        return;
    }
    string linea;
    while (getline(fn, linea)) {
        contador_iteraciones++;
        // Aquí podrías cargar a un arreglo si lo necesitas
    }
    fn.close();
}

void alojamiento::mostrarAlojamientosDisponibles() {
    contador_iteraciones = 0;
    std::ifstream alojFile("alojamientos.txt");
    if (!alojFile.is_open()) {
        std::cout << "Error abriendo alojamientos.txt\n";
        return;
    }
    std::ifstream reservasFile("reservas.txt");
    if (!reservasFile.is_open()) {
        std::cout << "Error abriendo reservas.txt\n";
        alojFile.close();
        return;
    }
    std::string municipioBuscado, fechaBuscada;
    std::cout << "Ingrese municipio: "; std::cin >> municipioBuscado;
    std::cout << "Ingrese fecha deseada (YYYY-MM-DD): "; std::cin >> fechaBuscada;
    alojFile.clear();
    alojFile.seekg(0);

    string alojLinea;
    while (getline(alojFile, alojLinea)) {
        contador_iteraciones++;
        char alojBuffer[512];
        strcpy(alojBuffer, alojLinea.c_str());
        char* nombre = strtok(alojBuffer, "|");
        char* idAlojStr = strtok(NULL, "|");
        char* idAnfitrion = strtok(NULL, "|");
        char* departamento = strtok(NULL, "|");
        char* municipio = strtok(NULL, "|");
        if (!municipio || !idAlojStr) continue;
        string municipioStr(municipio);
        if (municipioStr != municipioBuscado) continue;

        // Ahora verificar si está reservado en esa fecha
        bool ocupado = false;
        reservasFile.clear();
        reservasFile.seekg(0);
        string reservaLinea;
        while (getline(reservasFile, reservaLinea)) {
            contador_iteraciones++;
            char resBuffer[512];
            strcpy(resBuffer, reservaLinea.c_str());
            char* fechaRes = strtok(resBuffer, "|");
            strtok(NULL, "|"); // noches
            strtok(NULL, "|"); // idReserva
            char* idResAloj = strtok(NULL, "|");
            if (!fechaRes || !idResAloj) continue;
            string fechaResStr(fechaRes);
            string idResAlojStr(idResAloj);
            if (fechaResStr == fechaBuscada && idResAlojStr == idAlojStr) {
                ocupado = true;
                break;
            }
        }
        if (!ocupado) {
            std::cout << "\nAlojamiento disponible:\n" << alojLinea << std::endl;
        }
    }
    reservasFile.close();
    alojFile.close();
    std::cout << "Iteraciones: " << contador_iteraciones << "\n";
}

void alojamiento::mostrarAlojamientosFiltrados(long int precioMax, double puntuacionMinima) {
    contador_iteraciones = 0;
    std::ifstream aloj("alojamientos.txt");
    std::ifstream users("usuariosA.txt");
    if (!aloj.is_open() || !users.is_open()) {
        std::cout << "Error abriendo archivos\n";
        return;
    }
    string linea;
    while (getline(aloj, linea)) {
        contador_iteraciones++;
        char buffer[512];
        strcpy(buffer, linea.c_str());
        char* nombre = strtok(buffer, "|");
        char* idAlojStr = strtok(NULL, "|");
        char* idAnfitrion = strtok(NULL, "|");
        strtok(NULL, "|");
        strtok(NULL, "|");
        strtok(NULL, "|");
        strtok(NULL, "|");
        char* precioStr = strtok(NULL, "|");
        long int precio = atol(precioStr);
        // Buscar puntuación del anfitrión
        string uline;
        double puntuacion = 0;
        users.clear();
        users.seekg(0);
        while (getline(users, uline)) {
            contador_iteraciones++;
            if (uline.find(idAnfitrion) != string::npos) {
                char buf[256];
                strcpy(buf, uline.c_str());
                strtok(buf, "|");
                strtok(NULL, "|");
                strtok(NULL, "|");
                strtok(NULL, "|");
                char* puntos = strtok(NULL, "|");
                puntuacion = atof(puntos);
                break;
            }
        }
        if (precio <= precioMax && puntuacion >= puntuacionMinima) {
            std::cout << "Alojamiento válido -> " << linea << std::endl;
        }
    }
    aloj.close();
    users.close();
    std::cout << "Iteraciones: " << contador_iteraciones << "\n";
}

void alojamiento::mostrarAlojamientoPorCodigo(int codigo) {
    contador_iteraciones = 0;
    std::ifstream aloj("alojamientos.txt");
    if (!aloj.is_open()) {
        std::cout << "Error abriendo alojamientos.txt\n";
        return;
    }
    string linea;
    bool encontrado = false;
    while (getline(aloj, linea)) {
        contador_iteraciones++;
        char buffer[512];
        strcpy(buffer, linea.c_str());
        strtok(buffer, "|"); // nombre
        char* idAlojStr = strtok(NULL, "|");
        if (idAlojStr && atoi(idAlojStr) == codigo) {
            std::cout << "Alojamiento encontrado: " << linea << std::endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) std::cout << "No se encontró el alojamiento.\n";
    aloj.close();
    std::cout << "Iteraciones: " << contador_iteraciones << "\n";
}

int alojamiento::getIdAlojamiento() const { return idAlojamiento; }
void alojamiento::setIdAlojamiento(int id) { idAlojamiento = id; }
alojamiento::~alojamiento() {}
