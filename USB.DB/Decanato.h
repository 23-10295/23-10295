///
/// Decanato.h
///

#pragma once

#include "Codigo.h"
#include "Descripcion.h"

#include <vector>

class Decanato {
public:
    
    Decanato(Codigo clave, Descripcion descripcion);

    ~Decanato();

    std::string str() const;
    std::string json() const;

    Codigo clave() {
        return clave_;
    }

    Descripcion descripcion() {
        return descripcion_;
    }

    static const std::vector<Decanato>& tabla();

private:
    Codigo clave_;
    Descripcion descripcion_;
};
