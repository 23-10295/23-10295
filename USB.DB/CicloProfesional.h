///
/// Ciclo Profesional (interfaz)
///

#pragma once

#include "Codigo.h"
#include <string>
#include <vector>

// Representa las asignaturas dadas en un trimestre de una carrera dada
typedef std::vector<std::string> Trimestre;

// Representa un año de la carrera - contiene tres trimestres: primero, segundo, y tercero
typedef std::vector<Trimestre> UYear;

// Representa el ciclo profesional completo, que consiste de varios años de la carrera
typedef std::vector<UYear> Ciclo;

class CicloProfesional {
public:

    // Retorna los codigos de las carreras que tienen su ciclo profesional ya implementado.
    // Todavía faltan varios ciclos profesionales porque este proyecto sigue evolucionando.
    // Un ciclo profesional y 4 carreras listas son más que suficientes para esta tarea.
    static const std::vector<Codigo>& carreras();

    // Retorna los códigos de las asignaturas de un trimestre dado
    //
    // carrera: código de la carrera
    // uyear: año de la carrera - los valores para las ingenierías son de 1 a 5
    // trimestre: trimestre del año academico: de 1 a 3 (tambien aquí, 0 no es válido)
    // retorna un vector con los códigos (en formato const char *) de las materias
    static const Trimestre& asignaturas(Codigo carrera, int uyear, int trimestre);
};
