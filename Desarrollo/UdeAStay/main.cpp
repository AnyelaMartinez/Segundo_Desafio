#include <iostream>
#include <string>
using namespace std;

class alojamiento{
private:
    string nombre;
    int idAlojamiento;
    string anfitrion;
    string departamento;
    string minucipio;
    string tipoAlojamiento;
    string direccion;
    long int precioNoche;
    string amenidades;
    string fechaReserva;

public:
    alojamiento();
    ~alojamiento();
};

class reservacion{
private:
    string fechaEntrada;
    int cantNoches;
    int idReserva;
    int idAlojamiento;
    int idHuesped;
    string metodoPago;
    string fechaPago;
    long int montoPago;
    string observaciones;

public:
    reservacion();
    ~reservacion();
};

class anfitrion{
private:
    int idAnfitrion;
    int antiguedad;
    double puntuacion;
    int idAlojamiento;

public:
    anfitrion();
    void cargaUpdateData();
    bool login();
    void anularReserva();
    void consultarReserva();
    void updateHistorial();

    ~anfitrion();
};

class huesped{
private:
    int idHuesped;
    int antiguedad;
    double puntuacion;
    string reservaHuesped;

public:
    huesped();
    bool login();
    void reservarAlojamiento();
    void anularReserva();

    ~huesped();
};

int main()
{

    return 0;
}

alojamiento::alojamiento(){
    cout<<"instancias"<<endl;
}

reservacion::reservacion(){
    cout<<"instancias"<<endl;
}

anfitrion::anfitrion(){
    cout<<"instancias"<<endl;
}

huesped::huesped(){
    cout<<"instancias"<<endl;
}


