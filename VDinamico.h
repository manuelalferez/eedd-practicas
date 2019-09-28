/**
 * @file VDinamico.h
 * @author Manuel Alférez Ruiz y Raúl Zucar Aceituno
 * @date on 26 de septiembre de 2019, 13:05
 * @note Práctica 1. Implementación de vector dinámico mediante plantillas y operadores en C++
 */

#ifndef EEDD_PR1_VDINAMICO_H
#define EEDD_PR1_VDINAMICO_H

template<class T>
class VDinamico {
    VDinamico(unsigned _tamf = 1);
    VDinamico(const VDinamico<T> &orig);

private:
    unsigned taml, tamf;
    T *v;
};

template<class T>
VDinamico<T>::VDinamico(int _tamf):
        tamf(_tamf), taml(0), v(new T[tamf]) {
}



#endif //EEDD_PR1_VDINAMICO_H
