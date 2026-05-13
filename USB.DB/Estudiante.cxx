///
/// Estudiante.cxx
///

#include "Estudiante.h"
#include "Calificacion.h"
#include "CicloProfesional.h"

#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

using std::string;
using std::vector;

// Simple implementación de un generador de números enteros aleatorios
// Suficientemente buena para el simple propósito de este módulo
int random_int(int n) {
    return rand() % n;        
}

// Muestra de nombres femeninos
vector<string> ffirst = {
    "Alicia",
    "Beatriz",
    "Cecilia",
    "Diana",
    "Erica",
    "Fernanda",
    "Graciela",
    "Hannah",
    "Irina",
    "Julia",
    "Kayla",
    "Lucia",
    "Monica",
    "Noelia",
    "Olga",
    "Patricia",
    "Quimera",
    "Raquel",
    "Susana",
    "Tatiana",
    "Ursula",
    "Victoria",
    "Wanda",
    "Xena",
    "Yolanda",
    "Zoila"
};

// Muestra de nombres masculinos
vector<string> mfirst = {
    "Andres",
    "Bruno",
    "Carlos",
    "David",
    "Ernesto",
    "Francisco",
    "Gabriel",
    "Héctor",
    "Ignacio",
    "Javier",
    "Kurt",
    "Luis",
    "Mauricio",
    "Néstor",
    "Oscar",
    "Pedro",
    "Quirino",
    "Roberto",
    "Samuel",
    "Tomás",
    "Ulises",
    "Victor",
    "Walter",
    "Xavier",
    "Yannick",
    "Zoila"
};

// Muestra de apellidos
vector<string> last = {
    "Alvarado",
    "Brito",
    "Campos",
    "Domínguez",
    "Echeverria",
    "Fuentes",
    "Gil",
    "Hernández",
    "Iriarte",
    "Jiménez",
    "Koch",
    "León",
    "Montoya",
    "Navarro",
    "Ordoñez",
    "Peña",
    "Quevedo",
    "Ruiz",
    "Sanchez",
    "Torres",
    "Uribe",
    "Villegas",
    "Weber",
    "Xu",
    "Yanez",
    "Zamora"
};

// Experimento opcional (no se evalua): agreguen algunos nombres y apellidos adicionales, y preguntense:
// Importa si no los agregan en orden alfabético?
// Importa si los agregan al comienzo o al final?
// Hacen que potencialmente (asumiendo una muestra grande) algunos nombres iniciales no aparezcan?

// Genera un nombre femenino completo con apellido
string generate_female_name() {
    int f_index = random_int(ffirst.size()); // computa el indice del 'primer' nombre (nombre de pila?)
    int m_index = random_int(26); // computa el indice (desplazamiento) de la inicial del nombre intermedio
    int l_index = random_int(last.size()); // computa el indice del apellido
    string full_name = ffirst[f_index] + " " + char('A' + m_index) + ". " + last[l_index];
    return full_name;
}

// Genera un nombre masculino completo con apellido
string generate_male_name() {
    int f_index = random_int(mfirst.size());
    int m_index = random_int(26);
    int l_index = random_int(last.size());
    string full_name = mfirst[f_index] + " " + char('A' + m_index) + ". " + last[l_index];
    return full_name;
}

Estudiante::Estudiante(Codigo carnet, std::string nombre, Codigo carrera)
:
    carnet_(carnet),
    nombre_(nombre),
    carrera_(carrera),
    year_(0)
{}

Codigo Estudiante::carnet() const {
    return carnet_;
}

string Estudiante::nombre() const {
    return nombre_;
}

int Estudiante::year() const {
    return year_;
}

bool Estudiante::activo() const {
    return !graduado();
}

bool Estudiante::graduado() const {
    return year_ < 0;
}

string Estudiante::str() const {
    return carnet_.str() + ": " + nombre_ + " (año: " + std::to_string(year_) + ")";
}

string Estudiante::json() const {
    return
        string("{ carnet: ") + carnet_.str()
        + ", nombre: " + nombre_
        + ", año: "  + std::to_string(year_) + "}";
}

/// Tabla de Estudiantes

static vector<Estudiante> estudiantes_ = {};

