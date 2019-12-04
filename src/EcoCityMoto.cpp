/**
 * @file EcoCityMoto.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */

#include "EcoCityMoto.h"

EcoCityMoto::EcoCityMoto(string direccionMotos, string direccionClientes, string direccionItinerario) :
        idUltimo(0), motos() {
    clientes = new THashCliente(20000, "doble");
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
                Cliente *cliente = new Cliente(dni, pass, nombre, direccion, dlat, dlon, this);
                this->clientes->insertar(cliente->getDni(), cliente);
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
                auto it = motos.end();
                motos.insert(it, moto);
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
    vector<Cliente *> *todosClientes = clientes->getTodosLosClientes();
    string paraImprimir, lineaImprimir;
    for (int i = 0; i < todosClientes->size(); ++i) {
        auto itList = todosClientes->at(i)->getItinerarios().begin();
        while (itList != todosClientes->at(i)->getItinerarios().end()) {
            lineaImprimir += itList->getToPrint();
            lineaImprimir = todosClientes->at(i)->getDni() + ";" + lineaImprimir + "\n";
            paraImprimir += lineaImprimir;
            lineaImprimir = "";
            itList++;
        }
    }
    ofstream fs("../itinerarios.txt");

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

bool EcoCityMoto::eliminarCliente(string id) {
    return clientes->borrar(id);
}


Cliente *EcoCityMoto::buscarCliente(string dni) {
    Cliente *abuscar;
    bool encontrado = this->clientes->buscar(dni, abuscar);
    return encontrado ? abuscar : NULL;
}

void EcoCityMoto::desbloquearMoto(Moto &moto) {
    for (auto &i : motos) {
        if (i.getId() == moto.getId()) {
            i.seDesactiva();
            break;
        }
    }
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
    string camposLeidos[numCampos];
    // inicioLat, inicioLon, finLat, finLon
    double camposPosicionesUTM[numPosicionesUTM];
    //anio, mes, dia, hora, minuto
    int camposFecha[numCamposFecha];

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
            ss << linea;
            string camLei;
            //El carácter ; se lee y se elimina de ss
            for (int i = 0; i < numCampos; i++) {
                getline(ss, camposLeidos[i], ';');
                camLei += camposLeidos[i];
            }
            int i = 2, j = 0;
            while (j < numPosicionesUTM) {
                camposPosicionesUTM[j] = stod(camposLeidos[i]);
                i++;
                j++;
            }
            i = 6;
            j = 0;
            while (j < numCamposFecha) {
                camposFecha[j] = stoi(camposLeidos[i], nullptr, 10);
                i++;
                j++;
            }
            Fecha fecha(camposFecha[2], camposFecha[1], camposFecha[0], camposFecha[3],
                        camposFecha[4]);

            Itinerario itinerario(stoi(camposLeidos[posId], nullptr, 10), camposPosicionesUTM[posIniLat],
                                  camposPosicionesUTM[posIniLon], camposPosicionesUTM[posFinLat],
                                  camposPosicionesUTM[posFinLon],
                                  fecha, stoi(camposLeidos[posMinutosMov], nullptr, 10), nullptr);
            if (camposLeidos[posDni].empty()) continue;
            buscarCliente(camposLeidos[posDni])->addItinerario(itinerario);
        } //while
        cout << "Total de itinerarios en el fichero: " << total - 1 << endl;
        fe.close();
    } else {
        cerr << "No se puede abrir el fichero itinerarios" << endl;
    }
}

void EcoCityMoto::crearItinerariosClientes() {
    vector<Cliente *> *todoCliente = clientes->getTodosLosClientes();
    for (int i = 0; i < todoCliente->size(); ++i)
        todoCliente->at(i)->crearItinerarios();

}

vector<Moto> EcoCityMoto::localizaMotosSinBateria() {
    vector<Moto> motosSinBateria;
    for (auto &moto : motos)
        if (moto.getEstatus() == sinBateria)
            motosSinBateria.push_back(moto);
    return motosSinBateria;
}

bool EcoCityMoto::nuevoCliente(Cliente *clienteNuevo) {
    return clientes->insertar(clienteNuevo->getDni(), clienteNuevo);;
}

THashCliente* EcoCityMoto::getClientes() {
    return clientes;
}