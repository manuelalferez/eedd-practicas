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

#define NOMBRE_ARCHIVO "/clientes_v2.csv"
#define NUM_MOSTRAR 6

#include "Cliente.h"
#include "VDinamico.h"

void leeClientes(string _fileNameClientes, VDinamico<Cliente> &_clientes) {
    ifstream fe;
    string linea;
    int total = 0;

    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon;

    //Asociamos el flujo al fichero 
    fe.open(_fileNameClientes);

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
                Cliente cliente(dni, pass, nombre, direccion, dlat, dlon);
                _clientes.insertar(cliente, UINT_MAX);
            } //if
        } //while
        cout << "Total de clientes en el fichero: " << total - 1 << endl;
        fe.close();
    } else {
        cerr << "No se puede abrir el fichero" << endl;
    }
} // leeClientes()

/**
 * @brief Calcula la dirección del archivo especificado en la macro-variable
 *
 * @note Funcionamiento. Calculamos el path del directorio de trabajo (pwd)
 *       Dicho path está ubicado en el cmake. Eliminamos la última entrada del path y nos
 *       ubicamos en /eedd-pr1.
 *       Después añadimos el nombre del archivo de datos.
 * @return direccion Contiene la ruta hasta el archivo de datos
 */
string calcularDireccion() {
    string direccion = getenv("PWD");
    direccion = direccion.substr(0, direccion.find_last_of("/"));
    direccion += NOMBRE_ARCHIVO;
    return direccion;
} // calcularDireccion()

void imprimirClientes(VDinamico<Cliente> _clientes, int _num_pos = UINT_MAX) {
    if (_num_pos == UINT_MAX) _num_pos = _clientes.tam();
    if (_num_pos < 0 || _num_pos > _clientes.tam()) {
        throw out_of_range("[main:imprimirClientes]: Posición fuera de rango");
    } else {
        for (int i = 0; i < _num_pos; i++) {
            cout << _clientes.lee(i).imprimir() << endl;
        }
    }
} //imprimirClientes()

int main(int argc, char **argv) {
    cout << "Comienzo de lectura de un fichero" << endl;
    string dir_file = calcularDireccion();

    //Instanciación del vector de clientes
    VDinamico<Cliente> clientes;
    leeClientes(dir_file, clientes);
    cout << "\nClientes: " << endl;
    imprimirClientes(clientes, NUM_MOSTRAR);
    cout << "... " << endl;

    // Ordenación de los clientes
    VDinamico<Cliente> clientes_ordenados = clientes;
    clientes_ordenados.ordenar();
    cout << "\nClientes ordenados: " << endl;
    imprimirClientes(clientes_ordenados, NUM_MOSTRAR);
    cout << "... \n" << endl;

    // Eliminar todos los clientes con un nombre dato
    Cliente cli;
    cli.setNombre("Aarika Eilles");
    cout << clientes_ordenados.eliminar(cli) << endl;
    imprimirClientes(clientes_ordenados, NUM_MOSTRAR);

    // Calcular distancia entre los clientes más alejados
    int pos_cliente_1 = 0, pos_cliente_2 = 0;
    double mayor_distancia_clientes = -INFINITY;

    for (int i = 0; i < clientes_ordenados.tam() - 1; i++)
        for (int j = i + 1; j < clientes_ordenados.tam(); j++) {
            if (i != j) {
                Cliente c1 = clientes_ordenados.lee(i);
                Cliente c2 = clientes_ordenados.lee(j);
                double distancia = c1.calculaDistancia(c2);
                if (mayor_distancia_clientes < distancia) {
                    mayor_distancia_clientes = distancia;
                    pos_cliente_1 = i;
                    pos_cliente_2 = j;
                }
            }
        }
    cout << "\nClientes con mayor distancia: " << endl;
    cout << clientes_ordenados.lee(pos_cliente_1).getNombre() + " - "
            + clientes_ordenados.lee(pos_cliente_2).getNombre() + "| Distancia: " + to_string(mayor_distancia_clientes)
         << endl;

    return 0;
} // main

