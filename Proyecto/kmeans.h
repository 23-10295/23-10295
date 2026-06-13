///
/// kmeans.h
/// Módulo encargado del algoritmo de agrupamiento y cálculos de dispersión estadística.
///

#pragma once

#include "cargador.h" // Para usar Coord_3D
#include <vector>

// Estructura para representar un Cluster/Centroide
struct Centroide {
    Coord_3D posicion;
    char etiqueta; // 'A', 'B', 'C', 'D', 'E' o 'F'
};

// Estructura para almacenar un punto ya clasificado
struct PuntoClasificado {
    Coord_3D coordenadas;
    char cluster_asignado;
};

class MotorKMeans {
public:
    // Función principal que ejecuta el algoritmo K-Means
    // Recibe el número de clusters (k) y el vector de datos inmutable
    static std::vector<PuntoClasificado> ejecutar(int k, const std::vector<Coord_3D>& datos, std::vector<Centroide>& centroides_finales);

    // Calcula la Distancia Euclidiana en el espacio 3D
    static double calcular_distancia(const Coord_3D& p1, const Coord_3D& p2);

    // Calcula la dispersión total (Inercia) para evaluar el ajuste del modelo y prevenir Overfitting
    static double calcular_dispersion_total(const std::vector<PuntoClasificado>& puntos_clasificados, const std::vector<Centroide>& centroides);
};