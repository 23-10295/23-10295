///
/// Carrera
///

#include "Carrera.h"

using std::string;
using std::vector;

static const vector<Carrera> tabla_ = {

    //
    // Adscritas al Decanato de Estudios Profesionales
    //

    // 6.2 Ciclo profesional de Ciencias Básicas
    Carrera("0400", "Licenciatura en Química"),
    Carrera("0500", "Licenciatura en Matemáticas"),
    Carrera("0501", "Licenciatura en Matemáticas (Estadística y Matemática Computacional)"),
    Carrera("0502", "Licenciatura en Matemáticas (Didáctica de la Matemática)"),
    Carrera("1000", "Licenciatura en Física"),
    Carrera("1900", "Licenciatura en Biología"),

    // 6.3 Ciclo profesional de Ingeniería y afines
    Carrera("0100", "Ingeniería Eléctrica"),
    Carrera("0200", "Ingeniería Mecánica"),
    Carrera("0300", "Ingeniería Química"),
    Carrera("0600", "Ingeniería Electrónica"),
    Carrera("0700", "Arquitectura"),
    Carrera("0800", "Ingeniería de Computación"),
    Carrera("1100", "Estudios Urbanos"),
    Carrera("1200", "Ingeniería Geofísica"),
    Carrera("1500", "Ingeniería de Materiales"),
    Carrera("1600", "Economía"),
    Carrera("1700", "Ingeniería de Producción"),
    Carrera("1800", "Ingeniería de Telecomunicaciones"),
    Carrera("4000", "Ingeniería de Mantenimiento"),

    // 6.4 Ciclo profesional de Ciencias Sociales, Humanidades y Administrativas
    Carrera("2400", "Licenciatura en Estudios y Artes Liberales"),
    Carrera("3000", "Licenciatura en Gestión de la Hospitalidad"),
    Carrera("3200", "Licenciatura en Comercio Internacional"),

    //
    // Adscritas al Decanato de Estudios Tecnológicos
    //
    
    Carrera("4001", "Tecnología Eléctrica"),
    Carrera("4102", "Tecnología Electrónica"),
    Carrera("4203", "Tecnología Mecánica"),
    Carrera("4204", "Mantenimiento Aeronáutico"),
    Carrera("4205", "Administración del Turismo"),
    Carrera("4206", "Administración Hotelera"),
    Carrera("4208", "Organización Empresarial"),
    Carrera("4309", "Comercio Exterior"),
    Carrera("4410", "Administración Aduanera"),
    Carrera("4507", "Administración del Transporte")
};

const vector<Carrera>& Carrera::tabla() {
    return tabla_;
};

Carrera::Carrera(Codigo clave, Descripcion descripcion)
:
    clave_(clave),
    descripcion_(descripcion)
{}

Carrera::~Carrera() throw() {}

string Carrera::str() const {
    return clave_.str() + ": " + descripcion_;
}

string Carrera::json() const {
    return "{ clave: " + clave_.str() + ", descripcion: " + descripcion_ + " }";
}
