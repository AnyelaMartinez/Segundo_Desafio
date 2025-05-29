#include "UdeAStayhead.h"
#include "globales.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

huesped::huesped() : idHuesped(0), antiguedad(0), puntuacion(0.0) {}

bool huesped::loginH(const string& username, const string& pass) {
    std::ifstream fin("usuariosH.txt");
    if (!fin.is_open()) {
        std::cout << "Error abriendo usuariosH.txt\n";
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
        if (user && passw && username == user && pass == passw) {
            idHuesped = atoi(idStr);
            antiguedad = atoi(ant);
            puntuacion = atof(punt);
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

int huesped::getId() const { return idHuesped; }

void huesped::generarComprobante(int idReserva, int idAlojamiento, int idHuesped, const fecha& entrada, int noches) {
    fecha salida = entrada.sumarDias(noches);
    string nombreArchivo = "comprobante_" + std::to_string(idReserva) + ".txt";
    std::ofstream fout(nombreArchivo.c_str());
    if (!fout.is_open()) {
        std::cout << "Error al crear comprobante\n";
        return;
    }
    fout << "***************************************\n";
    fout << "*       COMPROBANTE DE RESERVA        *\n";
    fout << "***************************************\n\n";
    fout << "Código de la reserva: " << idReserva << std::endl;
    fout << "ID del huesped: " << idHuesped << std::endl;
    fout << "Código del alojamiento: " << idAlojamiento << std::endl;
    fout << "Fecha de inicio: " << entrada.formatoBonito() << std::endl;
    fout << "Fecha de finalización: "<< salida.formatoBonito() << std::endl;
    fout << "Gracias por usar UdeAStay"<< std::endl;
    fout.close();
    std::cout << "Comprobante guardado en " << nombreArchivo << std::endl;
}

void huesped::reservarAlojamiento() {
    contador_iteraciones = 0;
    std::ofstream fout("reservas.txt", std::ios::app);
    if (!fout.is_open()) {
        std::cout << "Error abriendo reservas.txt\n";
        return;
    }
    string entrada, metodoPago, fechaPago, observaciones;
    int idReserva = 1, idAlojamiento, noches;
    long int monto;
    std::cout << "ID del alojamiento: "; std::cin >> idAlojamiento;
    std::cout << "Fecha de entrada (YYYY-MM-DD): "; std::cin >> entrada;
    std::cout << "Cantidad de noches: "; std::cin >> noches;

    // Validación de cruces de fechas para este huésped
    std::ifstream fin("reservas.txt");
    bool conflicto = false;
    while (getline(fin, observaciones)) { // usaremos observaciones como buffer temporal
        contador_iteraciones++;
        char buffer[512];
        strcpy(buffer, observaciones.c_str());
        char* fechaEntrada = strtok(buffer, "|");
        char* nochesStr = strtok(NULL, "|");
        char* idReservaStr = strtok(NULL, "|");
        char* idAlojStr = strtok(NULL, "|");
        char* idHuespStr = strtok(NULL, "|");
        if (!fechaEntrada || !nochesStr || !idHuespStr) continue;
        fecha fExistente; fExistente.leerDesdeCadena(fechaEntrada);
        int nochesExistente = atoi(nochesStr);
        int idHuesp = atoi(idHuespStr);
        fecha fFinExistente = fExistente.sumarDias(nochesExistente);
        fecha fNueva; fNueva.leerDesdeCadena(entrada.c_str());
        fecha fFinNueva = fNueva.sumarDias(noches);
        if (idHuesp == idHuesped) {
            // Verificar cruce
            if (!(fFinNueva.esMenor(fExistente) || fFinExistente.esMenor(fNueva))) {
                conflicto = true;
                break;
            }
        }
    }
    fin.close();
    if (conflicto) {
        std::cout << "Ya tiene una reserva en esas fechas.\n";
        return;
    }
    // Validar disponibilidad del alojamiento para ese rango
    fin.open("reservas.txt");
    conflicto = false;
    while (getline(fin, observaciones)) {
        contador_iteraciones++;
        char buffer[512];
        strcpy(buffer, observaciones.c_str());
        char* fechaEntrada = strtok(buffer, "|");
        char* nochesStr = strtok(NULL, "|");
        char* idReservaStr = strtok(NULL, "|");
        char* idAlojStr = strtok(NULL, "|");
        if (!fechaEntrada || !nochesStr || !idAlojStr) continue;
        fecha fExistente; fExistente.leerDesdeCadena(fechaEntrada);
        int nochesExistente = atoi(nochesStr);
        int idAloj = atoi(idAlojStr);
        fecha fFinExistente = fExistente.sumarDias(nochesExistente);
        fecha fNueva; fNueva.leerDesdeCadena(entrada.c_str());
        fecha fFinNueva = fNueva.sumarDias(noches);
        if (idAloj == idAlojamiento) {
            if (!(fFinNueva.esMenor(fExistente) || fFinExistente.esMenor(fNueva))) {
                conflicto = true;
                break;
            }
        }
    }
    fin.close();
    if (conflicto) {
        std::cout << "El alojamiento no está disponible en ese rango.\n";
        return;
    }
    // Generar ID de reserva automáticamente
    int maxId = 0;
    fin.open("reservas.txt");
    while (getline(fin, observaciones)) {
        contador_iteraciones++;
        char buffer[512];
        strcpy(buffer, observaciones.c_str());
        strtok(buffer, "|");
        strtok(NULL, "|");
        char* idReservaStr = strtok(NULL, "|");
        if (idReservaStr) {
            int id = atoi(idReservaStr);
            if (id > maxId) maxId = id;
        }
    }
    fin.close();
    idReserva = maxId + 1;
    std::cout << "Método de pago: "; std::cin >> metodoPago;
    std::cout << "Fecha del pago (YYYY-MM-DD): "; std::cin >> fechaPago;
    std::cout << "Monto total: "; std::cin >> monto;
    std::cout << "Observaciones (max 1000 caracteres, sin espacios): "; std::cin >> observaciones;
    fout << entrada << "|" << noches << "|" << idReserva << "|" << idAlojamiento << "|" << idHuesped << "|"
         << metodoPago << "|" << fechaPago << "|" << monto << "|" << observaciones << std::endl;
    fout.close();
    std::cout << "Reserva registrada exitosamente.\n";
    fecha fcon; fcon.leerDesdeCadena(entrada.c_str());
    generarComprobante(idReserva, idAlojamiento, idHuesped, fcon, noches);
    std::cout << "Iteraciones: " << contador_iteraciones << "\n";
}

void huesped::anularReserva() {
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
huesped::~huesped() {}
