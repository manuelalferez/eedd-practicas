cmake_minimum_required(VERSION 3.14)
project(eedd_pr1)

set(CMAKE_CXX_STANDARD 17)

add_executable(eedd_pr1
        src/main.cpp
        src/Cliente.cpp src/Cliente.h
        src/Itinerario.h src/Itinerario.cpp
        src/fecha.h src/fecha.cpp
        src/EcoCityMoto.cpp src/EcoCityMoto.h
        src/Moto.h src/Moto.cpp
        src/Utils.h src/Utils.cpp src/THashCliente.cpp src/THashCliente.h)