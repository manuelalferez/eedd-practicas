/**
 * @file Cliente.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_CLIENTE_H
#define EEDD_PR1_CLIENTE_H

#include <iostream>
#include <cmath>
#include <string>
#include<cstdlib>
#include <cfloat>
#include <sstream>
#include "fecha.h"
#include "Itinerario.h"
#include "EcoCityMoto.h"
#include <list>

using namespace std;

class Itinerario;
class EcoCityMoto;
class Itinerario;

class Cliente {
public:
    Cliente() : dni(""), pass(""), nombre(""), direccion(""), posicion(0, 0), rutas(), acceso(0) {};
    Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud,
            EcoCityMoto *_acceso);
    virtual ~Cliente() {}
    bool operator<(const Cliente &c) const;
    bool operator>(const Cliente &c) const;
    bool operator==(const Cliente &c) const;
    string imprimir();
    string getDni() { return this->dni; };
    void crearItinerarios();
    void agregarItinerario(UTM inicio, Moto *moto);
    list<Itinerario> &getItinerarios() { return rutas; };
    Moto *buscarMotoCercana();
    void desbloquearMoto(Moto &moto);
    void terminarTrayecto(UTM min, UTM max);
    int simularMovimiento();
    UTM getUTM(UTM min, UTM max);

    void addItinerario(Itinerario& itinerario);
private:
    string dni;
    string pass;
    string nombre;
    string direccion;
    UTM posicion;
    std::list<Itinerario> rutas;
    EcoCityMoto *acceso;
    static UTM coordenada_max;
    static UTM coordenada_min;
};


#endif
