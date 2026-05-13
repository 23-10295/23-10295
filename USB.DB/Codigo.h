///
/// Codigo.h
///

#pragma once

#include <string>

// Nota: explicar porque el uso de 'using" en archivos de encabezado es una MALA práctica.
// using N::C (por ejemplo, using std::string) <== NO lo hagan en archivos de encabezado (i.e. *.h)
// using namespace N (por ejemplo, using namespace std) <== aun peor, NO en archivos de encabezado

class Codigo {
public:
    Codigo(const char *s);
    Codigo(const std::string& s);
    const std::string& str() const;
    const char *c_str() const;
private:
    std::string valor_;
};
