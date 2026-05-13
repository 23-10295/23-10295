///
/// Division.h
///

#pragma once

#include "Codigo.h"
#include "Descripcion.h"

#include <vector>

using std::vector;

class Division {
public:
    
    class Tabla: std::vector<Division> {};

    Division(Codigo clave, Descripcion descripcion);

    ~Division();

    std::string str() const;
    std::string json() const;

    Codigo clave() {
        return clave_;
    }

    Descripcion descripcion() {
        return descripcion_;
    }

    static const std::vector<Division>& tabla();

private:
    Codigo clave_;
    Descripcion descripcion_;
    static std::vector<Division> tabla_;
};
