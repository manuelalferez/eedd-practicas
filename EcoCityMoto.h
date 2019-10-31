/**
 * @file EcoCityMoto.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */

#ifndef EEDD_PR1_ECOCITYMOTO_H
#define EEDD_PR1_ECOCITYMOTO_H

#include "AVL.h"
#include "VDinamico.h"
#include "Moto.h"

class Moto;
class EcoCityMoto {
public:
    EcoCityMoto(string direccionMotos, string direccionClientes);
    Moto* localizaMotoCercana(UTM ubicacion);
    void desbloquearMoto(Moto &moto);
    Cliente* buscarCliente(string dni);
    void construirClientes(string nombreArchivoClientes);
    void construirMotos(string nombreArchivoMotos);
    void mostrarClientesInorden();
    void mostrarAltura();
    virtual ~EcoCityMoto();

private:
    unsigned int idUltimo;
    AVL<Cliente> clientes;
    VDinamico<Moto> motos;
};


#endif //EEDD_PR1_ECOCITYMOTO_H
