#include "UdeAStayhead.h"
#include <iostream>
using namespace std;


int main() {
    anfitrion obj;
    huesped hobj;
    alojamiento alj;
    int rol;
    cout << "\n*************************\n";
    cout << "*    Bienvenido a UdeAStay    *\n";
    cout << "*************************\n";
    cout << "1. Anfitrion\n";
    cout << "2. Huesped\n";
    cout << "Ingrese el numero de su rol: ";
    cin >> rol;
    if (rol == 1) {
        string userA, passA;
        cout << "Ingrese su username de anfitrion: "; cin >> userA;
        cout << "Ingrese su clave de anfitrion: "; cin >> passA;
        if (obj.loginA(userA, passA)) {
            int opc;
            cout << "Opciones disponibles:\n";
            cout << "1. Anular una reservacion.\n";
            cout << "2. Consultar las reservaciones en sus alojamientos.\n";
            cout << "3. Actualizar historico.\n";
            cout << "Seleccione: "; cin >> opc;
            if (opc == 1) obj.anularReserva();
            else if (opc == 2) obj.consultarReserva();
            else if (opc == 3) obj.updateHistorial();
            else cout << "Opcion invalida.\n";
        } else {
            cout << "Credenciales incorrectas.\n";
        }
    } else if (rol == 2) {
        string userU, passU;
        cout << "Ingrese su username de huesped: "; cin >> userU;
        cout << "Ingrese su clave de huesped: "; cin >> passU;
        if (hobj.loginH(userU, passU)) {
            int opc;
            cout << "\nOpciones disponibles:\n";
            cout << "1. Reservar un alojamiento.\n";
            cout << "2. Anular una reservacion.\n";
            cout << "Seleccione: "; cin >> opc;
            if (opc == 1) {
                int filtro;
                cout << "Desea aplicar filtros?\n";
                cout << "0. No aplicar filtros\n";
                cout << "1. Costo maximo por noche\n";
                cout << "2. Puntuacion minima del anfitrion\n";
                cout << "3. Ambos filtros\n";
                cout << "Seleccione una opcion: "; cin >> filtro;
                if (filtro == 0) alj.mostrarAlojamientosDisponibles();
                else if (filtro == 1) {
                    long int precioMax; cout << "Ingrese el valor maximo por noche: "; cin >> precioMax;
                    alj.mostrarAlojamientosFiltrados(precioMax, 0);
                } else if (filtro == 2) {
                    double punt; cout << "Ingrese la puntuacion minima aceptable: "; cin >> punt;
                    alj.mostrarAlojamientosFiltrados(999999999, punt);
                } else if (filtro == 3) {
                    long int precioMax; double punt;
                    cout << "Ingrese el valor maximo por noche: "; cin >> precioMax;
                    cout << "Ingrese la puntuacion minima aceptable: "; cin >> punt;
                    alj.mostrarAlojamientosFiltrados(precioMax, punt);
                } else cout << "Opcion de filtro invalida.\n";
                // Buscar por código si desea
                char s; cout << "¿Buscar por codigo de alojamiento? (s/n): "; cin >> s;
                if (s == 's' || s == 'S') {
                    int codigo; cout << "Ingrese el codigo: "; cin >> codigo;
                    alj.mostrarAlojamientoPorCodigo(codigo);
                }
                hobj.reservarAlojamiento();
            } else if (opc == 2) hobj.anularReserva();
            else cout << "Opcion invalida.\n";
        } else cout << "Credenciales incorrectas.\n";
    } else {
        cout << "Rol invalido.\n";
    }
    cout << "Gracias por usar UdeAStay.\n";
    return 0;
}
