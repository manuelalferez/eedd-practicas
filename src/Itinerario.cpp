

#include "Itinerario.h"

Itinerario::Itinerario(int _id, double _latitud_ini, double _longitud_ini, double _latitud_fin, double _longitud_fin,
                       Fecha _fecha, int _minutos, Moto* _vehiculo) : id(_id),
                                                     inicio(_latitud_ini, _longitud_ini),
                                                     fin(_latitud_fin, _longitud_fin),
                                                     fecha(_fecha), minutos(_minutos),
                                                     vehiculo(_vehiculo)
{
    vehiculo->actualizaBateria(minutos);
}

string Itinerario::getToPrint() {
    return to_string(this->id) + ";" + to_string(this->inicio.latitud) + ";" + to_string(this->inicio.longitud) + ";" + to_string(this->fin.latitud) + ";"+
    to_string(this->fin.longitud) + ";" + to_string(this->fecha.verAnio()) + ";" + to_string(this->fecha.verMes());
}