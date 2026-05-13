///
/// Calificacion
///

#include "Calificacion.h"

using std::string;
using std::vector;

Calificacion::Calificacion(Codigo carnet, int year, int trimestre, Codigo asignatura, int nota)
:
    carnet_(carnet),
    year_(year),
    trimestre_(trimestre),
    asignatura_(asignatura),
    nota_(nota)
{}

Calificacion::~Calificacion() throw()
{}

string Calificacion::str() const {
    return
        string("(")
            + carnet_.str() + ", "
            + std::to_string(year_) + "/"
            + std::to_string(trimestre_) + ", "
            + asignatura_.str() + ", "
            + std::to_string(nota_)
        + ")"
    ;
}

string Calificacion::json() const {
    return
        string("{")
            + "carnet: " + carnet_.str() + ", "
            + "year: " + std::to_string(year_) + ", "
            + "trimestre: " + std::to_string(trimestre_) + ", "
            + "asignatura: " + asignatura_.str() + ", "
            + "nota: " + std::to_string(nota_)
        + "}"
    ;
}

/// Tabla de Calificaciones

static vector<Calificacion> calificaciones = {};

vector<Calificacion>& Calificacion::tabla() {
    if (calificaciones.empty()) {
        calificaciones.reserve(1024);
    }
    return calificaciones;
}

void Calificacion::reset() {
    calificaciones.clear();
}
