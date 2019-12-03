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
    unsigned int dispersonDoble(const string dni, unsigned int hash, int intentos);

    unsigned int djb2(string dni);
    int dispersionCuadratica(const string dni, int hash, int intentos, Cliente *dato);
private:
    unsigned int _tamTabla;
    unsigned int _numClientes;
    vector<Cliente *> *_tabla;
    unsigned int _maxColisiones;
    unsigned int _colisiones;
    unsigned int _numInserciones;
    const string _tipoDispersion;
};


#endif //EEDD_PR1_THASHCLIENTE_H
