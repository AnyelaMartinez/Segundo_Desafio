#include "UdeAStayhead.h"
#include <iostream>

using namespace std;

int main() {
    anfitrion obj;
    huesped hobj;
    alojamiento alj;
    int rol;

    cout << endl;
    cout << "*************************" << endl;
    cout << "*                       *" << endl;
    cout << "* Bienvenido a UdeAStay *" << endl;
    cout << "*                       *" << endl;
    cout << "*************************" << endl;

    cout << "1. Anfitrion" << endl;
    cout << "2. Huesped" << endl;
    cout << "Ingrese el numero de su rol: ";
    cin >> rol;

    if (rol == 1) {
        string userA, passA;
        cout << "Ingrese su username de anfitrion: ";
        cin >> userA;
        cout << "Ingrese su clave de anfitrion: ";
        cin >> passA;

        if (obj.loginA(userA, passA)) {
            int opc;
            cout << "Opciones disponibles:"<<endl;
            cout << "1. Anular una reservacion." << endl;
            cout << "2. Consultar las reservaciones en sus alojamientos." << endl;
            cout << "3. Actualizar historico." << endl;
            cout << "Seleccione: ";
            cin >> opc;

            if (opc == 1) {
                obj.anularReserva();
            } else if (opc == 2) {
                obj.consultarReserva();
            } else if (opc == 3) {
                obj.updateHistorial();
            } else {
                cout << "Opcion invalida." << endl;
            }
        } else {
            cout << "Credenciales incorrectas." << endl;
        }
    } else if (rol == 2) {
        string userU, passU;
        cout << "Ingrese su username de huesped: ";
        cin >> userU;
        cout << "Ingrese su clave de huesped: ";
        cin >> passU;

        if (hobj.loginH(userU, passU)) {
            int opc;
            cout << "\nOpciones disponibles:\n";
            cout << "1. Reservar un alojamiento." << endl;
            cout << "2. Anular una reservacion." << endl;
            cout << "Seleccione: ";
            cin >> opc;

            if (opc == 1) {
                int filtro;
                cout << "Desea aplicar filtros?" << endl;
                cout << "0. No aplicar filtros" << endl;
                cout << "1. Costo maximo por noche" << endl;
                cout << "2. Puntuacion minima del anfitrion" << endl;
                cout << "3. Ambos filtros" << endl;
                cout << "Seleccione una opcion: ";
                cin >> filtro;

                if (filtro == 0) {
                    alj.mostrarAlojamientosDisponibles();
                } else if (filtro == 1) {
                    long int precioMax;
                    cout << "Ingrese el valor maximo por noche: ";
                    cin >> precioMax;
                    alj.mostrarAlojamientosFiltrados(precioMax, 0);
                } else if (filtro == 2) {
                    double punt;
                    cout << "Ingrese la puntuacion minima aceptable: ";
                    cin >> punt;
                    alj.mostrarAlojamientosFiltrados(999999999, punt);
                } else if (filtro == 3) {
                    long int precioMax;
                    double punt;
                    cout << "Ingrese el valor maximo por noche: ";
                    cin >> precioMax;
                    cout << "Ingrese la puntuacion minima aceptable: ";
                    cin >> punt;
                    alj.mostrarAlojamientosFiltrados(precioMax, punt);
                } else {
                    cout << "Opcion de filtro invalida." << endl;
                }

                // Realizar la reserva
                hobj.reservarAlojamiento();

            } else if (opc == 2) {
                hobj.anularReserva();
            } else {
                cout << "Opcion invalida." << endl;
            }
        } else {
            cout << "Credenciales incorrectas." << endl;
        }
    } else {
        cout << "Rol invalido." << endl;
    }

    cout << "Gracias por usar UdeAStay." << endl;
    return 0;
}
