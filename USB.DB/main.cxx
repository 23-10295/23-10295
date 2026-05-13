///
/// main.cxx
///

///
/// De acuerdo a las enseñanzas de Aristoteles y Arnold Schwarzenegger:
///
/// no main => no pain &
/// no pain => no gain =>
/// ------------------
/// no main => no gain (Q.E.D.)
///
/// En Latin, a esto se le llama "modus ponendo ponens" ..
/// .. frequentemente abreviado "modus ponens"
///

#include "Division.h"
#include "Departamento.h"
#include "Asignatura.h"
#include "Decanato.h"
#include "Coordinacion.h"
#include "Carrera.h"
#include "Estudiante.h"
#include "Calificacion.h"
#include "Query.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using std::string;

//
// Menu
//

typedef int (*Functor)();

struct MenuOption {
    MenuOption(string key, const char *option, Functor fun)
    :
        key_(key),
        option_(option),
        fun_(fun)
    {}

    string key_;
    const char *option_;
    Functor fun_;
};

typedef const vector<MenuOption> Options;

//
// Funciones del menu
//

static int nop() {
    return EXIT_SUCCESS;
}

static int prueba_divisiones() {
    fprintf(stdout, "probando divisiones\n");
    const std::vector<Division>& tabla = Division::tabla();
    for (Division division: tabla) {
        fprintf(stdout, "%s\n", division.str().c_str());
    }
    for (Division division: tabla) {
        fprintf(stdout, "%s\n", division.json().c_str());
    }
    return EXIT_SUCCESS;
}

static int prueba_departamentos() {
    fprintf(stdout, "probando departamentos\n");
    const std::vector<Departamento>& tabla = Departamento::tabla();
    for (Departamento departamento: tabla) {
        fprintf(stdout, "%s\n", departamento.str().c_str());
    }
    for (Departamento departamento: tabla) {
        fprintf(stdout, "%s\n", departamento.json().c_str());
    }
    return EXIT_SUCCESS;
}

static int prueba_asignaturas() {
    fprintf(stdout, "probando asignaturas\n");
    const std::vector<Asignatura>& tabla = Asignatura::tabla();
    for (Asignatura asignatura: tabla) {
        fprintf(stdout, "%s\n", asignatura.str().c_str());
    }
    for (Asignatura asignatura: tabla) {
        fprintf(stdout, "%s\n", asignatura.json().c_str());
    }
    return EXIT_SUCCESS;
}

static int prueba_decanatos() {
    fprintf(stdout, "probando decanatos\n");
    const std::vector<Decanato>& tabla = Decanato::tabla();
    for (Decanato decanato: tabla) {
        fprintf(stdout, "%s\n", decanato.str().c_str());
    }
    for (Decanato decanato: tabla) {
        fprintf(stdout, "%s\n", decanato.json().c_str());
    }
    return EXIT_SUCCESS;
}

static int prueba_coordinaciones() {
    fprintf(stdout, "probando coordinaciones\n");
    const std::vector<Coordinacion>& tabla = Coordinacion::tabla();
    for (Coordinacion coordinacion: tabla) {
        fprintf(stdout, "%s\n", coordinacion.str().c_str());
    }
    for (Coordinacion coordinacion: tabla) {
        fprintf(stdout, "%s\n", coordinacion.json().c_str());
    }
    return EXIT_SUCCESS;
}

static int prueba_carreras() {
    fprintf(stdout, "probando carreras\n");
    const std::vector<Carrera>& tabla = Carrera::tabla();
    for (Carrera carrera: tabla) {
        fprintf(stdout, "%s\n", carrera.str().c_str());
    }
    for (Carrera carrera: tabla) {
        fprintf(stdout, "%s\n", carrera.json().c_str());
    }
    return EXIT_SUCCESS;
}

