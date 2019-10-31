cmake_minimum_required(VERSION 3.14)
project(eedd_pr1)

set(CMAKE_CXX_STANDARD 17)

add_executable(eedd_pr1 main.cpp Cliente.cpp Cliente.h VDinamico.h ListaDEnlazada.h Nodo.h Iterador.h Itinerario.h
        fecha.h fecha.cpp AVL.h EcoCityMoto.cpp EcoCityMoto.h Moto.h Utils.h)