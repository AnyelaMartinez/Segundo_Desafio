#include "UdeAStayhead.h"
#include <iostream>
#include <fstream>
#include <cstring>

huesped::huesped(){
    cout<<"instancias huesped"<<endl;
}

bool huesped::loginH(const string& username, const string& pass){
    ifstream fin("usuariosH.txt");
    if (!fin.is_open()) {
        cout << "Error abriendo usuariosH.txt" << endl;
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

int huesped::getId() const {
    return idHuesped;
}

void huesped::generarComprobante(int idReserva, int idAlojamiento, int idHuesped, const fecha& entrada, int noches) {
    fecha salida = entrada.sumarDias(noches);

    string nombreArchivo = "comprobante_" + to_string(idReserva) + ".txt";
    ofstream fout(nombreArchivo.c_str());

    if (!fout.is_open()) {
        cout << "Error al crear comprobante" << endl;
        return;
    }

    fout << "***************************************\n";
    fout << "*       COMPROBANTE DE RESERVA        *\n";
    fout << "***************************************\n\n";

    fout << "Código de la reserva: " << idReserva << endl;
    fout << "ID del huésped: " << idHuesped << endl;
    fout << "Código del alojamiento: " << idAlojamiento << endl;

    fout << "Fecha de inicio: ";
    entrada.mostrar(); fout << endl;

    fout << "Fecha de finalización: "<< endl;
    salida.mostrar(); fout << endl;

    fout << "Gracias por usar UdeAStay"<< endl;

    fout.close();

    cout << "Comprobante guardado en " << nombreArchivo << endl;
}

void huesped::reservarAlojamiento() {
    fecha fcon;
    ofstream fout("reservas.txt", ios::app);
    if (!fout.is_open()) {
        cout << "Error abriendo archivo reservas.txt" << endl;
        return;
    }

    string entrada, metodoPago, fechaPago, observaciones;
    int idReserva, idAlojamiento, noches;
    long int monto;

    cout << "ID de la reserva: "; cin >> idReserva;
    cout << "ID del alojamiento: "; cin >> idAlojamiento;
    cout << "Fecha de entrada (YYYY-MM-DD): "; cin >> entrada;
    cout << "Cantidad de noches: "; cin >> noches;
    cout << "Método de pago: "; cin >> metodoPago;
    cout << "Fecha del pago (YYYY-MM-DD): "; cin >> fechaPago;
    cout << "Monto total: "; cin >> monto;
    cout << "Observaciones (sin espacios, máx 1000 caracteres): "; cin >> observaciones;

    fout << entrada << "|" << noches << "|" << idReserva << "|" << idAlojamiento << "|" << idHuesped << "|"
         << metodoPago << "|" << fechaPago << "|" << monto << "|" << observaciones << endl;

    fout.close();

    cout << "Reserva registrada exitosamente." << endl;

    fcon.leerDesdeCadena(entrada.c_str());
    generarComprobante(idReserva, getId(), idHuesped,fcon,noches);

}

void huesped::anularReserva() {
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
huesped::~huesped() {
    // Destructor
}