static int prueba_estudiantes() {
    fprintf(stdout, "probando estudiantes\n");
    const std::vector<Estudiante>& tabla = Estudiante::tabla();
    // Por razones prácticas, limitamos el numero de estudiantes mostrados
    size_t M = 6;
    size_t N = tabla.size();
    M = M < (N + 1) / 2 ? M : (N + 1) / 2;
    fprintf(stdout, "La tabla tiene %zu estudiantes - mostramos algunos al comienzo y al final\n", N);
    for (size_t i = 0; i < M; ++i) {
        Estudiante estudiante = tabla[i];
        fprintf(stdout, "%s\n", estudiante.str().c_str());
    }
    for (size_t i = 0; i < M; ++i) {
        Estudiante estudiante = tabla[i];
        fprintf(stdout, "%s\n", estudiante.json().c_str());
    }
    fprintf(stdout, ".. .. .. .. .. .. .. ..\n");
    for (size_t i = N - M; i < N; ++i) {
        Estudiante estudiante = tabla[i];
        fprintf(stdout, "%s\n", estudiante.str().c_str());
    }
    for (size_t i = N - M; i < N; ++i) {
        Estudiante estudiante = tabla[i];
        fprintf(stdout, "%s\n", estudiante.json().c_str());
    }
    return EXIT_SUCCESS;
}

static int prueba_calificaciones() {
    fprintf(stdout, "probando calificaciones\n");
    const std::vector<Calificacion>& tabla = Calificacion::tabla();
    // Por razones prácticas, limitamos el numero de calificaciones a mostrar
    size_t M = 18;
    size_t N = tabla.size();
    M = M < (N + 1) / 2 ? M : (N + 1) / 2;
    fprintf(stdout, "La tabla tiene %zu calificaciones - mostramos varias al comienzo y al final\n", N);
    for (size_t i = 0; i < M; ++i) {
        Calificacion calificacion = tabla[i];
        fprintf(stdout, "%s\n", calificacion.str().c_str());
    }
    for (size_t i = 0; i < M; ++i) {
        Calificacion calificacion = tabla[i];
        fprintf(stdout, "%s\n", calificacion.json().c_str());
    }
    fprintf(stdout, ".. .. .. .. .. .. .. ..\n");
    for (size_t i = N - M; i < N; ++i) {
        Calificacion calificacion = tabla[i];
        fprintf(stdout, "%s\n", calificacion.str().c_str());
    }
    for (size_t i = N - M; i < N; ++i) {
        Calificacion calificacion = tabla[i];
        fprintf(stdout, "%s\n", calificacion.json().c_str());
    }
    return EXIT_SUCCESS;
}

