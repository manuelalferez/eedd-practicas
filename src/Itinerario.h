/**
 * @file Itinerario.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 15 de octubre de 2019, 9:21
 * @note Práctica 2. Implementación de una lista doblemente enlazada mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_ITINERARIO_H
#define EEDD_PR1_ITINERARIO_H

#include "fecha.h"
#include "Moto.h"
#include "Utils.h"
#include <sstream>

class Moto;
class Itinerario {
public:
    Itinerario(int _id, double _latitud_ini, double _longitud_ini, double _latitud_fin,
               double _longitud_fin, Fecha _fecha, int _minutos);
    int getId() { return id; }
    UTM getInicio() { return this->inicio; }
    void setFin(UTM posicionFinal) {
        fin.latitud = posicionFinal.latitud;
        fin.longitud = posicionFinal.longitud;
    };
    Moto *getVehiculo() { return this->vehiculo; }

    string getToPrint();
private:
    int id;
    UTM inicio;
    UTM fin;
    Fecha fecha;
    int minutos;

    Moto *vehiculo{};
};


#endif //EEDD_PR1_ITINERARIO_H
