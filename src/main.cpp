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


    EcoCityMoto empresaMotos(direccionArchivoMotos, direccionArchivoClientes, direccionArchivoItinerarios);
    THashCliente* tabla_clientes = empresaMotos.getClientes();
    vector<Cliente*>* mis_clientes = tabla_clientes->getTodosLosClientes();

    for(int i=0;i<5;i++){
        cout<<mis_clientes->at(i)->getDni()<<endl;
    }
    string aBorrar = "46860472R";
    tabla_clientes->borrar(aBorrar);

    cout << "Numero total de elementos: " << tabla_clientes->getNumClientes() << endl;
    cout << "Numero total de colisiones: " << tabla_clientes->getColisiones() << endl;
    cout << "Maximo de colisiones: " << tabla_clientes->maxColisiones() << endl;
    cout << "Promedio de colisiones: " << tabla_clientes->promedioColisiones() << endl;
    cout << "Factor de carga: " << tabla_clientes->factorDeCarga() << endl;

    return 0;
} // main

