#include "UdeAStayhead.h"
#include <iostream>

using namespace std;

int main()
{
    anfitrion obj;
    huesped hobj;
    int rol;

    cout<<endl;
    cout<<"*************************"<<endl;
    cout<<"*                       *"<<endl;
    cout<<"* Bienvenido a UdeAStay *"<<endl;
    cout<<"*                       *"<<endl;
    cout<<"*************************"<<endl;

    cout<<"1. Anfitrion"<<endl;
    cout<<"2. Huesped"<<endl;
    cout<<"Ingrese el numero de su rol"<<endl;
    cin>>rol;
    if(rol==1){
        string userA, passA;
        cout<<"Ingrese su username de anfitrion"<<endl;
        cin>>userA;
        cout<<"Ingrese su clave de anfitrion"<<endl;
        cin>>passA;

        if (obj.loginA(userA,passA)){

        int opc;
        cout<<"Usted tiene varias opciones, seleccione el numero de la opción que desea realizar"<<endl;
        cout<<"1. Anular una reservacion."<<endl;
        cout<<"2. Consultar las reservaciones en sus alojamientos."<<endl;
        cout<<"3. Actualizar historico."<<endl;
        cin>>opc;

        if(opc==1){
            cout<<"Digite el ID de la reserva que desea anular"<<endl;
            // funcion con anular reserva, parametro id del alojamiento
            //Primero crear alojamientos

        }
        else if (opc==2){

        }
        else if (opc==3){

        }
        else {
            cout<<"Opcion invalida"<<endl;
        }
        }
        else{
        cout << "Credenciales incorrectas"<<endl;
        }
    }
    else if (rol==2){

        string userU, passU;
        cout<<"Ingrese su username de huesped"<<endl;
        cin>>userU;
        cout<<"Ingrese su clave de huesped"<<endl;
        cin>>passU;

        if (hobj.loginH(userU,passU)){
        int opc;

        cout<<"Usted tiene varias opciones, seleccione el numero de la opción que desea realizar"<<endl;
        cout<<"1. Reserva un alojamiento."<<endl;
        cout<<"2. Anular una reservacion."<<endl;
        cin>>opc;

        if(opc==1){
            int res = 1;
            cout<<"Ingrese la fecha de entrada"<<endl;
            //fecha
            cout<<"Ingrese el municipio en el que desa la reservacion"<<endl;
            //municipio
            cout<<"Cuantas noches necesita para su reservacion"<<endl;
            //cantidad Noches

            //muestra disponibles

            cout<<"Desea agregar filtros?"<<endl;
            //respuesta

            if(res == 1){
                cout<<"Ingrese el codigo del alojamiento que desea"<<endl;
                //Reservar alojamiento

                //comprobante
            }
            else if (res==2){
                int filtros = 0;
                cout<<"1. Costo maximo por noche"<<endl;
                cout<<"2. puntuacion del anfitrion"<<endl;
                cout<<"3. Ambos"<<endl;
                cout<<"Cual o cuales filtros desea aplicar?"<<endl;
                //filtros
                if(filtros==1){
                    cout<<"Ingrese el valor maximo que dispone para pagar por noche"<<endl;
                    //pago maximo

                    //muestra disponibles

                    cout<<"Ingrese el codigo del alojamiento que desea"<<endl;
                    //Reservar alojamiento

                    //comprobante
                }
                else if (filtros==2){
                    cout<<"Ingrese la puntuacion minima del anfitrion que esta dispuesto a aceptar"<<endl;
                    //puntos anfitrion

                    //muestra disponibles

                    cout<<"Ingrese el codigo del alojamiento que desea"<<endl;
                    //Reservar alojamiento

                    //comprobante
                }
                else if (filtros ==3){
                    cout<<"Ingrese el valor maximo que dispone para pagar por noche"<<endl;
                    //pago maximo
                    cout<<"Ingrese la puntuacion minima del anfitrion que esta dispuesto a aceptar"<<endl;
                    //puntos anfitrion

                    //muestra disponibles

                    cout<<"Ingrese el codigo del alojamiento que desea"<<endl;
                    //Reservar alojamiento

                    //comprobante
                }
                else {
                    cout<<"Opcion invalida"<<endl;
                }
            }
            else {
                cout<<"Opcion invalida"<<endl;
            }
        }
        else if (opc==2){
            cout<<"Digite el ID de la reserva que desea anular"<<endl;
            //anular reserva
        }
        else {
            cout<<"Opcion invalida"<<endl;
        }
        }
        else{
        cout << "Credenciales incorrectas"<<endl;
        }
    }
    else{
        cout<<" Rol invalido"<<endl;
    }

    return 0;
}



