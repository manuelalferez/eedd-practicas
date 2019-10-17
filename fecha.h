/***************************************************************************
 *   Copyright (C) 2006 by Antonio J. Rueda   *
 *   ajrueda@coppino   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef EEDD_PR1_FECHA_H
#define EEDD_PR1_FECHA_H

/**
@author Antonio J. Rueda
*/

#include <string>

using namespace std;

class ErrorFechaIncorrecta {
};

/** @brief Clases sencilla para representar fechas y horas */
class Fecha {
    /** Fecha y hora */
    unsigned dia, mes, anio, hora, min;
    /** Dias por mes */
    static const unsigned diasMes[12];

    void comprobarFecha(unsigned aDia, unsigned aMes, unsigned aAnio, unsigned aHora, unsigned aMin) const;
    void leerTiempo(const tm &t);
    void escribirTiempo(tm &t);

public:
    /** Crea una fecha con la hora actual */
    Fecha();
    /** Crea una fecha concreta. Devuelve una excepci�n ErrorFechaIncorrecta si la fecha introducida no es correcta */
    Fecha(unsigned aDia, unsigned aMes, unsigned aAnio, unsigned aHora = 0, unsigned aMin = 0);
    /** Constructor copia */
    Fecha(const Fecha &f) :
            dia(f.dia), mes(f.mes), anio(f.anio), hora(f.hora), min(f.min) {}

    void asignarDia(unsigned aDia, unsigned aMes, unsigned aAnio);
    void asignarHora(unsigned aHora, unsigned aMin);

    unsigned verHora() const { return hora; }
    unsigned verMin() const { return min; }
    unsigned verDia() const { return dia; }
    unsigned verMes() const { return mes; }
    unsigned verAnio() const { return anio; }

    string cadenaDia() const;
    string cadenaHora() const;
    string cadena() const {
        return cadenaDia() + " " + cadenaHora();
    }

    bool mismoDia(const Fecha &f) const {
        return dia == f.dia && mes == f.mes && anio == f.anio;
    }
    bool operator<(const Fecha &f);
    Fecha &operator=(const Fecha &f);

    void anadirMin(int numMin);
    void anadirHoras(int numHoras);
    void anadirDias(int numDias);
    void anadirMeses(int numMeses);
    void anadirAnios(int numAnios);

    ~Fecha();
};

ostream &operator<<(ostream &os, const Fecha &f);

#endif //EEDD_PR1_FECHA_H
