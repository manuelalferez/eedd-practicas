/**
 * @file Moto.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */
#include "Moto.h"

Moto::Moto(string _id, int _estatus, double _latitud, double _longitud) : id(_id), posicion(_latitud, _longitud),
                                                                          estatus((estados) _estatus), cliente(0) {}
Moto::~Moto() {}

bool Moto::seActiva(Cliente &cli) {
    this->cliente = &cli;
    estatus = activa;
    return true;
}

void Moto::seDesactiva() {
    this->cliente = nullptr;
    estatus = bloqueada;
}

bool Moto::estaDisponible() {
    return estatus == bloqueada;
}