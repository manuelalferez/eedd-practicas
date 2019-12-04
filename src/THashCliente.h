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
    bool insertar(string dni, Cliente &cli);
    bool buscar(string &dni, Cliente *cli);
    bool borrar(unsigned long clave, string &dni);
    unsigned int numClientes();

    unsigned int getTamTabla() const;
    float factorDeCarga();

private:
    unsigned int dispersionDoble(const string dni, unsigned int hash, unsigned int intentos, string modo);
    unsigned int djb2(string dni, string modo);
    unsigned int dispersionCuadratica(const string dni, int hash, unsigned int intentos, string modo);
    void redispersion(int nuevo);
    void inicializacion();
private:
    unsigned int _tamTabla;
    unsigned int _numClientes;
    vector<pair<string, Cliente *>> *_tabla;
    unsigned int _maxColisiones;
    unsigned int _colisiones;
    unsigned int _numInserciones;
    const string _tipoDispersion;
};


#endif //EEDD_PR1_THASHCLIENTE_H
