#pragma once
#include <vector>
#include <string>

struct Coord_3D {
    double x;
    double y;
    double z;
};

class BaseDatos {
public:
    static bool cargar_desde_archivo(const std::string& filename);
    static const std::vector<Coord_3D>& obtener_datos();
};