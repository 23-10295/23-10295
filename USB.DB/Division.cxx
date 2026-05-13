///
/// Division.cxx
///

#include "Division.h"

using std::string;

static const char *divisiones[][2] = {
    { "CFM", "División de Ciencias Físicas y Matemáticas" },
    { "CSH", "División de Ciencias Sociales y Humanidades" },
    { "BIO", "División de Ciencias Biológicas" },
    { "TAI", "División de Ciencias y Tecnologías Administrativas e Industriales" }
};

Division::Division(Codigo clave, Descripcion descripcion)
:
    clave_(clave),
    descripcion_(descripcion)
{}

Division::~Division() {}

string Division::str() const {
    return clave_.str() + ": " + descripcion_;
}

string Division::json() const {
    return "{ clave: " + clave_.str() + ", descripcion: " + descripcion_ + "}";
}

std::vector<Division> Division::tabla_ = {};

const std::vector<Division>& Division::tabla() {
    if (tabla_.size() == 0) {
        const int N = sizeof(divisiones) / sizeof(divisiones[0]);
        for (int i = 0; i < N; ++i) {
            Codigo codigo = Codigo(divisiones[i][0]);
            Descripcion descripcion = Descripcion(divisiones[i][1]);
            Division division = Division(codigo, descripcion);
            tabla_.push_back(division);
        }
    }
    return tabla_;
}
