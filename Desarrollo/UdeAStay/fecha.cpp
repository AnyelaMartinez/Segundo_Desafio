#include "UdeAStayhead.h"
#include <iostream>
#include <cstdio>
#include <cstring>

fecha::fecha() {
    dia = mes = anio = 0;
}

fecha::fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}

fecha::fecha(const fecha& otra) {
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
}

fecha::~fecha() {}

bool fecha::esMenor(const fecha& otra) const {
    if (anio < otra.anio) return true;
    if (anio == otra.anio && mes < otra.mes) return true;
    if (anio == otra.anio && mes == otra.mes && dia < otra.dia) return true;
    return false;
}

bool fecha::esIgual(const fecha& otra) const {
    return (dia == otra.dia && mes == otra.mes && anio == otra.anio);
}

fecha fecha::sumarDias(int dias) const {
    fecha nueva = *this;
    nueva.dia += dias;

    while (nueva.dia > 30) {
        nueva.dia -= 30;
        nueva.mes++;
        if (nueva.mes > 12) {
            nueva.mes = 1;
            nueva.anio++;
        }
    }

    return nueva;
}

void fecha::mostrar() const {
    std::cout << (dia < 10 ? "0" : "") << dia << "/"
              << (mes < 10 ? "0" : "") << mes << "/"
              << anio;
}

int fecha::getDia() const { return dia; }
int fecha::getMes() const { return mes; }
int fecha::getAnio() const { return anio; }

void fecha::leerDesdeCadena(const char* fecha) {
    sscanf(fecha, "%d-%d-%d", &anio, &mes, &dia);
}

void fecha::convertirACadena(char* destino) const {
    sprintf(destino, "%04d-%02d-%02d", anio, mes, dia);
}

string fecha::formatoBonito() const {
    const char* dias[] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
    const char* meses[] = {"", "enero", "febrero", "marzo", "abril", "mayo", "junio",
                           "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

    string resultado = string("X") + ", " + to_string(dia) + " de " + meses[mes] + " del " + to_string(anio);
    return resultado;
}
