/**
 * @file EcoCityMoto.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */

#include <vector>
#include "EcoCityMoto.h"

EcoCityMoto::EcoCityMoto(string direccionMotos, string direccionClientes, string direccionItinerario) :
        idUltimo(0), motos(VDinamico<Moto>()),
        clientes(AVL<Cliente>()) {
    this->construirClientes(direccionClientes);
    this->construirMotos(direccionMotos);
    if (!direccionItinerario.empty()) this->cargarItinerariosClientes(direccionItinerario);
    else this->crearItinerariosClientes();
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
    guardarItinerarios();
}

void EcoCityMoto::guardarItinerarios() {
    auto itClientes = clientes.begin();
    string paraImprimir;
    while (itClientes != clientes.end()) {
        auto itList = itClientes->second.getItinerarios().begin();
        while (itList != itClientes->second.getItinerarios().end()) {
            paraImprimir += itList->getToPrint();
            paraImprimir = itClientes->second.getDni() + paraImprimir+"\n";
            itList++;
        }
        itClientes++;
    }
    ofstream fs("itinerarios.txt");

    // Enviamos una cadena al fichero de salida
    fs << paraImprimir;
    fs.close();
}

Moto *EcoCityMoto::localizaMotoCercana(UTM ubicacion) {
    int posMejorMoto = 0;
    int distanciaMejor = INT_MAX;
    for (int i = 0; i < motos.size(); i++) {
        if (motos[i].estaDisponible()) {
            int distanciaActual = Utils::calcularDistancia(motos[i].getPosicion(), ubicacion);
            if (distanciaActual < distanciaMejor) {
                posMejorMoto = i;
                distanciaMejor = distanciaActual;
            }
        }
    }
    return &motos[posMejorMoto];
}

bool EcoCityMoto::nuevoCliente(Cliente &cliente) {

}

bool EcoCityMoto::eliminarCliente(string id) {
    auto it = this->clientes.find(id);
    if(it != clientes.end()) {
        this->clientes.erase(it);
        return true;
    }
    return false;
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

void EcoCityMoto::cargarItinerariosClientes(string direccionItinerarios) {
    ifstream fe;
    string linea;
    int total = 0;
    enum PosicionesCamposEntrada {
        posDni, posId, posIniLat, posIniLon, posFinLat, posFinLon, posAnio,
        posMes, posDia, posHora, posMinuto, posMinutosMov
    };
    int numCampos = 12, numPosicionesUTM = 4, numCamposFecha = 5;
    // dni, id, inicioLat, inicioLon, finLat, finLon, anio, mes, dia, hora, minuto, minutos
    auto *camposLeidos = new string[numCampos];
    // inicioLat, inicioLon, finLat, finLon
    auto *camposPosicionesUTM = new double[numPosicionesUTM];
    //anio, mes, dia, hora, minuto
    int *camposFecha = new int[numCamposFecha];

    //Asociamos el flujo al fichero
    fe.open(direccionItinerarios);

    if (fe.good()) {
        //Mientras no se haya llegado al final del fichero
        while (!fe.eof()) {
            getline(fe, linea);
            stringstream ss;        //Stream que trabaja sobre buffer interno

            if (!linea.empty()) {
                ++total;
            }
            if (total > 1) {
                ss << linea;
                //El carácter ; se lee y se elimina de ss
                for (int i = 0; i < numCampos; i++) {
                    getline(ss, camposLeidos[i], ';');
                }
                int i = 2, j = 0;
                while (j < numPosicionesUTM) {
                    camposPosicionesUTM[j] = stold(camposLeidos[i]);
                    i++;
                    j++;
                }
                i = 6;
                j = 0;
                while (j < numCamposFecha) {
                    camposFecha[j] = stoi(camposLeidos[i]);
                    i++;
                    j++;
                }
                Fecha fecha(camposFecha[posDia], camposFecha[posMes], camposFecha[posAnio], camposFecha[posHora],
                            camposFecha[posMinuto]);

                Itinerario itinerario(stoi(camposLeidos[posId]), camposPosicionesUTM[posIniLat],
                                      camposPosicionesUTM[posIniLon], camposPosicionesUTM[posFinLat],
                                      camposPosicionesUTM[posFinLon],
                                      fecha, stoi(camposLeidos[posMinutosMov]));
                Cliente cliente;
                cliente.setDni(camposLeidos[posDni]);
                this->clientes.busca(cliente)->addItinerario(itinerario);
            } //if
        } //while
        cout << "Total de clientes en el fichero: " << total - 1 << endl;
        fe.close();
    } else {
        cerr << "No se puede abrir el fichero" << endl;
    }
}

void EcoCityMoto::crearItinerariosClientes() {

}

void EcoCityMoto::mostrarAltura() {
    cout << "La altura del AVL es: " + to_string(clientes.alturaAVL()) << endl;
}

vector<Moto>* EcoCityMoto::localizaMotosSinBateria() {
    vector<Moto> *motosSinBateria = new vector<Moto>;
    for (int i = 0; i < motos.size(); ++i)
        if (motos[i].getEstatus() == sinBateria)
            motosSinBateria->push_back(motos[i]);
    return motosSinBateria;

}

bool EcoCityMoto::nuevoCliente(Cliente *clienteNuevo) {
    auto clienteInsertado = this->clientes.insert(pair<string, Cliente>(clienteNuevo->getDni(), *clienteNuevo) );
    return  clienteInsertado.second;
}