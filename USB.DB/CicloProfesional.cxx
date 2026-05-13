///
/// Ciclo Profesional (implementación)
///

#include "CicloProfesional.h"
#include "Carrera.h"
#include "CicloBasico.h"

using std::string;
using std::vector;

// Ingenieria Eléctrica
Ciclo ingenieria_electrica = {
    mfq1,
    {
        { "MA2115", "EC1251", "FS2211", "FS2181", "EG2004" },
        { "MA2112", "EC2262", "FS2212", "CT1212", "CI2125" },
        { "MA2113", "CT3231", "FS2213", "EC2286", "MC2141" }
    },
    {
        { "MA3111", "EC1167", "CT3232", "EC1311" }, 
        { "PS1314", "EC1168", "CT3233", "CT1311", "EC3192" },
        { "PS2316", "EC3713", "CT4234", "CT2311", "PS1381" }
    },
    {
        { "CT4381", "CT3311", "CO3121", "EC3188", "EG4010", "CT4211" },
        { "CT4311", "CT4212", "CT4382", "CT4441", "EG4011" },
        { "CT4351", "CT4611", "CT4222", "CT5442", "EG4012" }
    },
    {
        { "EP1201", "CE3114", "YC5013", "EG5013" },
        { "CT4111", "EP2201", "YC5014", "EG5014" },
        { "EP3201", "CT5215", "YC5015", "YC5115" }
    }
};

// Ingenieria Mecánica
Ciclo ingenieria_mecanica = {
    mfq1,
    {
        { "MA2115", "QM1121", "FS2211", "FS2181" },
        { "MA2112", "MC2421", "FS2212", "MC2131", "FS2281" },
        { "MA2113", "MC2141", "MC2422", "EG2006" }
    },
    {
        { "MA3111", "MC2142", "MC2431", "TF1121" },
        { "MC2143", "MC2432", "MC2312", "TF2123" },
        { "MC2313", "MC2415", "TF2251", "MT1113", "EG3009" }
    },
    {
        { "TF2252", "MC4131", "MC2414", "MC2314", "EG4010" },
        { "CT3411", "MC4132", "MC3611", "CT3331" },
        { "MC3612", "CT3412", "MC4133", "PS1316", "CE3114" }
    },
    {
        { "EP3202", "CE3122", "EG5013", "YC5013" },
        { "EP4202", "CT3415", "EG5014", "YC5014", "YC5114" },
        { "EP5202", "CT3413", "YC5015", "YC5115" }
    }
};

// Ingenieria Electrónica
Ciclo ingenieria_electronica = {
    mfq1,
    {
        { "MA2115", "FS2211", "EC1251", "FS2181", "EG2004" },
        { "MA2112", "FS2212", "EC2272", "EC1281", "EG2005" },
        { "MA2113", "FS2213", "PS2315", "CI2125", "FS2282" }
    },
    {
        { "MA3111", "EC1177", "CI2126", "EC1723" },
        { "CO3121", "EC2178", "EC2721", "CE2562", "EG3008" },
        { "EC1421", "EC1311", "EC3731", "EG3009" }
    },
    {
        { "EC2422", "EC2322", "EC3179", "EC3881" },
        { "EC3423", "PS2322", "EC4179", "EC3882" },
        { "PS2323", "CE3122", "EC3883", "EG4012" }
    },
    {
        { "EP1206", "EC4434", "EC5751", "EC3173" },
        { "EP2206", "YC5014", "YC5114", "YC5214", "EG5014" },
        { "EP3206", "YC5015", "YC5115", "YC5215" }
    }
};

// Ingeniería de Computación
Ciclo ingenieria_de_computacion = {
    mfq1,
    {
        { "MA2115", "CI2511", "CI2525", "EG3007" },
        { "MA2112", "CI2611", "CI2691", "CI2526" },
        { "CO3211", "CI2612", "CI2692", "CI2527" }
    },
    {
        { "CO3121", "CI3815", "CI2613", "CI2693", "EG3007" },
        { "CO3321", "CI3825", "CI3311", "CI3391" },
        { "PS1115", "CI3715", "CI3725" }
    },
    {
        { "PS1111", "CI4835", "CI3641", "CI3661" },
        { "CI4325", "DA4011", "DA4111", "EG4011" },
        { "DA3311", "DA2563", "EG4012" }
    },
    {
        { "EP1308", "EP5855", "YC5013", "DA5113" },
        { "EP2308", "EP5856", "YC5014", "EG5014" },
        { "EP3308", "YC5015", "EG5015" }
    }
};

static const Ciclo& ciclo(Codigo carrera) {
    // inelegante y a fuerza bruta .. por ahora
    if (carrera.str() == Codigo("0100").str()) {
        return ingenieria_electrica;
    }
    if (carrera.str() == Codigo("0200").str()) {
        return ingenieria_mecanica;
    }
    if (carrera.str() == Codigo("0600").str()) {
        return ingenieria_electronica;
    }
    if (carrera.str() == Codigo("0800").str()) {
        return ingenieria_de_computacion;
    }
    fprintf(stderr, "Ciclo Profesional %s no esta soportado\n", carrera.c_str());
    fprintf(stderr, "code invariant violation .. aborting");
    exit(EXIT_FAILURE);
}

const Trimestre& CicloProfesional::asignaturas(Codigo carrera, int uyear, int trimestre) {
    return ciclo(carrera)[uyear - 1][trimestre - 1];
}

static const vector<Codigo> carreras_ = {
    Codigo("0100"),     // Ingenieria Eléctrica
    Codigo("0200"),     // Ingenieria Mecánica
    Codigo("0600"),     // Ingenieria Electrónica
    Codigo("0800")      // Ingeniería de Computación
};

const vector<Codigo>& CicloProfesional::carreras() {
    return carreras_;
}
