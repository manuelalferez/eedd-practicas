/**
 * @file Utils.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */


#include "Utils.h"

int Utils::calcularDistancia(UTM inicio, UTM fin) {
    return sqrt(pow(inicio.latitud - fin.latitud, 2) +
                pow(inicio.longitud - fin.longitud, 2));
}
