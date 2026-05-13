///
/// Carrera.h
///
/// Carrera
///

#pragma once

#include "Codigo.h"
#include "Descripcion.h"

#include <string>
#include <vector>

class Carrera {
public:
    Carrera(Codigo clave, Descripcion descripcion);

    ~Carrera() throw();

    std::string str() const;
    std::string json() const;

    Codigo clave() {
        return clave_;
    }

    Descripcion descripcion() {
        return descripcion_;
    }

    static const std::vector<Carrera>& tabla();

private:
    Codigo clave_;
    Descripcion descripcion_;
};
