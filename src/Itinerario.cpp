

#include "Itinerario.h"

Itinerario::Itinerario(int _id, double _latitud_ini, double _longitud_ini, double _latitud_fin, double _longitud_fin,
                       Fecha _fecha, int _minutos) : id(_id),
                                                     inicio(_latitud_ini, _longitud_ini),
                                                     fin(_latitud_fin, _longitud_fin),
                                                     fecha(_fecha), minutos(_minutos) {}
string Itinerario::getToPrint() {
    return this->id+";"+this->inicio.latitud+";"+this->inicio.longitud+";"+this->fin.latitud+";"+
    this->fin.longitud+";"+this->fecha.verAnio()+";"+this->fecha.verMes()
}