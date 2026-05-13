///
/// Departamento.h
///
/// Departamento
///

/*
*/

#pragma once

#include "Codigo.h"
#include "Descripcion.h"

#include <string>
#include <vector>

class Departamento {
public:
    Departamento(Codigo clave, Codigo division, Descripcion descripcion);

    ~Departamento() throw();

    std::string str() const;
    std::string json() const;

    Codigo clave() {
        return clave_;
    }

    Codigo division() {
        return division_;
    }

    Descripcion descripcion() {
        return descripcion_;
    }

    static const std::vector<Departamento>& tabla();

private:
    Codigo clave_;
    Codigo division_;
    Descripcion descripcion_;
};
