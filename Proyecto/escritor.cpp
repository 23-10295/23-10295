#include "escritor.h"
#include <fstream>
#include <iostream>
#include <iomanip> // Para fijar el número de decimales en la salida

bool EscritorResultados::guardar_puntos_clasificados(const std::string& filename, const std::vector<PuntoClasificado>& puntos) {
    std::ofstream archivo(filename);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de salida " << filename << std::endl;
        return false;
    }

    archivo << std::fixed << std::setprecision(6);

    for (const auto& punto : puntos) {
        archivo << punto.coordenadas.x << ","
                << punto.coordenadas.y << ","
                << punto.coordenadas.z << ","
                << punto.cluster_asignado << "\n"; // Salto de línea estricto
    }

    std::cout << "Archivo '" << filename << "' generado exitosamente con " << puntos.size() << " registros." << std::endl;
    return true;
}

bool EscritorResultados::guardar_resumen(const std::string& filename, const std::vector<Centroide>& centroides, const std::vector<PuntoClasificado>& puntos) {
    std::ofstream archivo(filename);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de reporte " << filename << std::endl;
        return false;
    }

    archivo << std::fixed << std::setprecision(6);
    
    for (const auto& centroide : centroides) {
        int N = 0;
        double MD_cluster = 0.0;
        
        for (const auto& punto : puntos) {
            if (punto.cluster_asignado == centroide.etiqueta) {
                N++;
                // Usamos la función pública que ya tenías en K-Means para calcular la distancia
                double dist = MotorKMeans::calcular_distancia(punto.coordenadas, centroide.posicion);
                MD_cluster += (dist * dist);
            }
        }

        archivo << centroide.etiqueta << ": " << N << ", (" 
                << centroide.posicion.x << ", " 
                << centroide.posicion.y << ", " 
                << centroide.posicion.z << "), " 
                << MD_cluster << "\n";
    }

    std::cout << "Reporte estadistico '" << filename << "' generado exitosamente." << std::endl;
    return true;
}
