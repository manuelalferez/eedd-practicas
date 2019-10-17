/**
 * @file ListaDEnlazada.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 15 de octubre de 2019, 9:21
 * @note Práctica 2. Implementación de una lista doblemente enlazada mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_LISTADENLAZADA_H
#define EEDD_PR1_LISTADENLAZADA_H

#include "Nodo.h"
#include "Iterador.h"
#include <stdexcept>

template<class T>
class ListaDEnlazada {
    Nodo<T> *cabecera, *cola;
    int tama;

public:
    ListaDEnlazada() : cabecera(0), cola(0), tama(0) {}
    ListaDEnlazada(const ListaDEnlazada<T> &orig);
    ListaDEnlazada<T> &operator=(const ListaDEnlazada<T> &orig);

    T &inicio() { return cabecera->dato; }
    T &fin() { return cola->dato; }
    Iterador<T> iterador() { return Iterador<T>(cabecera); }

    void insertaInicio(T &_dato);
    void insertarFin(T &_dato);
    void inserta(Iterador<T> _i, T &_dato);

    void borraInicio();
    void borraFinal();
    void borra(Iterador<T> &_i);

    int tam() { return this->tama; }

    ListaDEnlazada<T> &concatena(ListaDEnlazada<T> &_l);

    ~ListaDEnlazada();
};

template<class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T> &orig) {
    if (this != &orig) { //Listas distintas
        if (orig.cabecera != 0) { //Lista con contenido
            cabecera = new Nodo<T>(orig.cabecera->dato, 0, 0);
            auto i = this->cabecera;
            auto j = orig.cabecera;

            while (j->sig != 0) {
                i->sig = new Nodo<T>(j->sig->dato, i, 0);
                i = i->sig;
                j = j->sig;
            }

            if (orig.cabecera == orig.cola) cola = cabecera;
            else cola = i;
        } else cabecera = cola = 0;
        this->tama = orig.tama;
    }
}

template<class T>
ListaDEnlazada<T> &ListaDEnlazada<T>::operator=(const ListaDEnlazada<T> &orig) {
    if (this != &orig) {
        while (cabecera != cola != 0) { //Eliminamos lista
            Nodo<T> *borrado = cabecera;
            cabecera = cabecera->sig;
            delete borrado;

            if (cabecera == 0) cola = 0;
        }
        if (orig.cabecera != 0) {
            cabecera = new Nodo<T>(orig.cabecera->dato, 0, 0);
            auto i = this->cabecera;
            auto j = orig.cabecera;

            while (j->sig != 0) {
                i->sig = new Nodo<T>(j->sig->dato, i, 0);
                i = i->sig;
                j = j->sig;
            }

            if (orig.cabecera == orig.cola) cola = cabecera;
            else cola = i;
        } else cabecera = cola = 0;
        this->tama = orig.tama;
    }
    return *this;
} //operator=()

template<class T>
void ListaDEnlazada<T>::insertaInicio(T &_dato) {
    Nodo<T> *nuevo = new Nodo<T>(_dato, 0, cabecera);

    if (cola == 0) cola = nuevo;
    else cabecera->ant = nuevo;

    cabecera = nuevo;
    this->tama++;
}

template<class T>
void ListaDEnlazada<T>::insertarFin(T &_dato) {
    Nodo<T> *nuevo = new Nodo<T>(_dato, cola, 0);

    if (cabecera == 0) cabecera = nuevo;
    else cola->sig = nuevo;

    cola = nuevo;
    this->tama++;
}

template<class T>
void ListaDEnlazada<T>::inserta(Iterador<T> _i, T &_dato) {
    if (_i.nodo == cabecera) {
        Nodo<T> *nuevo = new Nodo<T>(_dato, 0, cabecera);

        if (cola == 0) cola = nuevo;
        else cabecera->ant = nuevo;

        cabecera = nuevo;
    } else if (_i.nodo == cola) {
        Nodo<T> *nuevo = new Nodo<T>(_dato, cola, 0);

        if (cabecera == 0) cabecera = nuevo;
        else cola->sig = nuevo;

        cola = nuevo;
    } else {
        Nodo<T> *nuevo = new Nodo<T>(_dato, _i.nodo->ant, _i.nodo);
        _i.nodo->ant->sig = nuevo;
        _i.nodo->ant = nuevo;
    }
    this->tama++;
} //inserta()

template<class T>
void ListaDEnlazada<T>::borraInicio() {
    if (cabecera != 0) {
        Nodo<T> *borrado = cabecera;
        cabecera = cabecera->sig;
        delete borrado;

        if (cabecera == 0) cola = 0;
        else cabecera->ant = 0;
        this->tama--;
    } else throw std::logic_error("[ListaDEnlazada<T>::borraInicio]: Lista vacía");
}

template<class T>
void ListaDEnlazada<T>::borraFinal() {
    if (cola != 0) {
        Nodo<T> *borrado = cola;
        cola = cola->ant;
        delete borrado;

        if (cola == 0) cabecera = 0;
        else cola->sig = 0;
        this->tama--;
    } else throw std::logic_error("[ListaDEnlazada<T>::borraFinal]: Lista vacía");
}

template<class T>
void ListaDEnlazada<T>::borra(Iterador<T> &_i) {
    if (_i.nodo == cabecera) {
        if (cabecera != 0) {
            Nodo<T> *borrado = cabecera;
            cabecera = cabecera->sig;
            delete borrado;

            if (cabecera == 0) cola = 0;
            else cabecera->ant = 0;
            this->tama--;
        } else throw std::logic_error("[ListaDEnlazada<T>::borra]: Lista vacía");
    } else if (_i.nodo == cola) {
        Nodo<T> *borrado = cola;
        cola = cola->ant;
        delete borrado;

        if (cola == 0) cabecera = 0;
        else cola->sig = 0;
        this->tama--;
    } else {
        Nodo<T> *borrado = _i.nodo;
        _i.nodo->ant->sig = _i.nodo->sig;
        _i.nodo->sig->ant = _i.nodo->ant;

        delete borrado;
        this->tama--;
    }
} //borra()

template<class T>
ListaDEnlazada<T> &ListaDEnlazada<T>::concatena(ListaDEnlazada<T> &_l) {
    if (_l.tama != 0) {
        auto i = _l.iterador();
        while (i != 0) {
            this->insertarFin(i.nodo->dato);
            i.siguiente();
        }
    }
    return *this;
}

template<class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    while (cabecera != cola != 0) {
        Nodo<T> *borrado = cabecera;
        cabecera = cabecera->sig;

        delete borrado;
        if (cabecera == 0)
            cola = 0;
    }
}

#endif //EEDD_PR1_LISTADENLAZADA_H
