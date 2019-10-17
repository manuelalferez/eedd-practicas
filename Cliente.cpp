/**
 * @file Cliente.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */


#include "Cliente.h"
UTM Cliente::coordenada_min(DBL_MAX,DBL_MAX);
UTM Cliente::coordenada_max(DBL_MIN,DBL_MIN);


Cliente::Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud) :
        dni(_dni), pass(_pass), nombre(_nombre), direccion(_direccion), posicion(_latitud, _longitud) {
    if (_latitud < coordenada_min.latitud) coordenada_min.latitud = _latitud;
    if (_latitud > coordenada_max.latitud) coordenada_max.latitud = _latitud;
    if (_longitud < coordenada_min.longitud) coordenada_min.longitud = _longitud;
    if (_longitud > coordenada_max.longitud) coordenada_max.longitud = _longitud;
}

bool Cliente::operator<(const Cliente &c) const {
    return this->nombre < c.nombre;
}

/*
 * Compara si dos nombres de clientes son iguales
 *
 * Devuelve verdadero si son iguales y falso en caso contrario
 */
bool Cliente::operator==(const Cliente &c) const {
    stringstream ss;
    ss << this->nombre;
    string this_nombre;
    getline(ss, this_nombre, ' ');
    return this_nombre == c.nombre;
}

string Cliente::imprimir() {
    return "DNI: " + this->dni + ", Pass: " + this->pass + ", Nombre: " + this->nombre +
           ", Dirección: " + this->direccion + "Latitud: " + to_string(this->posicion.latitud) + ", Longitud: " +
           to_string(this->posicion.longitud);
}

double Cliente::calculaDistancia(Cliente &c) {
    return sqrt(pow(c.posicion.latitud - this->posicion.latitud, 2) +
                pow(c.posicion.longitud - this->posicion.longitud, 2));
}

void Cliente::crearItinerarios() {
    int num_itinerarios = 1 + rand() % (6 - 1);
    double latitud_random_ini, longitud_random_ini, latitud_random_fin, longitud_random_fin;
    unsigned minutos_aleatorios, dia, mes, anio = 2019, hora, minuto;
    Fecha fecha;
    while (itinerarios.tam() != num_itinerarios) {
        latitud_random_ini = (coordenada_max.latitud - coordenada_min.latitud) *
                             ((double) rand() / (double) RAND_MAX) + coordenada_min.latitud;
        longitud_random_ini = (coordenada_max.longitud - coordenada_min.longitud)
                              * ((double) rand() / (double) RAND_MAX) + coordenada_min.longitud;
        latitud_random_fin = (coordenada_max.latitud - coordenada_min.latitud) *
                             ((double) rand() / (double) RAND_MAX) + coordenada_min.latitud;
        longitud_random_fin = (coordenada_max.longitud - coordenada_min.longitud)
                              * ((double) rand() / (double) RAND_MAX) + coordenada_min.longitud;

        minutos_aleatorios = (unsigned)(1 + rand() % (121 - 1));
        mes = 1 + rand() % (13 - 1);
        hora = rand() % 24;
        minuto = 0 + rand() % 60;
        switch (mes) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                dia = 1 + rand() % (32 - 1); //Meses con 31 días
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                dia = 1 + rand() % (31 - 1); // Meses con 30 días
            case 2:
                dia = 1 + rand() % (29 - 1); // Meses con 28 días
        }
        fecha.asignarDia(dia,mes,anio);
        fecha.asignarHora(hora, minuto);
        Itinerario nuevo_itinerario(itinerarios.tam(), latitud_random_ini, longitud_random_ini, latitud_random_fin,
                                    longitud_random_fin, fecha, minutos_aleatorios);
        this->itinerarios.insertaInicio(nuevo_itinerario);
    }
}