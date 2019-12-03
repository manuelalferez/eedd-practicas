//
// Created by aabedraba on 3/12/19.
//

#ifndef EEDD_PR1_THASHCLIENTE_H
#define EEDD_PR1_THASHCLIENTE_H

#include <string>
#include "Cliente.h"

class THashCliente {
public:
    THashCliente(int tamTabla);
    bool insertar(unsigned long clave, string &dni, Cliente &cli);
    bool buscar(unsigned long clave, string &dni, Cliente &*cli);
    bool borrar(unsigned long clave, string &dni);
    unsigned int numClientes();

private:
    void hash(unsigned long clave, int intento);
};


#endif //EEDD_PR1_THASHCLIENTE_H
