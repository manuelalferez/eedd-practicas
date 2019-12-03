//
// Created by aabedraba on 3/12/19.
//

#ifndef EEDD_PR1_THASHCLIENTE_H
#define EEDD_PR1_THASHCLIENTE_H

#include <string>
#include "Cliente.h"

class THashCliente {
public:
    THashCliente(int tamTabla, string tipoInsercion);
    virtual ~THashCliente();
    bool insertar(unsigned long clave, string &dni, Cliente &cli);
    bool buscar(unsigned long clave, string &dni, Cliente &*cli);
    bool borrar(unsigned long clave, string &dni);
    unsigned int numClientes();

private:
    void hash(unsigned long clave, int intento);
    unsigned int dispersonDoble(string dni, unsigned int hash, int intentos);

private:
    unsigned int _tamTabla;
    unsigned int _numClientes;
    unsigned int _maxColisiones;
    unsigned int _colisiones;
    unsigned int _numInserciones;
    const string _tipoDispersion;
    vector<Cliente*> *_tabla;
};


#endif //EEDD_PR1_THASHCLIENTE_H
