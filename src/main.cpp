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

#define NUM_MOSTRAR 5

#include "VDinamico.h"
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

void imprimirClientes(VDinamico<Cliente> _clientes, int _num_pos = UINT_MAX) {
    if (_num_pos == UINT_MAX) _num_pos = _clientes.tam();
    if (_num_pos < 0 || _num_pos > _clientes.tam()) {
        throw out_of_range("[main:imprimirClientes]: Posición fuera de rango");
    } else {
        for (int i = 0; i < _num_pos; i++) {
            cout << _clientes.lee(i)->imprimir() << endl;
        }
    }
} //imprimirClientes()

int main(int argc, char **argv) {
    cout << "Comienzo de lectura de un fichero" << endl;
    string direccionArchivoClientes = calcularDireccion("/clientes_v2.csv");
    string direccionArchivoMotos = calcularDireccion("/motos.txt");


    // Crear un árbol AVL con los clientes de la base de datos proporcionada en la práctica 1 (clientes_v2.csv).
    // La clave ahora es el dni.
    // Cargar las motos usando el fichero adjunto (motos.csv)
    EcoCityMoto empresaMotos(direccionArchivoMotos, direccionArchivoClientes);

    // Mostrar el árbol AVL en inorden.
    empresaMotos.mostrarClientesInorden();

    // Mostrar la altura del árbol AVL
    empresaMotos.mostrarAltura();

    // Buscar un cliente en el árbol dado su DNI
    Cliente *cliente = empresaMotos.buscarCliente("88642870V");
    if (cliente) {
        cout << "Cliente encontrado, nombre: " + cliente->getNombre() << endl;
    } else {
        cout << "Cliente con DNI (67462104W) no encontrado." << endl;
    }

    // Simular que ese cliente quiere desplazarse, localiza la moto más cercana y hace un
    // trayecto con un final aleatorio dentro del rango (37, 3) - (38,4) correspondiente a la zona de Jaén.
    UTM min(37, 3);
    UTM max(38, 4);
    Moto *moto = cliente->buscarMotoCercana();
    cliente->desbloquearMoto(*moto);
    cout << "Moto desbloqueada, " + cliente->getNombre() + " esta moviendose..." << endl;
    cliente->terminarTrayecto(min, max);
    cout << "Moto bloqueada" << endl;

    return 0;
} // main

