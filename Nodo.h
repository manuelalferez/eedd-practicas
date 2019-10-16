/**
 * @file Nodo.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 15 de octubre de 2019, 9:21
 * @note Práctica 2. Implementación de una lista doblemente enlazada mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_NODO_H
#define EEDD_PR1_NODO_H

template<class T>
class Nodo {
public:
    T dato;
    Nodo *ant, *sig;
    Nodo(T _dato, Nodo *_ant, Nodo *_sig) :
            dato(_dato), ant(_ant), sig(_sig) {}

    virtual ~Nodo() {}
};


#endif //EEDD_PR1_NODO_H
