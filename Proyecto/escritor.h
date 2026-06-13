#pragma once

#include "kmeans.h" 
#include <vector>
#include <string>

class EscritorResultados {
public:
   
    static bool guardar_puntos_clasificados(const std::string& filename, const std::vector<PuntoClasificado>& puntos);

    static bool guardar_resumen(const std::string& filename, const std::vector<Centroide>& centroides, const std::vector<PuntoClasificado>& puntos);
};  