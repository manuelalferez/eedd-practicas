/**
 * @file EcoCityMoto.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */

#ifndef EEDD_PR1_ECOCITYMOTO_H
#define EEDD_PR1_ECOCITYMOTO_H

#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>

#include "Moto.h"
#include "Utils.h"
#include "THashCliente.h"

class Moto;
class THashCliente;
class Cliente;
class EcoCityMoto {
public:
    EcoCityMoto(string direccionMotos, string direccionClientes, string direccionItinerarios="");
    Moto* localizaMotoCercana(UTM ubicacion);
    void desbloquearMoto(Moto &moto);
    Cliente* buscarCliente(string dni);
    void construirClientes(string nombreArchivoClientes);
    void construirMotos(string nombreArchivoMotos);
    void cargarItinerariosClientes(string direccionItinerarios);
    void crearItinerariosClientes();
    vector<Moto> localizaMotosSinBateria();
    virtual ~EcoCityMoto();
    bool eliminarCliente(string id);
    void guardarItinerarios();
    bool nuevoCliente(Cliente *clienteNuevo);
    THashCliente* getClientes();
private:
    unsigned int idUltimo;
    THashCliente* clientes;
    vector<Moto> motos;
};

#endif