const vector<Estudiante>& Estudiante::tabla() {
    return estudiantes_;
}

/// 
/// The simulation happens here ..
/// 

static bool debug = true;

static unsigned int starting_year = 2041;
static unsigned int academic_year = starting_year;

static size_t active_students = 0;
static size_t graduated_students = 0;
static size_t previous = 0;

static size_t COHORT_SIZE  = 1024;
static double GROW_RATE = 1.18;

static vector<Calificacion>& calificaciones = Calificacion::tabla();

static void report_statistics() {
    int y = academic_year;
    size_t a = active_students;
    size_t g = graduated_students;
    const char *format = "%d-%d: active: %lu, graduated: %lu, total: %lu\n";
    fprintf(stdout, format, y, y + 1, a, g, a + g);
    size_t growth = estudiantes_.size() - previous;
    format = "growth (%4.2f): %lu -> %lu => %lu (%lu)\n"; // warning: format reuse hack
    fprintf(stdout, format, GROW_RATE, previous, estudiantes_.size(), growth, a + g);
    fprintf(stdout, "Grades: %lu\n", calificaciones.size());
}

static vector<int> notas = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5 };

static void eval(const Estudiante& estudiante, const Trimestre& trimestre, int tri) {
    Codigo carnet = estudiante.carnet();
    int year = academic_year + int(1 < tri);
    for (Codigo asignatura: trimestre) {
        int nota = notas[random_int(notas.size())];
        auto calificacion = Calificacion(carnet, year, tri, asignatura, nota);
        calificaciones.push_back(calificacion);
    }
}

void Estudiante::update_academic_record() {
    assert(this->activo()); // siempre se cumple si el codigo no es alterado
    if (year_ == 5) {
        year_ = -1; // graduated!
        ++graduated_students;
        --active_students;
        return;
    }
    ++year_;
    for (int tri = 1; tri <= 3; ++tri) {
        Trimestre trimestre = CicloProfesional::asignaturas(carrera_, year_, tri);
        eval(*this, trimestre, tri);
    }
}

static void update_academic_records() {
    for (auto& s: estudiantes_) {
        if (s.graduado()) {
            // leave graduated students untouched
            continue;
        }
        // only update students that are still active
        s.update_academic_record();
    }
}

static const vector<Codigo>& carreras = CicloProfesional::carreras();

int Estudiante::new_academic_year() {
    ++academic_year;
    if (debug) fprintf(stdout, "<<<<<<<< %u >>>>>>>>\n", academic_year);
    previous = estudiantes_.size();
    if (previous == 0) {
        estudiantes_.reserve(2500); // for efficiency in the early growth stages
    }
    COHORT_SIZE = size_t(GROW_RATE * COHORT_SIZE);
    string prefix = std::to_string(academic_year % 100) + "-";
    // Add "fresh" students
    for (size_t i = 0; i < COHORT_SIZE; ++i) {
        Codigo carnet = prefix + std::to_string(10001 + i);
        string full = (random_int(2) == 0 ? generate_female_name() : generate_male_name());
        Codigo carrera = carreras[random_int(carreras.size())];
        Estudiante estudiante = Estudiante(carnet, full, carrera);
        estudiantes_.push_back(estudiante);
        ++active_students;
    }
    // Add records for attendance and academic results in this new academic year
    update_academic_records();
    // Reduce growth rate for aymptotic growth
    if (1.0 < GROW_RATE) {
        GROW_RATE -= 0.005;
    } else {
        GROW_RATE = 1.0; // required for perfect stability (avoids rounding error)
    }
    report_statistics();
    return EXIT_SUCCESS;
}

int Estudiante::into_the_future(int n) {
    if (n < 1 || 49 < n) {
        fprintf(stderr, "n == %d is not allowed\n", n);
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i) {
        Estudiante::new_academic_year();
    }
    return EXIT_SUCCESS;
}

void Estudiante::reset() {
    Calificacion::reset();
    estudiantes_.clear();
    academic_year = starting_year;

    active_students = 0;
    graduated_students = 0;
    previous = 0;

    COHORT_SIZE  = 1024;
    GROW_RATE = 1.18;
}
