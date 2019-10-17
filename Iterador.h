/**
 * @file Iterador.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 15 de octubre de 2019, 9:21
 * @note Práctica 2. Implementación de una lista doblemente enlazada mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_ITERADOR_H
#define EEDD_PR1_ITERADOR_H

#include "Nodo.h"

template<class T>
class ListaDEnlazada; //Para resolver el problema que surje al utilizar una clase amiga

template<class T>
class Iterador {
private:
    Nodo<T> *nodo;
    friend class ListaDEnlazada<T>;
public:
    Iterador(Nodo<T> *_nodo) : nodo(_nodo) {}
    bool hayAnterior() { return nodo->ant != 0; }
    bool haySiguiente() { return nodo->sig != 0; }
    void anterior() { nodo = nodo->ant; }
    void siguiente() { nodo = nodo->sig; }
    T &dato() { return nodo->dato; }
    bool fin() { return nodo == 0;}


    Iterador<T>& operator=(const Iterador<T> &i);
};


template <class T>
Iterador<T>& Iterador<T>::operator=(const Iterador<T>& i) {
    if (this != i)
        nodo = i._nodo;
    return *this;
}

#endif //EEDD_PR1_ITERADOR_H
