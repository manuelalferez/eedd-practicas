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
    //1. Añadir a la empresa un nuevo cliente que no exista previamente con coordenadas en Jaén, rango ​(37, 3) - (38, 4)​.
    Cliente cliente("53597523W", "5359", "Abdallah", "Lopera", 37.3, 38.4, &empresaMotos);
    bool clienteNoExiste = empresaMotos.nuevoCliente(&cliente);
    //2. Localizar el cliente anterior en la empresa por su DNI y buscar una moto cercana que se pueda utilizar.
    //3. Realizar un itinerario con la moto localizada con una duración válida para la carga de batería de la moto. Al dejarla el cliente debe comprobar la carga de la moto para poner adecuadamente el estado.

    if (clienteNoExiste) {
        cout << "Cliente con DNI " << cliente.getDni() << " insertado." << endl;
        Moto *moto = cliente.buscarMotoCercana();
        cliente.agregarItinerario(moto->getPosicion(), moto);
        cliente.desbloquearMoto(*moto);
        UTM min(37, 3);
        UTM max(38, 4);
        cliente.terminarTrayecto(min, max);
        cout << "Cliente con DNI " << cliente.getDni() << " ha terminado su trayecto." << endl;
        cout << "Minutos en circulación: " << cliente.getItinerarios().begin()->getMinutos() << endl;
        cout << "Batería de la moto id(" << cliente.getItinerarios().begin()->getVehiculo()->getId() << "): "
             << cliente.getItinerarios().begin()->getVehiculo()->getPorcentajeBateria() << endl;
    } else {
        cout << "El cliente " << cliente.getDni() << " ya existe" << endl;
    }

    //4. Localizar las motos sin batería e indicar si la moto utilizada está en esa situación.
    auto motosSinBateria = empresaMotos.localizaMotosSinBateria();
    bool esta = false;
    for (auto & i : motosSinBateria) {
        if (cliente.getItinerarios().begin()->getVehiculo()->getId() == i.getId()) {
            esta = true;
            break;
        }
    }
    if (esta)
        cout << "Moto id(" << cliente.getItinerarios().begin()->getVehiculo()->getId()
             << "), está en el conjunto de motos sin baterías" << endl;
    else
        cout << "Moto id(" << cliente.getItinerarios().begin()->getVehiculo()->getId()
             << "), NO está en el conjunto de motos sin baterías" << endl;
    //5. Borrar el cliente que se insertó en el punto 1 y comprobar que efectivamente ya no existe.
    empresaMotos.eliminarCliente(cliente.getDni());
    cout << "Cliente eliminado" <<endl;

    auto estaCliente = empresaMotos.buscarCliente(cliente.getDni());
    if (!estaCliente)
        cout << "Cliente no está en la empresa" <<endl;

    return 0;
} // main

