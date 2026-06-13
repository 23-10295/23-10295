#pragma once
#include "cargador.h" 
#include <vector>

struct Centroide {
    Coord_3D posicion;
    char etiqueta; // 'A', 'B', 'C', 'D', 'E' o 'F'
};

struct PuntoClasificado {
    Coord_3D coordenadas;
    char cluster_asignado;
};

class MotorKMeans {
public:
   
    static std::vector<PuntoClasificado> ejecutar(int k, const std::vector<Coord_3D>& datos, std::vector<Centroide>& centroides_finales);

   
    static double calcular_distancia(const Coord_3D& p1, const Coord_3D& p2);

  
    static double calcular_dispersion_total(const std::vector<PuntoClasificado>& puntos_clasificados, const std::vector<Centroide>& centroides);
};
