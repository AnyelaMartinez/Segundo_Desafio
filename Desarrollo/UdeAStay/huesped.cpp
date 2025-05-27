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


void huesped::reservarAlojamiento() {
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
         << metodoPago << "|" << fechaPago << "|" << monto << "|" << observaciones << "\n";

    fout.close();

    cout << "Reserva registrada exitosamente." << endl;

}

void generarComprobante(int idReserva, int idAlojamiento, int idHuesped, const fecha& entrada, int noches) {
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

    fout << "Fecha de finalización: ";
    salida.mostrar(); fout << endl;

    fout << "\nGracias por usar UdeAStay\n";

    fout.close();

    cout << "Comprobante guardado en " << nombreArchivo << endl;
}


void huesped::anularReserva() {
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

void huesped::cargaUpdateDataH(){};

huesped::~huesped() {
    // Destructor
}

