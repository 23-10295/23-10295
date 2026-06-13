#include "kmeans.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

double MotorKMeans::calcular_distancia(const Coord_3D& p1, const Coord_3D& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double MotorKMeans::calcular_dispersion_total(const std::vector<PuntoClasificado>& puntos_clasificados, const std::vector<Centroide>& centroides) {
    double suma_dispersión = 0.0;
    for (const auto& punto : puntos_clasificados) {
        for (const auto& centroide : centroides) {
            if (centroide.etiqueta == punto.cluster_asignado) {
                double dist = calcular_distancia(punto.coordenadas, centroide.posicion);
                suma_dispersión += (dist * dist); 
                break;
            }
        }
    }
    return suma_dispersión;
}

std::vector<PuntoClasificado> MotorKMeans::ejecutar(int k, const std::vector<Coord_3D>& datos, std::vector<Centroide>& centroides_finales) {
    std::vector<Centroide> centroides(k);
    
    std::srand(42);

    for (int i = 0; i < k; ++i) {
        int indice_azar = std::rand() % datos.size();
        centroides[i].posicion = datos[indice_azar];
        centroides[i].etiqueta = static_cast<char>('A' + i); // Asigna 'A', 'B', 'C'...
    }

    std::vector<PuntoClasificado> resultado(datos.size());
    bool centroides_movidos = true;
    int iteracion = 0;
    const int max_iteraciones = 100;

    while (centroides_movidos && iteracion < max_iteraciones) {
        centroides_movidos = false;
        iteracion++;
        
        for (size_t i = 0; i < datos.size(); ++i) {
            double dist_minima = 99999999.0;
            char mejor_etiqueta = 'A';

            for (int j = 0; j < k; ++j) {
                double dist = calcular_distancia(datos[i], centroides[j].posicion);
                if (dist < dist_minima) {
                    dist_minima = dist;
                    mejor_etiqueta = centroides[j].etiqueta;
                }
            }
            resultado[i].coordenadas = datos[i];
            resultado[i].cluster_asignado = mejor_etiqueta;
        }

        for (int j = 0; j < k; ++j) {
            double suma_x = 0.0, suma_y = 0.0, suma_z = 0.0;
            int conteo_puntos = 0;

            for (const auto& punto : resultado) {
                if (punto.cluster_asignado == centroides[j].etiqueta) {
                    suma_x += punto.coordenadas.x;
                    suma_y += punto.coordenadas.y;
                    suma_z += punto.coordenadas.z;
                    conteo_puntos++;
                }
            }

            if (conteo_puntos > 0) {
                Coord_3D nueva_pos = { suma_x / conteo_puntos, suma_y / conteo_puntos, suma_z / conteo_puntos };
                
                if (calcular_distancia(centroides[j].posicion, nueva_pos) > 0.0001) {
                    centroides[j].posicion = nueva_pos;
                    centroides_movidos = true;
                }
            }
        }
    }

    std::cout << "Algoritmo K-Means convergio de forma exitosa en la iteracion: " << iteracion << std::endl;
    centroides_finales = centroides;
    return resultado;
}
