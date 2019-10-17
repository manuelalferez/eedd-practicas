/**
 * @file Cliente.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_CLIENTE_H
#define EEDD_PR1_CLIENTE_H

#include <iostream>
#include <math.h>
#include <string>
#include<stdlib.h>
#include <cfloat>
#include <sstream>
#include "ListaDEnlazada.h"
#include "Itinerario.h"
#include "fecha.h"

using namespace std;

class Cliente {
public:
    Cliente() : dni(""), pass(""), nombre(""), direccion(""), posicion(0, 0), itinerarios() {};
    Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud);
    bool operator<(const Cliente &c) const;
    bool operator==(const Cliente &c) const;
    string imprimir();
    void setNombre(string _nombre) { this->nombre = _nombre; }
    double calculaDistancia(Cliente &c);
    string getNombre() { return this->nombre; }
    void crearItinerarios();
    ListaDEnlazada<Itinerario>& getItinerarios() { return itinerarios; }
private:
    string dni;
    string pass;
    string nombre;
    string direccion;
    UTM posicion;
    ListaDEnlazada<Itinerario> itinerarios;

    static UTM coordenada_max;

    static UTM coordenada_min;
};


#endif
