/**
 * @file AVL.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 30 de octubre de 2019, 6:23
 * @note Práctica 3. Arboles AVL
 */

#ifndef EEDD_PR1_AVL_H
#define EEDD_PR1_AVL_H

#include <iostream>

using namespace std;

template<typename T>
class NodoA {
public:
    NodoA(T &ele) :
            izq(0),
            der(0),
            bal(0),
            dato(ele) {};
    NodoA(const NodoA &orig) :
            izq(orig.izq),
            der(orig.der),
            dato(orig.dato),
            bal(orig.bal) {};
    virtual ~NodoA(){};
    NodoA<T> *izq;
    NodoA<T> *der;
    T dato;
    char bal;
};

template<class T>
class AVL {
public:
    AVL();
    AVL(const AVL<T> &orig);
    AVL &operator=(const AVL<T> &orig);
    virtual ~AVL() { destruirArbol(raiz); }

    int altura(NodoA<T> *&nodo);
    int alturaAVL() { return altura(raiz); }
    bool inserta(T &dato) { return inserta(raiz, dato); }
    bool busca(T &dato, T &result);
    T *busca(T &dato);
    bool buscaIt(T &dato, T &result);
    unsigned int numElmentos() { return numElementos; }
    void recorreInorden() { inorden(raiz, 0); }
private:
    NodoA<T> *raiz;
    unsigned int numElementos;

    void copiaArbol(NodoA<T> *orig);
    void destruirArbol(NodoA<T> *nodo);
    void rotDer(NodoA<T> *&nodo);
    void rotIzq(NodoA<T> *&nodo);
    int inserta(NodoA<T> *&nodo, T &dato);
    void inorden(NodoA<T> *nodo, int nivel);
    NodoA<T> *busca(T &ele, NodoA<T> *p);

};

template<typename T>
AVL<T>::AVL():
        raiz(0),
        numElementos(0) {}

template<typename T>
AVL<T>::AVL(const AVL<T> &orig) :
        raiz(0), numElementos(orig->numElementos) {
    if (orig.raiz) copiaArbol(orig.raiz);
}

template<typename T>
void AVL<T>::copiaArbol(NodoA<T> *orig) {
    if (orig) {
        this->inserta(orig->dato);
        if (orig->izq)
            copiaArbol(orig->izq);
        if (orig->der)
            copiaArbol(orig->der);
    }
}

template<typename T>
AVL<T> &AVL<T>::operator=(const AVL<T> &orig) {
    if (this != &orig) {
        destruirArbol(this->raiz);
        numElementos = orig.numElementos;
        copiaArbol(orig.raiz);
    }
    return *this;
}

template<typename T>
void AVL<T>::destruirArbol(NodoA<T> *nodo) {
    if (nodo) {
        NodoA<T> *p = nodo;
        if (p->izq) {
            destruirArbol(p->izq);
            p->izq = 0;
        }
        if (p->der) {
            destruirArbol(p->der);
            p->der = 0;
        }
        if (p->dato == raiz->dato) {
            delete raiz;
            raiz = 0;
        } else {
            delete p;
            p = 0;
        }
    }
}

template<typename T>
int AVL<T>::inserta(NodoA<T> *&nodo, T &dato) {
    NodoA<T> *p = nodo;
    int deltaH = 0;

    if (!p) {
        p = new NodoA<T>(dato); //La recursion llega a una hoja
        nodo = p;
        deltaH = 1;
        numElementos++;
    } else if (dato > p->dato) {
        if (inserta(p->der, dato)) {
            p->bal--;
            if (p->bal == -1) deltaH = 1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDer(p->der); //Rotacion doble: caso 3
                rotIzq(nodo); //Rotacion simple: caso 4
            }
        }
    } else if (dato < p->dato) {
        if (inserta(p->izq, dato)) {
            p->bal++;
            if (p->bal == 1) deltaH = 1;
            else if (p->bal == 2) {
                if (p->izq->bal == -1) rotIzq(p->izq); //Rotacion doble: caso 2
                rotDer(nodo); //Rotacion simple: caso 1
            }
        }
    }
    return deltaH;
}

template<typename T>
void AVL<T>::rotDer(NodoA<T> *&nodo) {
    NodoA<T> *q = nodo;
    NodoA<T> *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if (q->bal < 0) l->bal -= -q->bal;
}

template<typename T>
void AVL<T>::rotIzq(NodoA<T> *&nodo) {
    NodoA<T> *q = nodo;
    NodoA<T> *r;
    nodo = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if (q->bal > 0) r->bal += q->bal;
}

template<typename T>
void AVL<T>::inorden(NodoA<T> *nodo, int nivel) {
    if (nodo) {
        inorden(nodo->izq, nivel + 1);
        std::cout << "Procesando nodo " << nodo->dato.mostrar();
        std::cout << " en el nivel " << nivel << std::endl;
        inorden(nodo->der, nivel + 1);
    }
}

template<typename T>
bool AVL<T>::busca(T &dato, T &result) {
    NodoA<T> *p = busca(dato, raiz);
    if (p) {
        result = p->dato;
        return true;
    }
    return false;
}


template<typename T>
NodoA<T> *AVL<T>::busca(T &ele, NodoA<T> *p) {
    if (!p)
        return 0;
    else if (ele < p->dato)
        return busca(ele, p->izq);
    else if (ele > p->dato)
        return busca(ele, p->der);
    else return p;
}

template<typename T>
bool AVL<T>::buscaIt(T &dato, T &result) {
    NodoA<T> *nodoActual = this->raiz;
    while (nodoActual != nullptr) {
        if (nodoActual->dato == dato) {
            result = nodoActual->dato;
            return true;
        } else if (dato < nodoActual->dato)
            nodoActual = nodoActual->izq;
        else
            nodoActual = nodoActual->der;
    }
    return false;
}

template<typename T>
int AVL<T>::altura(NodoA<T> *&nodo) {
    if (nodo) {
        int alturaTotal = 0;
        int alturaHijo;
        NodoA<T> *p = nodo;
        if (p->izq) {
            alturaHijo = altura(p->izq);
            if (alturaTotal < alturaHijo) alturaTotal = alturaHijo;
        }
        if (p->der) {
            alturaHijo = altura(p->der);
            if (alturaTotal < alturaHijo) alturaTotal = alturaHijo;
        }
        if (p->dato == raiz->dato) return alturaTotal;
        else return ++alturaTotal;
    }
    return 0;
}

template<typename T>
T *AVL<T>::busca(T &dato) {
    NodoA<T> *p = busca(dato, raiz);
    if (p != nullptr) return &p->dato;
    else return 0;
}

#endif //EEDD_PR1_AVL_H
