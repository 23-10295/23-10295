///
/// Decanato.cxx
///

#include "Decanato.h"

using std::string;
using std::vector;

static const char *decanatos[] = {
    "Decanato de Estudios Generales",
    "Decanato de Estudios Profesionales",
    "Decanato de Estudios Tecnológicos",
    "Decanato de Estudios de Postgrado",
    "Decanato de Investigación y Desarrollo",
    "Decanato de Extensión"
};

Decanato::Decanato(Codigo clave, Descripcion descripcion)
:
    clave_(clave),
    descripcion_(descripcion)
{}

Decanato::~Decanato() {}

string Decanato::str() const {
    return clave_.str() + ": " + descripcion_;
}

string Decanato::json() const {
    return "{ clave: " + clave_.str() + ", descripcion: " + descripcion_ + "}";
}

// La tabla de decanatos (tabla_) es una variable escondida.
// Aqui usamos la técnica de inicializacion en el primer acceso

static vector<Decanato> tabla_ = {};

// Retorna la tabla de decanatos ..
// .. pero primero la crea si está vacia
// Este función permite el acceso de lectura, pero no escritura, a la tabla
const vector<Decanato>& Decanato::tabla() {
    if (tabla_.size() == 0) {
        const int N = sizeof(decanatos) / sizeof(const char *);
        for (int i = 0; i < N; ++i) {
            Codigo codigo = Codigo(std::to_string(100 * (1 + i)));
            Descripcion descripcion = Descripcion(decanatos[i]);
            Decanato decanato = Decanato(codigo, descripcion);
            tabla_.push_back(decanato);
        }
    }
    return tabla_;
}
