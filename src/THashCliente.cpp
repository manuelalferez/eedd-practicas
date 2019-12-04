//
// Created by aabedraba on 3/12/19.
//

#include <cstring>
#include <climits>
#include "THashCliente.h"

THashCliente::THashCliente(int tamTabla, string tipoInsercion) :
        _tamTabla(tamTabla),
        _tipoDispersion(tipoInsercion) {
    inicializacion();
}

void THashCliente::inicializacion() {
    _tabla = new vector<pair<string, Cliente *>>(_tamTabla);
    for (int i = 0; i < _tamTabla; i++) {
        _tabla->at(i).first = "vacia";
        _tabla->at(i).second = nullptr;
    }
}
unsigned int THashCliente::maxColisiones(){
    return _maxColisiones;
}

unsigned int THashCliente::promedioColisiones(){
    return _colisiones/_numInserciones;
}

bool THashCliente::borrar(string &dni) {
    unsigned int pos = djb2(dni, "buscar");
    if (pos != INT_MAX) {
        delete _tabla->at(pos).second;
        _tabla->at(pos).first = "disponible";
        _numClientes--;
        if (factorDeCarga() < 0.33) redispersion(_tamTabla/2);
        return true;
    }
    return false;
}

bool THashCliente::buscar(string &dni, Cliente *cli) {
    unsigned int pos = djb2(dni, "buscar");
    if (pos == INT_MAX) {
        cli = _tabla->at(pos).second;
        return true;
    }
    return false;
}

bool THashCliente::insertar(string dni, Cliente *cli) {
    unsigned int pos = djb2(cli->getDni(), "buscar");
    if (pos == INT_MAX) {
        pos = djb2(cli->getDni(), "insertar");
        _tabla->at(pos).second = cli;
        _tabla->at(pos).first = "ocupada";
        _numInserciones++;
        _numClientes++;
        if (factorDeCarga() > 0.7)
            redispersion(_tamTabla * 2);

        return true;
    }
    return false;
}

unsigned int THashCliente::dispersionDoble(const string dni, unsigned int hash, unsigned int intentos, string modo) {
    unsigned int h1 = hash % 57;
    unsigned int h2 = hash % 23;
    unsigned int pos = (h1 + intentos * h2) % _tamTabla;
    if (modo == "insertar") {
        if (_tabla->at(pos).first == "disponible" || _tabla->at(pos).first == "vacia") {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else {
            _colisiones++;
            dispersionDoble(dni, hash, intentos + 1, modo);
        }
    } else if (modo == "busqueda") {
        if (_tabla->at(pos).first == "disponible")
            dispersionDoble(dni, hash, intentos + 1, modo);
        else if (_tabla->at(pos).first == "ocupada") {
            if (_tabla->at(pos).second->getDni() == dni)
                return pos;
            else
                dispersionDoble(dni, hash, intentos + 1, modo);
        }
        if (modo == "vacia") {
            return INT_MAX;
        }
    }
}

unsigned int THashCliente::numClientes() {
    return _numClientes;
}

unsigned int THashCliente::djb2(string dni, string modo) {
    const char *str = dni.c_str();
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    if (_tipoDispersion == "doble") {
        return dispersionDoble(dni, hash, 0, modo);
    } else if (_tipoDispersion == "cuadratica") {
        return dispersionCuadratica(dni, hash, 0, modo);
    }
}

unsigned int THashCliente::dispersionCuadratica(const string dni, int hash, unsigned int intentos, string modo) {
    unsigned int pos = (hash + (intentos * intentos)) % _tamTabla;
    if (modo == "insertar") {
        if (_tabla->at(pos).first == "disponible" || _tabla->at(pos).first == "vacia") {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else {
            _colisiones++;
            dispersionCuadratica(dni, hash, intentos + 1, modo);
        }
    } else if (modo == "busqueda") {
        if (_tabla->at(pos).first == "disponible")
            dispersionCuadratica(dni, hash, intentos + 1, modo);
        else if (_tabla->at(pos).first == "ocupada") {
            if (_tabla->at(pos).second->getDni() == dni)
                return pos;
            else
                dispersionCuadratica(dni, hash, intentos + 1, modo);
        }
        if (modo == "vacia") {
            return INT_MAX;
        }
    }
}

void THashCliente::redispersion(int nuevo) {
    vector<pair<string, Cliente *>> *copia;
    copia = this->_tabla;
    _tamTabla = nuevo;
    inicializacion();
    for (int i = 0; i < copia->size(); ++i) {
        if (copia->at(i).first == "ocupada")
            insertar(copia->at(i).second->getDni(), copia->at(i).second);
    }
    delete (copia);
}

float THashCliente::factorDeCarga() {
    return _numClientes/_tamTabla;
}

THashCliente::~THashCliente() {
    for (int i = 0; i < _tamTabla; ++i) {
        delete _tabla->at(i).second;
    }
    delete _tabla;
}

vector<Cliente *> *THashCliente::getTodosLosClientes() {
    vector<Cliente *> *aDevolver = new vector<Cliente*>;
    for (int i = 0; i < _tamTabla; ++i) {
        if (_tabla->at(i).first == "ocupada")
            aDevolver->push_back(_tabla->at(i).second);
    }
    return aDevolver;
}

unsigned int THashCliente::getTamTabla() const {
    return _tamTabla;
}
