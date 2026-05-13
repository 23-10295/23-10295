///
/// Coordinacion.h
///
/// Coordinacion
///

/*
    (Código 0100) Ingeniería Eléctrica 
    (Código 0200) Ingeniería Mecánica 
    (Código 0300) Ingeniería Química 
    (Código 0400) Licenciatura en Química 
    (Código 0500) Licenciatura en Matemáticas 
    (Código 0501) Licenciatura en Matemáticas (opción Estadística y Matemática Computacional) 
    (Código 0502) Licenciatura en Matemáticas (opción Didáctica de la Matemática) 
    (Código 0600) Ingeniería Electrónica 
    (Código 0700) Arquitectura 
    (Código 0800) Ingeniería de Computación 
    (Código 1000) Licenciatura en Física 
    (Código 1100) Estudios Urbanos 
    (Código 1200) Ingeniería Geofísica 
    (Código 1500) Ingeniería de Materiales 
    (Código 1600) Economía 
    (Código 1700) Ingeniería de Producción 
    (Código 1800) Ingeniería de Telecomunicaciones 
    (Código 1900) Licenciatura en Biología 
    (Código 2400) Licenciatura en Estudios y Artes Liberales 
*/

#pragma once

#include "Codigo.h"
#include "Descripcion.h"

#include <string>
#include <vector>

class Coordinacion {
public:
    Coordinacion(Codigo clave, Codigo decanato, Descripcion descripcion);

    ~Coordinacion() throw();

    std::string str() const;
    std::string json() const;

    Codigo clave() {
        return clave_;
    }

    Codigo decanato() {
        return decanato_;
    }

    Descripcion descripcion() {
        return descripcion_;
    }

    static const std::vector<Coordinacion>& tabla();

private:
    Codigo clave_;
    Codigo decanato_;
    Descripcion descripcion_;
};
