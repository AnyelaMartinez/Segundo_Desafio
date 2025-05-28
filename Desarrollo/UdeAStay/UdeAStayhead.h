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
    string formatoBonito() const;
    void leerDesdeCadena(const char* fecha);
    void convertirACadena(char* destino) const;
};

class alojamiento{
private:
    string nombre;
    int idAlojamiento;
    string anfitrion;
    string departamento;
    string municipio;
    string tipoAlojamiento;
    string direccion;
    long int precioNoche;
    string amenidades;
    string fechaReserva;

public:
    alojamiento();
    void cargaUpdateDataAj();
    void aljDisponible();
    void mostrarAlojamientosDisponibles();
    void mostrarAlojamientosFiltrados(long int precioMax, double puntuacionMinima);
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
    int getId() const;
    void generarComprobante(int idReserva, int idAlojamiento, int idHuesped, const fecha& entrada, int noches);
    ~huesped();
};

#endif // UDEASTAYHEAD_H
