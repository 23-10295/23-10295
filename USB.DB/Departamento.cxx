///
/// Departamento.cxx
///

#include "Departamento.h"

#include <vector>

using std::string;
using std::vector;

static const std::vector<Departamento> tabla_ = {

    // División de Ciencias Físicas y Matemáticas
    Departamento("CI", "CFM", "Computación y Tecnología de la Información"),
    Departamento("CO", "CFM", "Cómputo Científico y Estadística"),
    Departamento("CT", "CFM", "Conversión y Transporte de Energía"),
    Departamento("EC", "CFM", "Electrónica y Circuitos"),
    Departamento("FS", "CFM", "Física"),
    Departamento("GC", "CFM", "Ciencias de la Tierra"),
    Departamento("MA", "CFM", "Matemáticas Puras y Aplicadas"),
    Departamento("MC", "CFM", "Mecánica"),
    Departamento("MT", "CFM", "Ciencia de los Materiales"),
    Departamento("PS", "CFM", "Procesos y Sistemas"),
    Departamento("QM", "CFM", "Química"),
    Departamento("TF", "CFM", "Termodinámica y Fenómenos de Transferencia"),

    // División de Ciencias Sociales y Humanidades
    Departamento("CC", "CSH", "Ciencia y Tecnología del Comportamiento"),
    Departamento("CE", "CSH", "Ciencias Económicas y Administrativas"),
    Departamento("CS", "CSH", "Ciencias Sociales"),
    Departamento("DA", "CSH", "Diseño, Arquitectura y Artes Plásticas"),
    Departamento("FL", "CSH", "Filosofía"),
    Departamento("ID", "CSH", "Idiomas"),
    Departamento("LL", "CSH", "Lengua y Literatura"),
    Departamento("PL", "CSH", "Planificación Urbana"),

    // División de Ciencias Biológicas
    Departamento("BC", "BIO", "Biología Celular"),
    Departamento("BO", "BIO", "Biología de Organismos"),
    Departamento("EA", "BIO", "Estudios Ambientales"),
    Departamento("PB", "BIO", "Tecnología de Procesos Biológicos y Bioquímicos"),

    // División de Ciencias y Tecnologías Administrativas e Industriales
    Departamento("FC", "TAI", "Formación General y Ciencias Básicas"),
    Departamento("TI", "TAI", "Tecnología Industrial"),
    Departamento("TS", "TAI", "Tecnología de Servicios")
};

const std::vector<Departamento>& Departamento::tabla() {
    return tabla_;
};

Departamento::Departamento(Codigo clave, Codigo division, Descripcion descripcion)
:
    clave_(clave),
    division_(division),
    descripcion_(descripcion)
{}

Departamento::~Departamento() throw() {}

string Departamento::str() const {
    return clave_.str() + ": " + descripcion_;
}

string Departamento::json() const {
    return
        "{ clave: " + clave_.str() +
         ", division: " + division_.str() +
         ", descripcion: " + descripcion_ + "}";
}

/*
Departamento::clave() {
    return clave_;
}

Departamento::division() {
    return division_;
}

Departamento::descripcion() {
    return descripcion_;
}
*/
