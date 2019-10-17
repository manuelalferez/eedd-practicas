/**
 * @file Itinerario.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 15 de octubre de 2019, 9:21
 * @note Práctica 2. Implementación de una lista doblemente enlazada mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_ITINERARIO_H
#define EEDD_PR1_ITINERARIO_H

#include "fecha.h"

// Coordenadas UTM formadas por latitud y longitud
struct UTM {
    double latitud;
    double longitud;
    UTM(double _lat, double _long) : latitud(_lat), longitud(_long) {}
};

class Itinerario {
public:
    Itinerario(int _id, double _latitud_ini, double _longitud_ini, double _latitud_fin,
               double _longitud_fin, Fecha _fecha, int _minutos) : id(_id),
                                                                   inicio(_latitud_ini, _longitud_ini),
                                                                   fin(_latitud_fin, _longitud_fin),
                                                                   fecha(_fecha), minutos(_minutos) {}
    int getMinutos() { return minutos; }
    int getId() { return id; }
    UTM getInicio() { return this->inicio; }
    UTM getFin() { return this->fin; }
    Fecha getFecha() { return this->fecha; }
private:
    int id;
    UTM inicio;
    UTM fin;
    Fecha fecha;
    int minutos;

};


#endif //EEDD_PR1_ITINERARIO_H
