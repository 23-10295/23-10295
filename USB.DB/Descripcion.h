///
/// Descripcion.h
///

#pragma once

#include <string>

// Nota: explicar porque el uso de 'using" en archivos de encabezado es una MALA práctica.
// using N::C (por ejemplo, using std::string) <== NO lo hagan en archivos de encabezado (i.e. *.h)
// using namespace N (por ejemplo, using namespace std) <== aun peor, NO en archivos de encabezado

typedef std::string Descripcion;
