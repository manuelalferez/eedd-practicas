//
// Created by aabedraba on 3/12/19.
//

#include <cstring>
#include "THashCliente.h"

THashCliente::THashCliente(int tamTabla, string tipoInsercion) :
        _tamTabla(tamTabla),
        _tipoDispersion(tipoInsercion) {

}
bool THashCliente::borrar(unsigned long clave, string &dni) {
    unsigned int pos = djb2(dni, "buscar");
    if (pos != INT_MAX) {
        delete _tabla.at(pos).second; //TODO no está resulto según implementación
        return true;
    }
    return false;
}

bool THashCliente::buscar(string &dni, Cliente &*cli) {
    unsigned int pos = djb2(dni, "buscar");
    if (pos == INT_MAX) {
        cli = _tabla.at(pos).second; //TODO no está resulto según implementación
        return true;
    }
    return false;
}

bool THashCliente::insertar(string &dni, Cliente &cli) {
    unsigned int pos = djb2(cli.getDni(), "buscar");
    if (pos == INT_MAX) {
        pos = djb2(cli.getDni(), "insertar");
        _tabla.at(pos).firts = cli; //TODO no está resulto según implementación
        return true;
    }
    return false;
}

unsigned int THashCliente::dispersonDoble(unsigned int hash, int intentos, const string dni, string modo) {
    unsigned int h1 = hash % 57;
    unsigned int h2 = hash % 23;
    unsigned int pos = (h1 + intentos * h2) % _tamTabla;
    if (dni.empty()) {
        if (_tabla->at(pos) == NULL) {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else {
            _colisiones++;
            dispersonDoble(hash, intentos + 1, dni, std::__cxx11::string());
        }
    } else {
        if (_tabla->at(pos)->getDni() == dni) {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else
            dispersonDoble(hash, intentos + 1, dni, std::__cxx11::string());
    }
}

unsigned int THashCliente::numClientes() {
    return _numClientes;
}

unsigned int THashCliente::djb2(string dni, string modo) {
    char cstr[dni.size() + 1];
    strcpy(cstr, dni.c_str());
    unsigned long hash = 5381;
    int c;
    while ((c = *cstr++)) hash = ((hash << 5) + hash) + c;
    if (_tipoDispersion == "doble") {
        return dispersonDoble(hash, 0, dni, std::__cxx11::string());
    } else if (_tipoDispersion == "cuadratica") {
        return dispersionCuadratica(dni, hash, 0, modo);
    }
}

unsigned int THashCliente::dispersionCuadratica(const string dni, int hash, int intentos) {
    unsigned int pos = (hash + (intentos * intentos)) % _tamTabla;
    if (dni.empty()) {
        if (_tabla->at(pos) == NULL) {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else {
            _colisiones++;
            dispersionCuadratica(dni, hash, intentos + 1);
        }
    } else {
        if (_tabla->at(pos)->getDni() == dni) {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else
            dispersionCuadratica(dni, hash, intentos + 1);
    }
}

THashCliente::~THashCliente() {

}
