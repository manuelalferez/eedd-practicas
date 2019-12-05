/**
 * @file main.cpp
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */

#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>

#define NUM_MOSTRAR 5

#include "EcoCityMoto.h"

class Moto;

/**
 * @brief Calcula la dirección del archivo
 *
 * @note Funcionamiento. Calculamos el path del directorio de trabajo (pwd)
 *       Dicho path está ubicado en el cmake. Eliminamos la última entrada del path y nos
 *       ubicamos en /eedd-pr1.
 *       Después añadimos el nombre del archivo de datos.
 * @return direccion Contiene la ruta hasta el archivo de datos
 */
string calcularDireccion(string nombreArchivo) {
    string direccion = getenv("PWD");
    direccion = direccion.substr(0, direccion.find_last_of("/"));
    direccion += nombreArchivo;
    return direccion;
} // calcularDireccion()

void imprimirClientes(vector<Cliente> _clientes, int _num_pos = UINT_MAX) {
    if (_num_pos == UINT_MAX) _num_pos = _clientes.size();
    if (_num_pos < 0 || _num_pos > _clientes.size()) {
        throw out_of_range("[main:imprimirClientes]: Posición fuera de rango");
    } else {
        for (int i = 0; i < _num_pos; i++) {
            cout << _clientes[i].imprimir() << endl;
        }
    }
} //imprimirClientes()

int main(int argc, char **argv) {
    cout << "Comienzo de lectura de un fichero" << endl;
    string direccionArchivoClientes = calcularDireccion("/clientes_v2.csv");
    string direccionArchivoMotos = calcularDireccion("/motos.txt");
    string direccionArchivoItinerarios = calcularDireccion("/itinerarios.txt");

    std::ifstream archivoItinerarios(direccionArchivoItinerarios);
    if (archivoItinerarios.peek() == std::ifstream::traits_type::eof()) {
        // Empty File
        direccionArchivoItinerarios = "";
    }

    EcoCityMoto *empresaMotos = new EcoCityMoto(direccionArchivoMotos, direccionArchivoClientes,
                                                direccionArchivoItinerarios);
    THashCliente *tabla_clientes = empresaMotos->getClientes();
    vector<Cliente *> *mis_clientes = tabla_clientes->getTodosLosClientes();

    // Programa de prueba 1
    cout << endl;
    cout << "------------------------------" << endl;
    cout << "Programa de prueba 1" << endl;
    cout << "------------------------------" << endl;
    cout << "Numero total de elementos: " << tabla_clientes->getNumClientes() << endl;
    cout << "Numero total de colisiones: " << tabla_clientes->getColisiones() << endl;
    cout << "Maximo de colisiones: " << tabla_clientes->maxColisiones() << endl;
    cout << "Promedio de colisiones: " << tabla_clientes->promedioColisiones() << endl;
    cout << "Factor de carga: " << tabla_clientes->factorDeCarga() << endl;
    cout << endl;

    // Programa de prueba 2
    cout << "------------------------------" << endl;
    cout << "Programa de prueba 2" << endl;
    cout << "------------------------------" << endl;
    Cliente *nuevoCliente = new Cliente("55956710S", "8392h3", "Manuel", "Jaén", 37.3, 38.4, empresaMotos);
    int colisionesAntes = tabla_clientes->getColisiones();
    empresaMotos->nuevoCliente(nuevoCliente);
    int colisionesDespues = tabla_clientes->getColisiones();
    cout << "Colisiones: " << colisionesDespues - colisionesAntes << endl;
    cout << "Cliente insertado correctamente" << endl;
    cout << endl;

    cout << "Localizando cliente..." << endl;
    nuevoCliente = empresaMotos->buscarCliente(nuevoCliente->getDni());
    cout << "Cliente localizado: " << nuevoCliente->imprimir() << endl;
    cout << endl;

    cout << "Moto más cercana: " << endl;
    Moto *motoMasCercana = empresaMotos->buscarCliente(nuevoCliente->getDni())->buscarMotoCercana();
    cout << motoMasCercana->imprimir() << endl;

    cout << endl;
    bool estaEliminado = empresaMotos->eliminarCliente(nuevoCliente->getDni());
    if (estaEliminado)
        cout << "Cliente eliminado" << endl;
    else
        cout << "El cliente no se pudo eliminar" << endl;

    cout << endl;
    cout << "Buscamos al cliente eliminado..." << endl;
    Cliente *buscado = empresaMotos->buscarCliente(nuevoCliente->getDni());
    if (buscado == nullptr)
        cout << "Cliente no encontrado" << endl;
    else
        cout << "Cliente encontrado" << endl;

    cout << endl;
    cout << "Factor de carga antes: " << tabla_clientes->factorDeCarga() << endl;
    for (int i = 0; i < 1000; i++) {
        empresaMotos->eliminarCliente(mis_clientes->at(i)->getDni());
    }
    cout << "Factor de carga después: " << tabla_clientes->factorDeCarga() << endl;

    return 0;
} // main

