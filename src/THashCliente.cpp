//
// Created by aabedraba on 3/12/19.
//

#include "THashCliente.h"

THashCliente::THashCliente(int tamTabla, string tipoInsercion):
        _tamTabla(tamTabla),
        _tipoDispersion(tipoInsercion)
{

}

void THashCliente::hash(unsigned long clave, int intento) {

}

bool THashCliente::borrar(unsigned long clave, string &dni) {

}

bool THashCliente::insertar(Cliente &cli) {

    unsigned int pos = djb2(cli.getDni(), cli);
    if (_tipoDispersion == "doble"){

    }

}

unsigned int THashCliente::dispersonDoble(string dni, unsigned int hash, int intentos) {
    unsigned int h1 = hash % 57;
    unsigned int h2 = hash % 23;
    unsigned int pos = (h1 + intentos*h2) % _tamTabla;
    if (dni.empty()){
        if (_tabla->at(pos) == NULL ) {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else {
            _colisiones++;
            dispersonDoble(dni, hash, intentos + 1);
        }
    } else {
        if (_tabla->at(pos)->getDni() == dni ) {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else
            dispersonDoble(dni, hash, intentos + 1);
    }
}

unsigned int THashCliente::numClientes() {
    return _numClientes;
}

unsigned int THashCliente::djb2(string *str) {
    char cstr[str->size() + 1];
    strcpy(cstr, str->c_str());
    unsigned long hash = 5381;
    int c;
    while ((c = *cstr++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

unsigned int THashCliente::dispersionCuadratica(const string dni, int hash, int intentos) {
    unsigned int pos = (hash + (intentos * intentos)) % _tamTabla;
    if (dni.empty()){
        if (_tabla->at(pos) == NULL ) {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else {
            _colisiones++;
            dispersionCuadratica(dni, hash, intentos + 1);
        }
    } else {
        if (_tabla->at(pos)->getDni() == dni ) {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else
            dispersionCuadratica(dni, hash, intentos + 1);
    }
}

int THashCliente::dispersionDoble(int hast, int intentos) {

}

THashCliente::~THashCliente() {

}
