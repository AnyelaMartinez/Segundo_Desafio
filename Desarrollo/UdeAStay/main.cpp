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
            //funcion de carga y update
        }
        else if (opc==2){

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



