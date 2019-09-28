/**
 * @file Cliente.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_CLIENTE_H
#define EEDD_PR1_CLIENTE_H

#include <iostream>
using namespace std;

// Coordenadas UTM formadas por latitud y longitud
struct UTM{
    double latitud;
    double longitud;
    UTM (double _lat, double _long): latitud(_lat), longitud (_long){}
};


class Cliente {
    string dni;
    string pass;
    string nombre;
    string direccion;
    UTM posicion;

public:
    Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud);
};


#endif
