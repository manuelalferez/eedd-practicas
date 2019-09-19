/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: lidia
 *
 */

#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

/*
 coordenadas UTM formadas por latitud y longitud 
*/

struct UTM{
    double latitud;
    double longitud;
    UTM (double _lat, double _long): latitud(_lat), longitud (_long){}
};


/**
Clase Cliente
**/

class Cliente {
    string dni;
    string pass;
    string nombre;
    string direccion;
    UTM posicion;

public:
    //Constructor
    Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud):
            dni(_dni), pass(_pass), nombre(_nombre), direccion (_direccion), posicion (_latitud, _longitud){}
};


void leeClientes(string fileNameClientes){
    ifstream fe;                    //Flujo de entrada
    string linea;                   //Cada línea tiene un clienete
    int total = 0;                  //Contador de líneas o clientes

    //Variables auxiliares para almacenar los valores leídos
    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon;



    //Asociamos el flujo al fichero 
    fe.open(fileNameClientes);

    if(fe.good()){
        //Mientras no se haya llegado al final del fichero
        while(!fe.eof()){
            getline(fe, linea);     //Toma una línea del fichero
            stringstream ss;        //Stream que trabaja sobre buffer interno         

            if(linea!=""){
                ++total;
            }

            if(total>1){
                //Inicializamos el contenido de ss
                ss << linea;

                //Leemos el NIF
                getline(ss,dni,';');            //El carácter ; se lee y se elimina de ss

                //Leemos el pass
                getline(ss,pass,';');           //El caráter ; se lee y se elimina de ss

                //Leemos el nombre
                getline(ss,nombre,';');         //El caráter ; se lee y se elimina de ss

                //Leemos la dirección
                getline(ss,direccion,';');      //El caráter ; se lee y se elimina de ss

                //Leemos la latitud y longitud
                getline(ss,latitud,';');        //El caráter ; se lee y se elimina de ss
                getline(ss,longitud,';');       //El caráter ; se lee y se elimina de ss

                dlat = stod(latitud);
                dlon = stod(longitud);

                //con todos los atributos leídos, se crea el cliente
                Cliente client (dni, pass, nombre, direccion,dlat, dlon);
                cout << "leido cliente " << total << "  ";
            }
        }

        cout<<"Total de clientes en el fichero: " << total <<endl;
        fe.close(); //Cerramos el flujo de entrada
    }else{
        cerr<<"No se puede abrir el fichero"<<endl;
    }
}



int main(int argc, char** argv) {

    cout << "Comienzo de lectura de un fichero " << endl;

    leeClientes ("clientes_v2.csv");
    return 0;
}

