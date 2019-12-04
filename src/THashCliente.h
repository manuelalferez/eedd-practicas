//
// Created by aabedraba on 3/12/19.
//

#ifndef EEDD_PR1_THASHCLIENTE_H
#define EEDD_PR1_THASHCLIENTE_H

#include <string>
#include "Cliente.h"

class Cliente;
class THashCliente {
public:
    THashCliente(int tamTabla, string tipoInsercion);
    virtual ~THashCliente();
    bool insertar(string dni, Cliente *cli);
    bool buscar(string &dni, Cliente *&cli);
    bool borrar(string &dni);
    unsigned int numClientes();
    unsigned int maxColisiones();
    float promedioColisiones();

    unsigned int getTamTabla() const;

    unsigned int getColisiones() const;

    unsigned int getNumClientes() const;

    float factorDeCarga();
    vector<Cliente *> * getTodosLosClientes();

private:
    unsigned int dispersionDoble(const string dni, const unsigned int hash, const unsigned int intentos, const string modo);
    unsigned int djb2(const string dni, const string modo);
    unsigned int dispersionCuadratica(const string dni, int hash, unsigned int intentos, string modo);
    void redispersion(int nuevo);
    void inicializacion();

    unsigned int _tamTabla;
    unsigned int _numClientes;
    vector<pair<string, Cliente *>> *_tabla;
    unsigned int _maxColisiones;
    unsigned int _colisiones;
    unsigned int _numInserciones;
    const string _tipoDispersion;
};


#endif //EEDD_PR1_THASHCLIENTE_H
