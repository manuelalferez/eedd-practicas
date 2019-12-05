

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
unsigned int THashCliente::maxColisiones() {
    return _maxColisiones;
}

float THashCliente::promedioColisiones() {
    return float(_colisiones) / float(_numInserciones);
}

bool THashCliente::borrar(string &dni) {
    unsigned int pos;
    pos = djb2(dni, "busqueda");
    if (pos != INT_MAX) {
        delete _tabla->at(pos).second;
        _tabla->at(pos).first = "disponible";
        _numClientes--;
        if (factorDeCarga() < 0.6) redispersion(_tamTabla / 2);
        return true;
    }
    return false;
}

bool THashCliente::buscar(string &dni, Cliente *&cli) {
    unsigned int pos = djb2(dni, "busqueda");
    if (pos != INT_MAX) {
        cli = _tabla->at(pos).second;
        return true;
    }
    return false;
}

bool THashCliente::insertar(string dni, Cliente *cli) {
    unsigned int pos = djb2(cli->getDni(), "busqueda");
    if (pos == INT_MAX) {
        unsigned int pos = djb2(cli->getDni(), "insertar");
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

unsigned int THashCliente::dispersionDoble(const string dni, const unsigned int hash, const unsigned int intentos,
                                           const string modo) {
    const unsigned int h1 = hash % 103007;
    const unsigned int h2 = hash % 102181;
    const unsigned int pos = (h1 + intentos * h2) % _tamTabla;
    if (modo == "insertar") {
        if (_tabla->at(pos).first == "disponible" || _tabla->at(pos).first == "vacia") {
            if (intentos > _maxColisiones) _maxColisiones = intentos;
            return pos;
        } else {
            _colisiones++;
            return dispersionDoble(dni, hash, (intentos + 1), modo);
        }
    } else if (modo == "busqueda") {
        if (_tabla->at(pos).first == "disponible")
            return dispersionDoble(dni, hash, intentos + 1, modo);
        else if (_tabla->at(pos).first == "ocupada") {
            if (_tabla->at(pos).second->getDni() == dni)
                return pos;
            else
                return dispersionDoble(dni, hash, intentos + 1, modo);
        } else if (_tabla->at(pos).first == "vacia") {
            return INT_MAX;
        }
    }
}

unsigned int THashCliente::numClientes() {
    return _numClientes;
}

unsigned int THashCliente::djb2(const string dni, const string modo) {
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
            return dispersionCuadratica(dni, hash, (intentos + 1), modo);
        }
    } else if (modo == "busqueda") {
        if (_tabla->at(pos).first == "disponible")
            return dispersionCuadratica(dni, hash, intentos + 1, modo);
        else if (_tabla->at(pos).first == "ocupada") {
            if (_tabla->at(pos).second->getDni() == dni)
                return pos;
            else
                return dispersionCuadratica(dni, hash, intentos + 1, modo);
        } else if (_tabla->at(pos).first == "vacia") {
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
    cout<<"Redispersión aplicada"<<endl;
}

float THashCliente::factorDeCarga() {
    return float(_numClientes) / float(_tamTabla);
}

THashCliente::~THashCliente() {
    for (int i = 0; i < _tamTabla; ++i) {
        delete _tabla->at(i).second;
    }
    delete _tabla;
}

vector<Cliente *> *THashCliente::getTodosLosClientes() {
    vector<Cliente *> *aDevolver = new vector<Cliente *>;
    for (int i = 0; i < _tamTabla; ++i) {
        if (_tabla->at(i).first == "ocupada")
            aDevolver->push_back(_tabla->at(i).second);
    }
    return aDevolver;
}

unsigned int THashCliente::getTamTabla() const {
    return _tamTabla;
}

unsigned int THashCliente::getColisiones() const {
    return _colisiones;
}

unsigned int THashCliente::getNumClientes() const {
    return _numClientes;
}
