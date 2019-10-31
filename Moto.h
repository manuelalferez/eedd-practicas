/**
 * @file Moto.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */

#ifndef EEDD_PR1_MOTO_H
#define EEDD_PR1_MOTO_H

#include "Cliente.h"
#include "Utils.h"

enum estados {
    bloqueada = 0, activa = 1, sinBateria = 2, rota = 3
};

//struct UTM;

class Cliente;

class Moto {
public:
    Moto() : id(""), posicion(), estatus(bloqueada), cliente(0) {}
    Moto(string _id, int _estatus, double _latitud, double _longitud);
    bool seActiva(Cliente &cli);
    virtual ~Moto();
    void seDesactiva();
    UTM getPosicion() { return posicion; }
    bool estaDisponible();
    string getId() { return id; }
private:
    string id;
    UTM posicion;
    estados estatus;
    Cliente *cliente;
};

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

#endif //EEDD_PR1_MOTO_H
