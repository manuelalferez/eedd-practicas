//
// Created by aabedraba on 3/12/19.
//

#ifndef EEDD_PR1_THASHCLIENTE_H
#define EEDD_PR1_THASHCLIENTE_H

#include <string>
#include "Cliente.h"
#include <cmath>

class THashCliente {
public:
    THashCliente(int tamTabla);
    virtual ~THashCliente();
    bool insertar(unsigned long clave, string &dni, Cliente &cli);
    bool buscar(unsigned long clave, string &dni, Cliente &*cli);
    bool borrar(unsigned long clave, string &dni);
    unsigned int numClientes();

private:
    void hash(unsigned long clave, int intento);
    unsigned int djb2(string *str);
    int dispersionCuadratica(int hash, int intentos, Cliente *dato);
    int dispersionDoble(int hast, int intentos);
private:
    unsigned int _tamTabla;
    unsigned int _numClientes;
    vector<Cliente *> *_tabla;
};


#endif //EEDD_PR1_THASHCLIENTE_H
