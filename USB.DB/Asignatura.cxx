///
/// Asignaturas
///

#include "Asignatura.h"

using std::string;
using std::vector;

static const vector<Asignatura> tabla_ = {

    // Asignaturas en los Ciclos Básicos

    // Ciclo básico de Ingeniería y Licenciatura (Matemáticas, Física y Química)
    Asignatura("MA1111", "MA", "Matemáticas I", 4),
    Asignatura("LLA111", "LL", "Lenguaje I", 3),
    Asignatura("CSA211", "CS", "Venezuela ante el Siglo XXI I", 3),
    Asignatura("ID1111", "ID", "Inglés I", 3),
    Asignatura("MA1511", "MA", "Geometría", 2),

    Asignatura("MA1112", "MA", "Matemáticas II", 4),
    Asignatura("LLA112", "LL", "Lenguaje II", 3),
    Asignatura("CSA212", "CS", "Venezuela ante el Siglo XXI II", 3),
    Asignatura("ID1112", "ID", "Inglés II", 3),
    Asignatura("FS1111", "FS", "Física I", 3),

    Asignatura("MA1116", "MA", "Matemáticas III", 4),
    Asignatura("LLA113", "LL", "Lenguaje III", 3),
    Asignatura("CSA213", "CS", "Venezuela ante el Siglo XXI III", 3),
    Asignatura("ID1113", "ID", "Inglés III", 3),
    Asignatura("FS1112", "FS", "Física II", 2),

    // Ciclo básico de Arquitectura y Urbanismo
    Asignatura("DA1111", "DA", "Geometría Descriptiva y Dibujo I", 3),
    Asignatura("PL1510", "PL", "Arquitectura y Urbanismo", 3),
    Asignatura("DA1112", "DA", "Geometría Descriptiva y Dibujo II", 3),
    Asignatura("FS1163", "FS", "Física Básica", 3),
    Asignatura("DA1113", "DA", "Dibujo y Perspectiva", 3),
    Asignatura("FS1117", "FS", "Física de las Estructuras", 3),

    // Ciclo básico de la Licenciatura en Biología
    Asignatura("EA2100", "EA", "Principios de Biología", 3),
    Asignatura("QM1121", "QM", "Química General I", 4),
    Asignatura("QM1122", "QM", "Química General II", 4),
    Asignatura("QM1181", "QM", "Laboratorio de Química General I", 2),

    // Ciclo básico de la Licenciatura en Gestión de la Hospitalidad
    Asignatura("FC1129", "FC", "Matemática I", 4),
    Asignatura("FC1505", "FC", "Lenguaje I", 3),
    Asignatura("FCA151", "FC", "Hombre Cultura y Sociedad I", 3),
    Asignatura("FC1221", "FC", "Inglés I", 3),
    Asignatura("TS1113", "TS", "Fundamentos de Administración", 3),

    Asignatura("FC1229", "FC", "Matemática II", 4),
    Asignatura("FC1515", "FC", "Lenguaje II", 3),
    Asignatura("FCA161", "FC", "Hombre Cultura y Sociedad II", 3),
    Asignatura("FC1224", "FC", "Inglés II", 3),
    Asignatura("TS1114", "TS", "Introducción a la Química", 3),

    Asignatura("FC3701", "FC", "Matemática Financiera", 4),
    Asignatura("FC1525", "FC", "Lenguaje III", 3),
    Asignatura("FCA171", "FC", "Hombre Cultura y Sociedad III", 3),
    Asignatura("FC1701", "FC", "Inglés III", 3),
    Asignatura("TS1724", "TS", "Contabilidad", 3),

    // Ciclo básico de Ingeniería de Mantenimiento
    Asignatura("FC1502", "FC", "Matemática I", 4),
    Asignatura("FC1504", "FC", "Inglés I", 3),
    Asignatura("FCA503", "FC", "Venezuela ante el Siglo XXI I", 3),
    Asignatura("FC1501", "FC", "Geometría", 2),

    Asignatura("FC1512", "FC", "Matemática II", 4),
    Asignatura("FC1514", "FC", "Inglés II", 3),
    Asignatura("FCA511", "FC", "Venezuela ante el Siglo XXI II", 3),
    Asignatura("FC1513", "FC", "Física I", 3),

    Asignatura("FC1524", "FC", "Matemática III", 4),
    Asignatura("FC1526", "FC", "Inglés III", 3),
    Asignatura("FCA521", "FC", "Venezuela ante el Siglo XXI III", 3),
    Asignatura("FC1527", "FC", "Física II", 3),

    // Ciclo básico de la Licenciatura en Comercio Internacional
    Asignatura("FC1221", "FC", "Inglés I", 3),
    Asignatura("FC1224", "FC", "Inglés II", 3),
    Asignatura("FC1701", "FC", "Inglés III", 3),

    // Ciclo básico de Economía
    Asignatura("CE3251", "CE", "Contabilidad Gerencial", 3),

    // Ciclo básico de la Licenciatura en Artes y Estudios Liberales
    Asignatura("FC0000", "FC", "Tutoría 0", 0),
    Asignatura("DAX101", "DA", "Introducción experiencia estética I", 3),
    Asignatura("FCX101", "FC", "Tópicos Especiales y Problemas de Ciencia", 3),

    //
    // Asignaturas en los Ciclos Profesionales
    //

    // MA
    Asignatura("MA2115", "MA", "Matemáticas IV", 4),
    Asignatura("MA2112", "MA", "Matemáticas V", 4),
    Asignatura("MA2113", "MA", "Matemáticas VI", 4),
    Asignatura("MA3111", "MA", "Matemáticas VII", 4),
    
    // FS
    Asignatura("FS2211", "FS", "Física III", 3),
    Asignatura("FS2212", "FS", "Física IV", 3),
    Asignatura("FS2213", "FS", "Física V", 3),
    Asignatura("FS2181", "FS", "Laboratorio de Física I", 2),
    Asignatura("FS2281", "FS", "Laboratorio de Física II", 2),

    // CO
    Asignatura("CO3121", "CO", "Fundaciones de Probabilidad y Estadística para Ingenieros", 3),
    Asignatura("CO3211", "CO", "Cálculo Numérico", 4),
    Asignatura("CO3321", "CO", "Estadística para Ingenieros", 4),

    // CI
    Asignatura("CI2125", "CI", "Computación I", 3),
    Asignatura("CI2511", "CI", "Lógica Simbólica", 4),
    Asignatura("CI2525", "CI", "Estructuras Discretas I", 4),
    Asignatura("CI2526", "CI", "Estructuras Discretas II", 4),
    Asignatura("CI2527", "CI", "Estructuras Discretas III", 4),
    Asignatura("CI2611", "CI", "Algoritmos y Estructuras I", 3),
    Asignatura("CI2612", "CI", "Algoritmos y Estructuras II", 3),
    Asignatura("CI2691", "CI", "Laboratorio de Algoritmos y Estructuras I", 2),
    Asignatura("CI2692", "CI", "Laboratorio de Algoritmos y Estructuras II", 2),
    Asignatura("CI2511", "CI", "Lógica Simbólica", 4),
    Asignatura("CI2526", "CI", "Estructuras Discretas II", 4),
    Asignatura("CI2527", "CI", "Estructuras Discretas III", 4),
    Asignatura("CI3815", "CI", "Organización del Computador", 5),
    Asignatura("CI2613", "CI", "Algoritmos y Estructuras III", 3),
    Asignatura("CI2693", "CI", "Laboratorio de Algoritmos y Estructuras III", 2),
    Asignatura("CI3825", "CI", "Sistemas de Operación", 5),
    Asignatura("CI3311", "CI", "Sistemas de Base de Datos I", 3),
    Asignatura("CI3391", "CI", "Laboratorio de Sistemas de Base de Datos I", 2),
    Asignatura("CI3715", "CI", "Ingeniería de Sotfware", 5),
    Asignatura("CI3725", "CI", "Traductores e Interpretadores", 5),
    Asignatura("CI4835", "CI", "Redes de Computadoras", 5),
    Asignatura("CI3641", "CI", "Lenguajes de Programación", 3),
    Asignatura("CI3661", "CI", "Laboratorio de Lenguajes de Programación", 2),
    Asignatura("CI4325", "CI", "Interfaces con el Usuario", 5),

    // EC
    Asignatura("EC1167", "EC", "Introducción a los Circuitos Electrónicos", 3),
    Asignatura("EC1168", "EC", "Análisis de Circuitos Electrónicos", 3),
    Asignatura("EC3713", "EC", "Electrónica Digital", 3),
    Asignatura("EC1311", "EC", "Teoría Electromagnética", 4),
    Asignatura("EC3192", "EC", "Laboratorio de Circuitos Electrónicos I", 2),
    Asignatura("EC3188", "EC", "Laboratorio de Electrónica Digital", 2),
    Asignatura("EC1251", "EC", "Análisis de Circuitos Eléctricos I", 3),
    Asignatura("EC2262", "EC", "Análisis de Circuitos Lineales", 3),
    Asignatura("EC2286", "EC", "Laboratorio de Mediciones Eléctricas", 2),
    
    // CT
    Asignatura("CT1212", "CT", "Introducción a la Ingeniería Eléctrica", 3),
    Asignatura("CT1311", "CT", "Conversión de Energía I", 4),
    Asignatura("CT3231", "CT", "Sistemas Eléctricos I", 3),
    Asignatura("CT3232", "CT", "Sistemas Eléctricos II", 3),
    Asignatura("CT3233", "CT", "Sistemas de Potencia I", 3),
    Asignatura("CT3331", "CT", "Accionamientos Eléctricos", 3),
    Asignatura("CT2311", "CT", "Conversión de Energía II", 4),
    Asignatura("CT3311", "CT", "Conversión de Energía III", 3),
    Asignatura("CT3413", "CT", "Sistemas Energéticos", 3),
    Asignatura("CT3415", "CT", "Máquinas Volumétricas", 4),
    Asignatura("CT4381", "CT", "Laboratorio de Conversión de Energía I", 2),
    Asignatura("CT4382", "CT", "Laboratorio de Conversión de Energía II", 2),
    Asignatura("CT4111", "CT", "Instalaciones de Alta Tensión", 3),
    Asignatura("CT4311", "CT", "Conversión de Energía IV", 3),
    Asignatura("CT4351", "CT", "Controladores de Potencia", 3),
    Asignatura("CT4211", "CT", "Sistemas de Potencia III", 3),
    Asignatura("CT4212", "CT", "Instalaciones de Media y Baja Tensión", 3),
    Asignatura("CT4611", "CT", "Taller de Proyectos", 3),
    Asignatura("CT4222", "CT", "Sistemas de Protección", 3),
    Asignatura("CT4234", "CT", "Sistemas de Potencia II", 3),
    Asignatura("CT4441", "CT", "Generación de Potencia I", 4),
    Asignatura("CT5215", "CT", "Líneas de Transmisión", 3),
    Asignatura("CT5442", "CT", "Generación de Potencia II", 3),
    Asignatura("CT3411", "CT", "Turbomáquinas Hidráulicas", 4),
    Asignatura("CT3412", "CT", "Turbomáquinas Térmicas", 4),

    // PS
    Asignatura("PS1111", "PS", "Modelos Lineales I", 4),
    Asignatura("PS1115", "PS", "Sistemas de Información I", 4),
    Asignatura("PS1314", "PS", "Sistemas de Control I", 3),
    Asignatura("PS1316", "PS", "Instrumentación y Control", 3),
    Asignatura("PS1381", "PS", "Laboratorio de Control", 2),
    Asignatura("PS2316", "PS", "Sistemas de Control II", 3),
    
    // EP
    Asignatura("EP1201", "EP", "Proyecto de Grado I", 3),
    Asignatura("EP1308", "EP", "Proyecto de Grado I", 3),
    Asignatura("EP2201", "EP", "Proyecto de Grado II", 3),
    Asignatura("EP2308", "EP", "Proyecto de Grado II", 3),
    Asignatura("EP3201", "EP", "Proyecto de Grado III", 3),
    Asignatura("EP3202", "EP", "Proyecto de Grado I", 3),
    Asignatura("EP3308", "EP", "Proyecto de Grado III", 3),
    Asignatura("EP4202", "EP", "Proyecto de Grado II", 3),
    Asignatura("EP5202", "EP", "Proyecto de Grado III", 3),
    Asignatura("EP5855", "EP", "Tópicos en Ingeniería de Computación", 4),
    Asignatura("EP5856", "EP", "Tópicos en Ingeniería de Computación", 4),
    
    // MC
    Asignatura("MC2131", "MC", "Dibujo Mecánico", 3),
    Asignatura("MC2141", "MC", "Mecánica de Materiales I", 3),
    Asignatura("MC2142", "MC", "Mecánica de Materiales II", 3),
    Asignatura("MC2143", "MC", "Mecánica de Materiales III", 3),
    Asignatura("MC2312", "MC", "Mecánica de Fluidos I", 3),
    Asignatura("MC2313", "MC", "Mecánica de Fluidos II", 3),
    Asignatura("MC2314", "MC", "Mecánica de Fluidos III", 3),
    Asignatura("MC2414", "MC", "Dinámica de Máquina", 3),
    Asignatura("MC2415", "MC", "Vibraciones Mecánicas", 3),
    Asignatura("MC2421", "MC", "Mecánica Computacional I", 3),
    Asignatura("MC2422", "MC", "Mecánica Computacional II", 3),
    Asignatura("MC2431", "MC", "Dinámica I", 4),
    Asignatura("MC2432", "MC", "Dinámica II", 4),
    Asignatura("MC3611", "MC", "Procesos de Fabricación I", 3),
    Asignatura("MC3612", "MC", "Procesos de Fabricación II", 3),
    Asignatura("MC4131", "MC", "Diseño de Máquina I", 3),
    Asignatura("MC4132", "MC", "Diseño de Máquinas II", 3),
    Asignatura("MC4133", "MC", "Metodología de Diseño", 3),

    // CE
    Asignatura("CE3114", "CE", "Economía de la Empresa", 3),
    Asignatura("CE3122", "CE", "Evaluación de Proyectos", 3),

    // TF
    Asignatura("TF1121", "TF", "Termodinámica I", 4),
    Asignatura("TF2123", "TF", "Termodinámica II", 4),
    Asignatura("TF2251", "TF", "Transferencia de Calor I", 3),
    Asignatura("TF2252", "TF", "Transferencia de Calor II", 4),

    // MT
    Asignatura("MT1113", "MT", "Materiales", 3),

    // EG
    Asignatura("EG2004", "EG", "Estudios Generales", 3),
    Asignatura("EG2005", "EG", "Estudios Generales", 3),
    Asignatura("EG2006", "EG", "Estudios Generales", 3),

    Asignatura("EG3007", "EG", "Estudios Generales", 3),
    Asignatura("EG3008", "EG", "Estudios Generales", 3),
    Asignatura("EG3009", "EG", "Estudios Generales", 3),

    Asignatura("EG4010", "EG", "Estudios Generales", 3),
    Asignatura("EG4011", "EG", "Estudios Generales", 3),
    Asignatura("EG4012", "EG", "Estudios Generales", 3),

    Asignatura("EG5013", "EG", "Estudios Generales", 3),
    Asignatura("EG5014", "EG", "Estudios Generales", 3),
    Asignatura("EG5015", "EG", "Estudios Generales", 3),

    // YC
    Asignatura("YC5013", "YC", "Electiva", 3),
    Asignatura("YC5014", "YC", "Electiva", 3),
    Asignatura("YC5015", "YC", "Electiva", 3),
    Asignatura("YC5115", "YC", "Laboratorio Electivo", 3),

    // DA
    Asignatura("DA2563", "DA", "Electiva de Área", 4),
    Asignatura("DA3311", "DA", "Electiva de Área", 4),
    Asignatura("DA4011", "DA", "Electiva de Área", 4),
    Asignatura("DA4111", "DA", "Electiva de Área", 4),
    Asignatura("DA5113", "DA", "Electiva de Área", 4),
};


Asignatura::Asignatura(Codigo codigo, Codigo departamento, Descripcion descripcion, uint8_t uc)
:
    codigo_(codigo),
    departamento_(departamento),
    descripcion_(descripcion),
    uc_(uc)
{}

Asignatura::~Asignatura() throw() {}

const vector<Asignatura>& Asignatura::tabla() {
    return tabla_;
}

string Asignatura::str() const {
    return string("( ") + codigo_.str() + ", " + descripcion_ + ", " + std::to_string(uc_) + ")";
}

string Asignatura::json() const {
    return string("")
        + "{ codigo: " + codigo_.str()
        + ", departamento: " + departamento_.str()
        + ", descripcion: " + descripcion_
        + ", uc: " + std::to_string(uc_)
        + " }";
}
