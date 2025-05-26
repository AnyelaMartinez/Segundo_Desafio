#include <string>
#ifndef UDEASTAYHEAD_H
#define UDEASTAYHEAD_H

using namespace std;

class fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    fecha();
    fecha(int d, int m, int a);
    fecha(const fecha& otra);
    ~fecha();

    bool esMenor(const fecha& otra) const;
    bool esIgual(const fecha& otra) const;
    fecha sumarDias(int dias) const;
    void mostrar() const;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void leerDesdeCadena(const char* fecha); // yyyy-mm-dd
    void convertirACadena(char* destino) const; // para guardar en archivo
};

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
    void cargaUpdateDataAj();
    void aljDisponible();
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
    void cargaUpdateDataR();

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
    void cargaUpdateDataA();
    bool loginA(const string& username, const string& pass);
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
    bool loginH(const string& username, const string& pass);
    void reservarAlojamiento();
    void anularReserva();
    void cargaUpdateDataH();

    ~huesped();
};

#endif // UDEASTAYHEAD_H
