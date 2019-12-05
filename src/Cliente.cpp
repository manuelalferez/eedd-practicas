/**
 * @file Cliente.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */


#include "Cliente.h"

UTM Cliente::coordenada_min(DBL_MAX, DBL_MAX);
UTM Cliente::coordenada_max(DBL_MIN, DBL_MIN);


Cliente::Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud,
                 EcoCityMoto *_acceso) :
        dni(_dni), pass(_pass), nombre(_nombre), direccion(_direccion), posicion(_latitud, _longitud), acceso(_acceso) {
    if (_latitud < coordenada_min.latitud) coordenada_min.latitud = _latitud;
    if (_latitud > coordenada_max.latitud) coordenada_max.latitud = _latitud;
    if (_longitud < coordenada_min.longitud) coordenada_min.longitud = _longitud;
    if (_longitud > coordenada_max.longitud) coordenada_max.longitud = _longitud;
}

bool Cliente::operator<(const Cliente &c) const {
    return this->dni < c.dni;
}
bool Cliente::operator>(const Cliente &c) const {
    return this->dni > c.dni;
}

/*
 * Compara si dos nombres de clientes son iguales
 *
 * Devuelve verdadero si son iguales y falso en caso contrario
 */
bool Cliente::operator==(const Cliente &c) const {
    stringstream ss;
    ss << this->nombre;
    string this_nombre;
    getline(ss, this_nombre, ' ');
    return this_nombre == c.nombre;
}

string Cliente::imprimir() {
    return "DNI: " + this->dni + ", Pass: " + this->pass + ", Nombre: " + this->nombre +
           ", Dirección: " + this->direccion + ", Latitud: " + to_string(this->posicion.latitud) + ", Longitud: " +
           to_string(this->posicion.longitud);
}

void Cliente::crearItinerarios() {
    int num_itinerarios = 1 + rand() % (6 - 1);
    double latitud_random_ini, longitud_random_ini, latitud_random_fin, longitud_random_fin;
    int minutos_aleatorios, dia = 0, mes, anio = 2019, hora, minuto;
    Fecha fecha;
    while (rutas.size() != num_itinerarios) {
        latitud_random_ini = (coordenada_max.latitud - coordenada_min.latitud) *
                             ((double) rand() / (double) RAND_MAX) + coordenada_min.latitud;
        longitud_random_ini = (coordenada_max.longitud - coordenada_min.longitud)
                              * ((double) rand() / (double) RAND_MAX) + coordenada_min.longitud;
        latitud_random_fin = (coordenada_max.latitud - coordenada_min.latitud) *
                             ((double) rand() / (double) RAND_MAX) + coordenada_min.latitud;
        longitud_random_fin = (coordenada_max.longitud - coordenada_min.longitud)
                              * ((double) rand() / (double) RAND_MAX) + coordenada_min.longitud;

        minutos_aleatorios = (unsigned) (1 + rand() % (121 - 1));
        mes = 1 + rand() % (13 - 1);
        hora = rand() % 24;
        minuto = 0 + rand() % 60;
        switch (mes) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                dia = 1 + rand() % (32 - 1); //Meses con 31 días
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                dia = 1 + rand() % (31 - 1); // Meses con 30 días
                break;
            case 2:
                dia = 1 + rand() % (29 - 1); // Meses con 28 días
                break;
        }
        fecha.asignarDia(dia, mes, anio);
        fecha.asignarHora(hora, minuto);
        Moto* nuevaMoto =nullptr ;
        Itinerario nuevoItinerario(rutas.size(), latitud_random_ini, longitud_random_ini, latitud_random_fin,
                                   longitud_random_fin, fecha, minutos_aleatorios, nuevaMoto);
        this->rutas.insert(this->rutas.begin(), nuevoItinerario);
    }
}

void Cliente::agregarItinerario(UTM inicio, Moto *moto) {
    double latitud_random_ini, longitud_random_ini;
    unsigned dia = 0, mes, anio = 2019, hora, minuto;
    Fecha fecha;
    mes = 1 + rand() % (13 - 1);
    hora = rand() % 24;
    minuto = 0 + rand() % 60;
    switch (mes) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            dia = 1 + rand() % (32 - 1); //Meses con 31 días
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            dia = 1 + rand() % (31 - 1); // Meses con 30 días
            break;
        case 2:
            dia = 1 + rand() % (29 - 1); // Meses con 28 días
            break;
    }
    fecha.asignarDia(dia, mes, anio);
    fecha.asignarHora(hora, minuto);
    Itinerario nuevoItinerario(rutas.size(), inicio.latitud, inicio.longitud, 0,
                               0, fecha, 0, moto);
    this->rutas.insert(this->rutas.begin(), nuevoItinerario);
}

UTM Cliente::getUTM(UTM min, UTM max) {
    double latitud = min.latitud + rand() % (int) (max.latitud - min.latitud);
    double longitud = min.longitud + rand() % (int) (max.longitud - min.longitud);
    UTM nuevoUTM(latitud, longitud);
    return nuevoUTM;
}

Moto *Cliente::buscarMotoCercana() {
    Moto *aUtilizar = this->acceso->localizaMotoCercana(this->posicion);
    aUtilizar->seActiva(*this);
    return aUtilizar;
}

void Cliente::desbloquearMoto(Moto &moto) {
    this->acceso->desbloquearMoto(moto);
}

void Cliente::terminarTrayecto(UTM min, UTM max) {
    auto ultimoItinerario = this->rutas.begin();
    UTM posicionFinal = this->getUTM(min, max);
    ultimoItinerario->setFin(posicionFinal);
    this->posicion = posicionFinal;
    ultimoItinerario->getVehiculo()->setPosicion(posicionFinal);
    desbloquearMoto(*ultimoItinerario->getVehiculo());
    simularMovimiento();
    ultimoItinerario->getVehiculo()->actualizaBateria(ultimoItinerario->getMinutos());
}

void Cliente::simularMovimiento() {
    auto ultimoItinerario = this->rutas.begin();
    int minutos = 1 + rand() % (int)(ultimoItinerario->getVehiculo()->getPorcentajeBateria() - 1);
    ultimoItinerario->setMinutos(minutos);
}

void Cliente::addItinerario(Itinerario &itinerario) {
    this->rutas.insert(this->rutas.begin(),itinerario);
}