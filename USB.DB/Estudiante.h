///
/// Estudiante.h
///

#pragma once

#include "Codigo.h"

#include <string>
#include <vector>

class Estudiante {
public:
    Estudiante(Codigo carnet, std::string nombre, Codigo carrera);

    std::string str() const;
    std::string json() const;

    Codigo carnet() const;
    std::string nombre() const;
    Codigo carrera() const;
    int year() const;

    bool activo() const;
    bool graduado() const;

    void update_academic_record();

    static const std::vector<Estudiante>& tabla();

    // OJO: NO deben usar las funciones declaradas de aqui al final del archivo
    static int new_academic_year();
    static int into_the_future(int n);
    static void reset();

private:
    Codigo carnet_;
    std::string nombre_;
    Codigo carrera_;
    int year_;
};
