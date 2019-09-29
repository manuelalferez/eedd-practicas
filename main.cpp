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

#define NOMBRE_ARCHIVO "/clientes_v2.csv";

#include "Cliente.h"
#include "VDinamico.h"

void leeClientes(string fileNameClientes) {
    ifstream fe;
    string linea;
    int total = 0;

    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon;

    //Asociamos el flujo al fichero 
    fe.open(fileNameClientes);

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
                Cliente client(dni, pass, nombre, direccion, dlat, dlon);
            } //if
        } //while
        cout << "Total de clientes en el fichero: " << total << endl;
        fe.close();
    } else {
        cerr << "No se puede abrir el fichero" << endl;
    }
}

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

int main(int argc, char **argv) {
    cout << "Comienzo de lectura de un fichero" << endl;
    string dir_file = calcularDireccion();
    leeClientes(dir_file);
    return 0;
} // main

