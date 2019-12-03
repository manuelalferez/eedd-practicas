//
// Created by aabedraba on 3/12/19.
//

#include "THashCliente.h"

THashCliente::THashCliente(int tamTabla) {

}

void THashCliente::hash(unsigned long clave, int intento) {

}

bool THashCliente::borrar(unsigned long clave, string &dni) {

}

bool THashCliente::insertar(Cliente &cli) {

}

unsigned int THashCliente::numClientes() {

}

unsigned int THashCliente::djb2(string *str) {
    char cstr[str->size() + 1];
    strcpy(cstr, str->c_str());
    unsigned long hash = 5381;
    int c;
    while ((c = *cstr++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

int THashCliente::dispersionCuadratica(int hash, int intentos, Cliente *dato) {
    unsigned int pos = (hash + (intentos * intentos)) % _tamTabla;
    if(dato){

    }
}

int THashCliente::dispersionDoble(int hast, int intentos) {

}

THashCliente::~THashCliente() {

}
