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

bool EscritorResultados::guardar_resumen(const std::string& filename, const std::vector<Centroide>& centroides, double dispersion) {
    std::ofstream archivo(filename);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de reporte " << filename << std::endl;
        return false;
    }

    archivo << std::fixed << std::setprecision(6);
    archivo << "========================================\n";
    archivo << "     NAGYSOFT - REPORTE DE CLUSTERING   \n";
    archivo << "========================================\n\n";
    
    archivo << "CENTROIDES ENCONTRADOS (Posiciones finales):\n";
    archivo << "----------------------------------------\n";
    for (const auto& centroide : centroides) {
        archivo << "Cluster " << centroide.etiqueta << " -> X: " 
                << std::setw(10) << centroide.posicion.x << " | Y: " 
                << std::setw(10) << centroide.posicion.y << " | Z: " 
                << std::setw(10) << centroide.posicion.z << "\n";
    }
    archivo << "----------------------------------------\n\n";

    // Requisito del Dr. Szilard: Presentar la medida de dispersión estadística lograda
    archivo << "METRICA DE EVALUACION ESTADISTICA:\n";
    archivo << "Dispersion Total (SSE/Inercia): " << dispersion << "\n";
    archivo << "\n[Fin del Reporte Ejecutivo]\n";

    std::cout << "Reporte estadistico '" << filename << "' generado exitosamente." << std::endl;
    return true;
}