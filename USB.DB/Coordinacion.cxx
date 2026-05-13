///
/// Coordinacion.cxx
///

#include "Coordinacion.h"

#include <vector>

using std::string;
using std::vector;

static const vector<Coordinacion> tabla_ = {

    // Decanato de Estudios Generales,
    Coordinacion("CIU", "DGEN", "Coordinación del Ciclo de Iniciación Universitaria"),
    Coordinacion("CCB", "DGEN", "Coordinación del Ciclo Básico"),
    Coordinacion("CFG", "DGEN", "Coordinación de Formación General"),
    Coordinacion("CCP", "DGEN", "Coordinación del Ciclo Profesional"),

    // Decanato de Estudios Profesionales
    Coordinacion("0100", "PROF", "Ingeniería Eléctrica"),
    Coordinacion("0200", "PROF", "Ingeniería Mecánica"),
    Coordinacion("0300", "PROF", "Ingeniería Química"),
    Coordinacion("0400", "PROF", "Licenciatura en Química"),
    Coordinacion("0500", "PROF", "Licenciatura en Matemáticas"),
    Coordinacion("0501", "PROF", "Licenciatura en Matemáticas (Estadística y Matemática Computacional)"),
    Coordinacion("0502", "PROF", "Licenciatura en Matemáticas (Didáctica de la Matemática)"),
    Coordinacion("0600", "PROF", "Ingeniería Electrónica"),
    Coordinacion("0700", "PROF", "Arquitectura"),
    Coordinacion("0800", "PROF", "Ingeniería de Computación"),
    Coordinacion("1000", "PROF", "Licenciatura en Física"),
    Coordinacion("1100", "PROF", "Estudios Urbanos"),
    Coordinacion("1200", "PROF", "Ingeniería Geofísica"),
    Coordinacion("1500", "PROF", "Ingeniería de Materiales"),
    Coordinacion("1600", "PROF", "Economía"),
    Coordinacion("1700", "PROF", "Ingeniería de Producción"),
    Coordinacion("1800", "PROF", "Ingeniería de Telecomunicaciones"),
    Coordinacion("1900", "PROF", "Licenciatura en Biología"),
    Coordinacion("2400", "PROF", "Licenciatura en Estudios y Artes Liberales"),
    Coordinacion("3000", "PROF", "Licenciatura en Gestión de la Hospitalidad"),
    Coordinacion("3200", "PROF", "Licenciatura en Comercio Internacional"),
    Coordinacion("4000", "PROF", "Ingeniería de Mantenimiento"),

    // Decanato de Estudios Tecnológicos
    Coordinacion(  "01", "DTEC", "Tecnología Eléctrica (Camurí)"),
    Coordinacion("4000", "DTEC", "Tecnología Eléctrica (Sartenejas)"),
    Coordinacion(  "02", "DTEC", "Tecnología Electrónica (Camurí)"),
    Coordinacion("4100", "DTEC", "Tecnología Electrónica (Sartenejas)"),
    Coordinacion(  "03", "DTEC", "Tecnología Mecánica (Camurí)"),
    Coordinacion(  "04", "DTEC", "Mantenimiento Aeronáutico (Camurí)"),
    Coordinacion(  "05", "DTEC", "Administración del Turismo (Camurí)"),
    Coordinacion(  "06", "DTEC", "Administración Hotelera (Camurí)"),
    Coordinacion(  "09", "DTEC", "Comercio Exterior (Camurí)"),
    Coordinacion("4300", "DTEC", "Comercio Exterior (Sartenejas)"),
    Coordinacion(  "10", "DTEC", "Administración Aduanera (Camurí)"),
    Coordinacion(  "07", "DTEC", "Administración del Transporte (Camurí)"),
    Coordinacion(  "08", "DTEC", "Organización Empresarial (Camurí)"),
    Coordinacion("4200", "DTEC", "Organización Empresarial (Sartenejas)")

    // Decanato de Estudios de Postgrado
    // Decanato de Investigación y Desarrollo
    // Decanato de Extensión"
};

const vector<Coordinacion>& Coordinacion::tabla() {
    return tabla_;
};

Coordinacion::Coordinacion(Codigo clave, Codigo decanato, Descripcion descripcion)
:
    clave_(clave),
    decanato_(decanato),
    descripcion_(descripcion)
{}

Coordinacion::~Coordinacion() throw() {}

string Coordinacion::str() const {
    return clave_.str() + ": " + descripcion_;
}

string Coordinacion::json() const {
    return "{ clave: " + clave_.str() + ", decanato: " + decanato_.str() + ", descripcion: " + descripcion_ + "}";
}

/*
Coordinacion::clave() {
    return clave_;
}

Coordinacion::decanato() {
    return decanato_;
}

Coordinacion::descripcion() {
    return descripcion_;
}
*/
