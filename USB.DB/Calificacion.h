///
/// Calificacion
///

#pragma once

#include "Codigo.h"

#include <string>
#include <vector>

class Calificacion {
public:
    Calificacion(Codigo carnet, int year, int trimestre, Codigo asignatura, int nota);

    ~Calificacion() throw();

    std::string str() const;
    std::string json() const;

    Codigo carnet() const {
        return carnet_;
    }

    int year() const {
        return year_;
    }

    int trimestre() const {
        return trimestre_;
    }

    Codigo asignatura() const {
        return asignatura_;
    }

    int nota() const {
        return nota_;
    }

    // La gran tabla de calificaciones
    static std::vector<Calificacion>& tabla();

    // reset
    static void reset();

private:
    Codigo carnet_;
    int year_;
    int trimestre_;
    Codigo asignatura_;
    int nota_;
};
