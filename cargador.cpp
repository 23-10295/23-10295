#include "cargador.h"
#include <fstream>   
#include <sstream>   
#include <iostream>  
#include <string>

const bool debug_mode = true;
static std::vector<Coord_3D> datos_originales = {};

bool BaseDatos::cargar_desde_archivo(const std::string& filename) {
    std::ifstream archivo(filename);
    if (!archivo.is_open()) {
        std::cerr << "Error: El archivo " << filename << " no pudo ser abierto." << std::endl;
        return false;
    }

    datos_originales.clear();
    std::string linea;
    
    if (debug_mode) {
        std::cout << "Iniciando lectura en modo C++ puro de: " << filename << std::endl;
    }

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string s_x, s_y, s_z;

        if (std::getline(ss, s_x, ',') && 
            std::getline(ss, s_y, ',') && 
            std::getline(ss, s_z, ',')) {
            
            try {
                Coord_3D punto;
                punto.x = std::stod(s_x);
                punto.y = std::stod(s_y);
                punto.z = std::stod(s_z);
                datos_originales.push_back(punto);

                if (debug_mode) {
                    std::cout << "Punto cargado -> X: " << punto.x << ", Y: " << punto.y << ", Z: " << punto.z << std::endl;
                }
            } 
            catch (const std::exception& e) {
                std::cerr << "Error al convertir datos en la linea: " << linea << std::endl;
            }
        }
    }
    std::cout << "Carga finalizada con exito. " << datos_originales.size() << " puntos cargados." << std::endl;
    return true;
}

const std::vector<Coord_3D>& BaseDatos::obtener_datos() {
    return datos_originales;
}