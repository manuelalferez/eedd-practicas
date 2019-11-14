/**
 * @file Utils.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */

#ifndef EEDD_PR1_UTILS_H
#define EEDD_PR1_UTILS_H

#include <cmath>

// Coordenadas UTM formadas por latitud y longitud

struct UTM {
    double latitud;
    double longitud;
    UTM() : latitud(0), longitud(0) {}
    UTM(double _lat, double _long) : latitud(_lat), longitud(_long) {}
    UTM& operator=(UTM copia){
        this->latitud=copia.latitud;
        this->longitud=copia.longitud;
        return *this;
    }
};
namespace Utils {
    int calcularDistancia(UTM inicio, UTM fin);
}

#endif //EEDD_PR1_UTILS_H
