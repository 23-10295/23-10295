#include "cargador.h"
#include "kmeans.h"
#include "escritor.h" // <--- Nuevo enlace de salida
#include <iostream>
#include <string>

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error en los parametros." << std::endl;
        std::cerr << "Uso correcto: cluster <k> <nombre_del_archivo>" << std::endl;
        return 1; 
    }

    int k = std::stoi(argv[1]);
    std::string filename = argv[2];

    if (k < 1 || k > 6) {
        std::cerr << "Error: El numero de clusters (k) debe estar entre 1 y 6." << std::endl;
        return 1;
    }

    std::cout << "=== Procesando pauta de NagySoft ===" << std::endl;
    std::cout << "Target de Clusters (k): " << k << std::endl;
    std::cout << "Archivo de origen: " << filename << std::endl;
    std::cout << "------------------------------------" << std::endl;

    if (!BaseDatos::cargar_desde_archivo(filename)) {
        std::cerr << "Error critico: No se pudo inicializar la base de datos." << std::endl;
        return 1;
    }

    const auto& datos = BaseDatos::obtener_datos();
    
    // Ejecución del motor algorítmico
    std::vector<Centroide> centroides_finales;
    std::vector<PuntoClasificado> puntos_procesados = MotorKMeans::ejecutar(k, datos, centroides_finales);

    // Evaluación métrica
    double metrica_dispersion = MotorKMeans::calcular_dispersion_total(puntos_procesados, centroides_finales);
    std::cout << "Medida de Dispersion Total (Inercia SSE): " << metrica_dispersion << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // Generación automatizada de los archivos exigidos por la empresa
    if (!EscritorResultados::guardar_puntos_clasificados("clasificados.csv", puntos_procesados)) {
        return 1;
    }
    
 // Le pasamos 'puntos_procesados' en lugar de la dispersión total
    if (!EscritorResultados::guardar_resumen("summary.txt", centroides_finales, puntos_procesados)) {
        return 1;
    }

    std::cout << "====================================" << std::endl;
    std::cout << "PROCESO COMPLETADO CON EXITO TOTAL" << std::endl;
    std::cout << "====================================" << std::endl;

    return 0;
}