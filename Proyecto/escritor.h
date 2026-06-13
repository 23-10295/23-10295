///
/// escritor.h
/// Módulo encargado de la exportación de resultados y generación de reportes requeridos.
///

#pragma once

#include "kmeans.h" // Para usar PuntoClasificado y Centroide
#include <vector>
#include <string>

class EscritorResultados {
public:
    // Genera el archivo obligatorio 'clasificados.csv' con los puntos etiquetados
    static bool guardar_puntos_clasificados(const std::string& filename, const std::vector<PuntoClasificado>& puntos);

    // Genera el reporte obligatorio 'summary.txt' con los centroides y la dispersión final
    static bool guardar_resumen(const std::string& filename, const std::vector<Centroide>& centroides, double dispersion);
};