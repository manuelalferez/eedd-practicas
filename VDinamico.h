/**
 * @file VDinamico.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_VDINAMICO_H
#define EEDD_PR1_VDINAMICO_H

#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

template<class T>
class VDinamico {
    VDinamico(int _tamf = 1);
    VDinamico(unsigned _tamf);
    VDinamico(const VDinamico<T> &orig);
    VDinamico(const VDinamico<T> &orig, unsigned inicio, unsigned num);

    virtual ~VDinamico() {
        delete[] v;
    }

    T &operator=(const VDinamico<T> &orig);
    T &operator[](unsigned pos);
    void insertar(const T &dato, unsigned pos = UINT_MAX);
    T borrar(unsigned pos = UINT_MAX);
    void ordenar() { sort(v, v + taml); };
    int busquedaBin(T &dato);
    unsigned tam() { return this->taml; }
private:
    unsigned taml, tamf;
    T *v;
};

template<class T>
VDinamico<T>::VDinamico(int _tamf):
        tamf(_tamf), taml(0), v(new T[tamf]) {
}

template<class T>
VDinamico<T>::VDinamico(unsigned _tamf): taml(0) {
    for (int i = 0; tamf < _tamf; i++)
        tamf = pow(2, i);
    v = new T[tamf];
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig):
        taml(orig.taml),
        tamf(orig.tamf),
        v(new T[tamf]) {
    for (int i = 0; i < tamf; i++) {
        v[i] = orig.v[i];
    }
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig, unsigned inicio, unsigned num):
        v(new T[tamf = num]), taml(0) {
    for (int i = inicio; i < inicio + num; i++) {
        v[i] = orig.v[i];
        taml++;
    }
}

template<class T>
T &VDinamico<T>::operator=(const VDinamico<T> &orig) {
    if (this->v != orig.v) {
        delete[]v;
        v = new T[tamf = orig.tamf];
        taml = orig.taml;
        for (int i = 0; i < tamf; i++)
            v[i] = orig.v[i];
        return *v;
    }
}

template<class T>
T &VDinamico<T>::operator[](unsigned pos) {
    if (pos > tamf || pos < 0)
        throw out_of_range("[VDinamico<T>::operator[]: Posición fuera de rango");
    return *v;
}

template<class T>
void VDinamico<T>::insertar(const T &dato, unsigned int pos) {
    // Posición fuera de rango
    if (pos >= tamf || pos < 0) {
        throw out_of_range("[VDinamico<T>::insertar]: Fuera de rango.");
    } else {
        // Vector lleno
        if (taml == tamf) {
            T *vaux;
            vaux = new T[tamf = tamf * 2];
            for (int i = 0; i < taml; i++)
                vaux[i] = v[i];
            delete[] v;
            v = vaux;
        }

        // Inserción por el medio
        if (pos != UINT_MAX) {
            // Abrimos hueco e insertamos el dato
            for (int i = taml - 1; i > pos; i--)
                v[i] = v[i - 1];
            v[pos] = dato;
        } else v[taml++] = dato;
    }
} // insertar()

template<class T>
T VDinamico<T>::borrar(unsigned int pos) {
    // Posición fuera de rango
    if (pos >= tamf || pos < 0) {
        throw out_of_range("[VDinamico<T>::borrar]: Fuera de rango.");
    } else {
        // Reducción a la mitad si taml*3<tamf
        if (taml * 3 < tamf) {
            T *vaux;
            vaux = new T[tamf = tamf / 2];
            for (int i = 0; i < taml; i++)
                vaux[i] = v[i];
            delete[] v;
            v = vaux;
        }

        // Eliminamos por el medio
        if (pos != UINT_MAX) {
            T val = v[pos];
            // Sobreescribimos
            for (int i = pos; i < taml; i++)
                v[i] = v[i + 1];
            taml--;
            return val;
        } else return v[--taml];
    }
} // borrar()

template<class T>
int VDinamico<T>::busquedaBin(T &dato) {
    int inf = 0;
    int sup = this->taml - 1;
    int mid;

    while (inf <= sup) {
        mid = (inf + sup) / 2;
        if (v[mid] == dato) return mid;
        else if (v[mid] < dato) inf = mid + 1;
        else sup = mid - 1;
    }
    return -1;
} // busquedaBin()

#endif //EEDD_PR1_VDINAMICO_H
