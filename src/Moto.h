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
    void seDesactiva(); //TODO update when it's deactivating
    UTM getPosicion() { return posicion; }
    bool estaDisponible();
    string getId() { return id; }
    void actualizaBateria(int minutos);
    float getPorcentajeBateria() const;
    estados getEstatus() const;
    void setPosicion(UTM posicion) { this->posicion = posicion; }
    string imprimir();
private:
    string id;
    UTM posicion;
    estados estatus;
    Cliente *cliente;
    float porcentajeBateria;
};

#endif //EEDD_PR1_MOTO_H
