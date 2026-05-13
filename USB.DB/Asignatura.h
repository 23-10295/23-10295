///
/// Asignatura.h
///

#pragma once

#include "Codigo.h"
#include "Descripcion.h"

#include <cstdint> // encabezado que define uint8_t
#include <string>
#include <vector>

class Asignatura {
public:
    Asignatura(Codigo codigo, Codigo departamento, Descripcion descripcion, uint8_t uc);

    ~Asignatura();

    std::string str() const;
    std::string json() const;

    Codigo codigo() {
        return codigo_;
    }

    Codigo departamento() {
        return departamento_;
    }

    Descripcion descripcion() {
        return descripcion_;
    }

    uint8_t uc() {
        return uc_;
    }

    static const std::vector<Asignatura>& tabla();

private:
    Codigo codigo_;
    Codigo departamento_;
    Descripcion descripcion_;
    uint8_t uc_;
};
