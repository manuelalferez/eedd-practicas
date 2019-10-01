/**
 * @file Cliente.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */

#include "Cliente.h"

Cliente::Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud) :
        dni(_dni), pass(_pass), nombre(_nombre), direccion(_direccion), posicion(_latitud, _longitud) {}

bool Cliente::operator<(const Cliente &c) const {
    return this->nombre < c.nombre;
}

bool Cliente::operator==(const Cliente &c) const {
    return this->nombre == c.nombre;
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