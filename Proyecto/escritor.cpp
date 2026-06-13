///
/// escritor.cpp
/// Implementación de los formateadores de archivos CSV y reportes de texto plano.
///

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

    // Configuramos para que exporte siempre con notación decimal fija de 6 dígitos (estándar CSV)
    archivo << std::fixed << std::setprecision(6);

    // Escribimos cada punto seguido por su etiqueta de grupo
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

    // Fijamos los decimales a 6 como lo tenías
    archivo << std::fixed << std::setprecision(6);
    
    // Iteramos sobre cada centroide para contar sus puntos y calcular su MD
    for (const auto& centroide : centroides) {
        int N = 0;
        double MD_cluster = 0.0;
        
        // Contamos los puntos de este cluster específico y sumamos su dispersión
        for (const auto& punto : puntos) {
            if (punto.cluster_asignado == centroide.etiqueta) {
                N++;
                // Usamos la función pública que ya tenías en K-Means para calcular la distancia
                double dist = MotorKMeans::calcular_distancia(punto.coordenadas, centroide.posicion);
                MD_cluster += (dist * dist);
            }
        }

        // Imprimimos en el formato EXACTO: Letra: N, (x, y, z), MD
        archivo << centroide.etiqueta << ": " << N << ", (" 
                << centroide.posicion.x << ", " 
                << centroide.posicion.y << ", " 
                << centroide.posicion.z << "), " 
                << MD_cluster << "\n";
    }

    std::cout << "Reporte estadistico '" << filename << "' generado exitosamente." << std::endl;
    return true;
}