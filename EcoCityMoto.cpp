/**
 * @file EcoCityMoto.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */

#include <fstream>
#include "EcoCityMoto.h"

EcoCityMoto::EcoCityMoto(string direccionMotos, string direccionClientes) : idUltimo(0), motos(VDinamico<Moto>()),
                                                                            clientes(AVL<Cliente>()) {
    this->construirClientes(direccionClientes);
    this->construirMotos(direccionMotos);
}

void EcoCityMoto::construirClientes(string direccionArchivoClientes) {
    ifstream fe;
    string linea;
    int total = 0;

    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon;

    //Asociamos el flujo al fichero
    fe.open(direccionArchivoClientes);

    if (fe.good()) {
        //Mientras no se haya llegado al final del fichero
        while (!fe.eof()) {
            getline(fe, linea);
            stringstream ss;        //Stream que trabaja sobre buffer interno

            if (linea != "") {
                ++total;
            }
            if (total > 1) {
                ss << linea;
                //El carácter ; se lee y se elimina de ss
                getline(ss, dni, ';');
                getline(ss, pass, ';');
                getline(ss, nombre, ';');
                getline(ss, direccion, ';');
                getline(ss, latitud, ';');
                getline(ss, longitud, ';');
                replace(latitud.begin(), latitud.end(), ',', '.');
                replace(longitud.begin(), longitud.end(), ',', '.');
                dlat = stold(latitud);
                dlon = stold(longitud);
                Cliente cliente(dni, pass, nombre, direccion, dlat, dlon, this);
                clientes.inserta(cliente);
            } //if
        } //while
        cout << "Total de clientes en el fichero: " << total - 1 << endl;
        fe.close();
    } else {
        cerr << "No se puede abrir el fichero" << endl;
    }
}

void EcoCityMoto::construirMotos(string direccionArchivoMotos) {
    ifstream fe;
    string linea;
    int total = 0;

    string matricula, estado, latitud, longitud;
    double dlat, dlon;
    int iEstado;

    //Asociamos el flujo al fichero
    fe.open(direccionArchivoMotos);

    if (fe.good()) {
        //Mientras no se haya llegado al final del fichero
        while (!fe.eof()) {
            getline(fe, linea);
            stringstream ss;        //Stream que trabaja sobre buffer interno

            if (linea != "") {
                ++total;
            }
            if (total > 1) {
                ss << linea;
                //El carácter ; se lee y se elimina de ss
                getline(ss, matricula, ';');
                getline(ss, estado, ';');
                getline(ss, latitud, ';');
                getline(ss, longitud, ';');
                replace(latitud.begin(), latitud.end(), ',', '.');
                replace(longitud.begin(), longitud.end(), ',', '.');
                dlat = stold(latitud);
                dlon = stold(longitud);
                stringstream estadoConvertido(estado);
                estadoConvertido >> iEstado;
                Moto moto(matricula, iEstado, dlat, dlon);
                motos.insertar(moto, UINT_MAX);
            } //if
        } //while
        cout << "Total de motos en el fichero: " << total - 1 << endl;
        fe.close();
    } else {
        cerr << "No se puede abrir el fichero" << endl;
    }
}

EcoCityMoto::~EcoCityMoto() {
}

Moto *EcoCityMoto::localizaMotoCercana(UTM ubicacion) {
    int posMejorMoto = 0;
    int distanciaMejor = INT_MAX;
    for (int i = 0; i < motos.tam(); i++) {
        if (motos.lee(i)->estaDisponible()) {
            int distanciaActual = utils::calcularDistancia(motos.lee(i)->getPosicion(), ubicacion);
            if (distanciaActual < distanciaMejor) {
                posMejorMoto = i;
                distanciaMejor = distanciaActual;
            }
        }
    }
    return motos.lee(posMejorMoto);
}

Cliente *EcoCityMoto::buscarCliente(string dni) {
    Cliente *cli = new Cliente();
    cli->setDni(dni);
    return clientes.busca(*cli);

}

void EcoCityMoto::desbloquearMoto(Moto &moto) {
    for (int i = 0; i < motos.tam(); i++) {
        if (motos.lee(i)->getId() == moto.getId()) {
            motos.lee(i)->seDesactiva();
            break;
        }
    }
}

void EcoCityMoto::mostrarClientesInorden() {
    clientes.recorreInorden();
}

void EcoCityMoto::mostrarAltura() {
    cout << "La altura del AVL es: " + to_string(clientes.alturaAVL()) << endl;
}