static int reset() {
    Estudiante::reset();
    const std::vector<Calificacion>& calificaciones = Calificacion::tabla();
    const std::vector<Estudiante>& estudiantes = Estudiante::tabla();
    if (calificaciones.size() == 0 && estudiantes.size() == 0) {
        fprintf(stdout, "Reset completo: de vuelta al estado inicial\n");
    } else {
        fprintf(stdout, "Esto puede ocurrir por interferencia con un neutrino\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int new_academic_year() {
    int status = Estudiante::new_academic_year();
    return status;
}

// global parameter hack for simulation depth
static int depth = 1;

// let's go: extend deep into the future ..
static int into_the_future() {
    Estudiante::into_the_future(depth);
    return EXIT_SUCCESS;
}

static int despedida() {
    fprintf(stdout, "¡Gracias por usar el simulador de la USB!\n");
    return EXIT_SUCCESS;
}

static int prueba_todas() {
    prueba_divisiones();
    prueba_departamentos();
    prueba_asignaturas();
    prueba_decanatos();
    prueba_coordinaciones();
    prueba_carreras();
    prueba_estudiantes();
    prueba_calificaciones();
    return EXIT_SUCCESS;
}

static int muestra_menu();

static Options options = {
    MenuOption("1", "divisiones",       prueba_divisiones       ),
    MenuOption("2", "departamentos",    prueba_departamentos    ),
    MenuOption("3", "asignaturas",      prueba_asignaturas      ),
    MenuOption("4", "decanatos",        prueba_decanatos        ),
    MenuOption("5", "coordinaciones",   prueba_coordinaciones   ),
    MenuOption("6", "carreras",         prueba_carreras         ),
    MenuOption("7", "estudiantes",      prueba_estudiantes      ),
    MenuOption("8", "calificaciones",   prueba_calificaciones   ),
    MenuOption(">", "avanzar un año",   new_academic_year       ),
    MenuOption("t", "todas",            prueba_todas            ),
    MenuOption("m", "menu",             muestra_menu            ),
    MenuOption(".", "salir",            despedida               ),

    MenuOption("x:", "extender años",   into_the_future         ),
    MenuOption("00", "reset",           reset                   ),

    MenuOption("q0", "query 0",         Query::q0               ),
    MenuOption("q1", "query 1",         Query::q1               ),
    MenuOption("q2", "query 2",         Query::q2               ),
    MenuOption("q3", "query 3",         Query::q3               ),
    MenuOption("q4", "query 4",         Query::q4               ),
    MenuOption("q5", "query 5",         Query::q5               ),
};

static int muestra_menu() {
    const char *CLEAR_SCREEN = "\033[2J\033[H";
    fprintf(stdout, "%s", CLEAR_SCREEN);
    for (const auto& option: options) {
        fprintf(stdout, "%s - %s\n", option.key_.c_str(), option.option_);
    }
    return EXIT_SUCCESS;
}

static Functor find(const string& key, const Options& options) {
    for (const auto& option: options) {
        if (key == option.key_) {
            return option.fun_;
        }
    }
    return nop;
}

static int menu() {
    for (;;) {

        string opt;
        fprintf(stdout, "<USB DB> ");
        std::getline(std::cin, opt);
        if (opt == string(".")) {
            return despedida();
        }

        const char *optcstr = opt.c_str();
        if (strncmp(optcstr, "x:", 2) == 0) {
            depth = atoi(&optcstr[2]);
            int status = into_the_future();
            depth = 1;
            if (status != EXIT_SUCCESS) {
                return status;
            }
        }

        Functor operation = find(opt, options);
        int status = operation();
        if (status != EXIT_SUCCESS) {
            return status;
        }
    }
}

static int uso_correcto(const char *programa) {
    fprintf(stdout, "%s divisiones\n", programa);
    fprintf(stdout, "%s departamentos\n", programa);
    fprintf(stdout, "%s asignaturas\n", programa);
    fprintf(stdout, "%s decanatos\n", programa);
    fprintf(stdout, "%s coordinaciones\n", programa);
    fprintf(stdout, "%s carreras\n", programa);
    fprintf(stdout, "%s estudiantes\n", programa);
    fprintf(stdout, "%s calificaciones\n", programa);
    fprintf(stdout, "%s todas\n", programa);
    return EXIT_SUCCESS;
}

static int prueba(const char *programa, const char *caso) {
    int status = EXIT_SUCCESS;
    if (strcmp(caso, "divisiones") == 0) {
        status += prueba_divisiones();
        return status;
    }
    if (strcmp(caso, "departamentos") == 0) {
        status += prueba_departamentos();
        return status;
    }
    if (strcmp(caso, "asignaturas") == 0) {
        status += prueba_asignaturas();
        return status;
    }
    if (strcmp(caso, "decanatos") == 0) {
        status += prueba_decanatos();
        return status;
    }
    if (strcmp(caso, "coordinaciones") == 0) {
        status += prueba_coordinaciones();
        return status;
    }
    if (strcmp(caso, "carreras") == 0) {
        status += prueba_carreras();
        return status;
    }
    if (strcmp(caso, "estudiantes") == 0) {
        status += prueba_estudiantes();
        return status;
    }
    if (strcmp(caso, "calificaciones") == 0) {
        status += prueba_calificaciones();
        return status;
    }
    if (strcmp(caso, "ayuda") == 0) {
        status += uso_correcto(programa);
        return status;
    }
    if (strcmp(caso, "todas") == 0) {
        status += prueba_todas();
        return status;
    }
    if (strncmp(caso, "ext:", 4) == 0) {
        depth = atoi(&caso[4]);
        status += into_the_future();
        depth = 1;
        return status;
    }
    // abandon hope, oh ye who enter here ..
    fprintf(stderr, "%s %s: no es válido\n", programa, caso);
    uso_correcto(programa);
    return EXIT_FAILURE;
}

static void mal_uso_es_abuso(const char *programa) {
    fprintf(stderr, "%s: ¡mal uso!\n", programa);
    fprintf(stdout, "formas apropiadas:\n");
    uso_correcto(programa);
}

int main(int argc, const char *argv[]) {

    if (argc == 1) {
        muestra_menu();
        int status = menu();
        return status;
    }

    if (argc == 2) {
        int status = prueba(argv[0], argv[1]);
        return status;
    }

    // abandon hope ye all who enter here ..
    mal_uso_es_abuso(argv[0]);
    return EXIT_FAILURE;
}
