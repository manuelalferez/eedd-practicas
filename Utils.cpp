//
// Created by aabedraba on 31/10/19.
//


#include "Utils.h"

int Utils::calcularDistancia(UTM inicio, UTM fin) {
    return sqrt(pow(inicio.latitud - fin.latitud, 2) +
                pow(inicio.longitud - fin.longitud, 2));
}
