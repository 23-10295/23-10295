///
/// Codigo.cxx
///

#include "Codigo.h"

Codigo::Codigo(const char *s)
:
    valor_(s)
{}

Codigo::Codigo(const std::string& s)
:
    valor_(s)
{}

const std::string& Codigo::str() const {
    return valor_;
}

const char *Codigo::c_str() const {
    return valor_.c_str();
}
