import sqlite3
import random

def inicializar_base_de_datos():
    conn = sqlite3.connect('dacex.db')
    cursor = conn.cursor()

    # 1. Eliminar tablas previas si existen
    cursor.execute("DROP TABLE IF EXISTS inscripciones")
    cursor.execute("DROP TABLE IF EXISTS historial_materias")
    cursor.execute("DROP TABLE IF EXISTS materias")
    cursor.execute("DROP TABLE IF EXISTS usuarios")
    cursor.execute("DROP TABLE IF EXISTS carreras")

    # 2. Crear tablas
    cursor.execute("""
        CREATE TABLE carreras (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL UNIQUE
        )
    """)

    cursor.execute("""
        CREATE TABLE usuarios (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            carnet TEXT UNIQUE NOT NULL,
            nombre TEXT NOT NULL,
            password TEXT NOT NULL,
            rol TEXT NOT NULL,
            carrera_id INTEGER,
            carrera TEXT,
            indice REAL DEFAULT 0.0,
            ano_actual INTEGER DEFAULT 1,
            FOREIGN KEY (carrera_id) REFERENCES carreras (id)
        )
    """)

    cursor.execute("""
        CREATE TABLE materias (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            codigo TEXT NOT NULL,
            nombre TEXT NOT NULL,
            creditos INTEGER NOT NULL,
            ano TEXT NOT NULL,
            carrera_id INTEGER NOT NULL,
            cupos_max INTEGER DEFAULT 30,
            cupos_disponibles INTEGER DEFAULT 5,
            FOREIGN KEY (carrera_id) REFERENCES carreras (id)
        )
    """)

    cursor.execute("""
        CREATE TABLE historial_materias (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            usuario_id INTEGER NOT NULL,
            materia_id INTEGER NOT NULL,
            nota INTEGER NOT NULL,
            estado TEXT NOT NULL,
            FOREIGN KEY (usuario_id) REFERENCES usuarios (id),
            FOREIGN KEY (materia_id) REFERENCES materias (id)
        )
    """)

    cursor.execute("""
        CREATE TABLE inscripciones (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            usuario_id INTEGER NOT NULL,
            materia_id INTEGER NOT NULL,
            fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (usuario_id) REFERENCES usuarios (id),
            FOREIGN KEY (materia_id) REFERENCES materias (id)
        )
    """)

    # 3. Insertar Carreras
    carreras = [
        ("Ingeniería en Computación",),
        ("Ingeniería Eléctrica",)
    ]
    cursor.executemany("INSERT INTO carreras (nombre) VALUES (?)", carreras)

    # 4. Insertar Usuarios (20 Estudiantes distribuídos en varios años + 1 Administrador)
    usuarios = [
        ("21-10001", "María Rodríguez", "1234", "estudiante", 1, "Ingeniería en Computación", 4.25, 2),
        ("20-10002", "Carlos Pérez", "1234", "estudiante", 2, "Ingeniería Eléctrica", 3.80, 2),
        ("23-10484", "Mariana Torres", "1234", "estudiante", 1, "Ingeniería en Computación", 4.50, 3),
        ("23-10295", "Adrian Mijares", "1234", "estudiante", 1, "Ingeniería en Computación", 3.65, 1),
        ("24-10230", "Diego Garcia", "1234", "estudiante", 2, "Ingeniería Eléctrica", 4.10, 3),
        ("21-10006", "Gabriel Torres", "1234", "estudiante", 1, "Ingeniería en Computación", 3.90, 2),
        ("20-10007", "Elena Ramírez", "1234", "estudiante", 2, "Ingeniería Eléctrica", 4.75, 5),
        ("21-10008", "Alejandro Díaz", "1234", "estudiante", 1, "Ingeniería en Computación", 3.40, 1),
        ("20-10009", "Valentina Morales", "1234", "estudiante", 2, "Ingeniería Eléctrica", 4.05, 4),
        ("21-10010", "José Castillo", "1234", "estudiante", 1, "Ingeniería en Computación", 4.80, 4),
        ("21-10011", "Camila Flores", "1234", "estudiante", 1, "Ingeniería en Computación", 3.70, 2),
        ("20-10012", "Fernando Vargas", "1234", "estudiante", 2, "Ingeniería Eléctrica", 3.55, 1),
        ("21-10013", "Isabella Mendoza", "1234", "estudiante", 1, "Ingeniería en Computación", 4.30, 3),
        ("20-10014", "Diego Silva", "1234", "estudiante", 2, "Ingeniería Eléctrica", 4.15, 2),
        ("21-10015", "Daniela Romero", "1234", "estudiante", 1, "Ingeniería en Computación", 3.85, 1),
        ("20-10016", "Javier Navarro", "1234", "estudiante", 2, "Ingeniería Eléctrica", 4.60, 4),
        ("21-10017", "Mariana Reyes", "1234", "estudiante", 1, "Ingeniería en Computación", 4.40, 2),
        ("20-10018", "Andrés Gil", "1234", "estudiante", 2, "Ingeniería Eléctrica", 3.95, 3),
        ("21-10019", "Natalia Acosta", "1234", "estudiante", 1, "Ingeniería en Computación", 4.10, 1),
        ("20-10020", "Ricardo Medina", "1234", "estudiante", 2, "Ingeniería Eléctrica", 4.20, 5),
        ("admin", "Administrador DACEX", "admin123", "administrador", None, "Administración Central", 0.0, 0)
    ]
    cursor.executemany("""
        INSERT INTO usuarios (carnet, nombre, password, rol, carrera_id, carrera, indice, ano_actual)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?)
    """, usuarios)

    # 5. Insertar Pensums Completos
    pensums = {
        # Carrera 1: Ingeniería en Computación
        1: {
            "Año 1": [
                ("MA-1111", "Matemáticas 1", 4),
                ("MA-1121", "Matemáticas de Honor 1", 4),
                ("FS-1111", "Física 1", 4),
                ("MA-1112", "Matemáticas 2", 4),
                ("MA-1122", "Matemáticas de Honor 2", 4),
                ("FS-1112", "Física 2", 4),
                ("MA-1116", "Matemáticas 3", 4),
                ("MA-1123", "Matemáticas de Honor 3", 4)
            ],
            "Año 2": [
                ("CI-2525", "Estructuras Discretas 1", 3),
                ("CI-2511", "Lógica Simbólica", 3),
                ("MA-2115", "Matemáticas 4", 4),
                ("CI-2611", "Algoritmos y Estructuras 1", 3),
                ("CI-2526", "Estructuras Discretas 2", 3),
                ("CI-2691", "Laboratorio de Algoritmos y Estructuras 1", 2),
                ("MA-2112", "Matemáticas 5", 4),
                ("CI-2612", "Algoritmos y Estructuras 2", 3),
                ("CO-3211", "Cálculo Numérico", 3),
                ("CI-2527", "Estructuras Discretas 3", 3),
                ("CI-2692", "Laboratorio de Algoritmos y Estructuras 2", 2)
            ],
            "Año 3": [
                ("CI-2613", "Algoritmos y Estructuras 3", 3),
                ("CI-2693", "Laboratorio de Algoritmos y Estructuras 3", 2),
                ("CI-3815", "Organización del Computador", 3),
                ("CO-3121", "Probabilidades para Ingenieros", 3),
                ("CO-3321", "Estadística", 3),
                ("CI-3391", "Laboratorio de Sistemas de Base de Datos 1", 2),
                ("CI-3311", "Sistemas de Base de Datos 1", 3),
                ("CI-3825", "Sistemas de Operación", 3),
                ("CI-3715", "Ingeniería de Software 1", 3),
                ("PS-1115", "Sistemas de Información 1", 3),
                ("CI-3725", "Traductores e Interpretadores", 3)
            ],
            "Año 4": [
                ("CI-3661", "Laboratorio de Lenguajes de Programación", 2),
                ("CI-3641", "Lenguajes de Programación", 3),
                ("PS-1111", "Modelos Lineales 1", 3),
                ("CI-4835", "Redes de Computadoras", 3),
                ("CI-4325", "Interfaces con el Usuario", 3)
            ]
        },
        # Carrera 2: Ingeniería Eléctrica
        2: {
            "Año 1": [
                ("MA-1111", "Matemáticas 1", 4),
                ("MA-1121", "Matemáticas de Honor 1", 4),
                ("FS-1111", "Física 1", 4),
                ("MA-1112", "Matemáticas 2", 4),
                ("MA-1122", "Matemáticas de Honor 2", 4),
                ("FS-1112", "Física 2", 4),
                ("MA-1116", "Matemáticas 3", 4),
                ("MA-1123", "Matemáticas de Honor 3", 4)
            ],
            "Año 2": [
                ("EC-1251", "Circuitos Eléctricos 1", 3),
                ("EC-1021", "Circuitos Eléctricos 1 (Alt)", 3),
                ("FS-2211", "Física 3", 4),
                ("FS-2181", "Laboratorio de Física 1", 2),
                ("MA-2115", "Matemáticas 4", 4),
                ("EC-2262", "Análisis de Circuitos Lineales", 3),
                ("CI-2125", "Computación 1", 3),
                ("FS-2212", "Física 4", 4),
                ("CT-1212", "Introducción a la Ingeniería Eléctrica", 3),
                ("MA-2112", "Matemáticas 5", 4),
                ("FS-2213", "Física 5", 4),
                ("EC-2286", "Laboratorio de Mediciones Eléctricas", 2),
                ("MA-2113", "Matemáticas 6", 4),
                ("MC-2141", "Mecánica de Materiales 1", 3),
                ("CT-3231", "Sistemas Eléctricos 1", 3)
            ],
            "Año 3": [
                ("EC-1167", "Introducción a Circuitos Electrónicos", 3),
                ("MA-3111", "Matemáticas 7", 4),
                ("CT-3232", "Sistemas Eléctricos 2", 3),
                ("EC-1311", "Teoría Electromagnética", 3),
                ("EC-1168", "Análisis de los Circuitos Electrónicos", 3),
                ("CT-1311", "Conversión de Energía 1", 3),
                ("EC-3192", "Laboratorio de Circuitos Electrónicos", 2),
                ("PS-1314", "Sistemas de Control 1", 3),
                ("CT-3233", "Sistemas de Potencia 1", 3),
                ("CT-2311", "Conversión de Energía 2", 3),
                ("EC-3713", "Electrónica Digital", 3),
                ("PS-1381", "Laboratorio de Control", 2),
                ("PS-2316", "Sistemas de Control 2", 3),
                ("CT-4234", "Sistemas de Potencia 2", 3)
            ],
            "Año 4": [
                ("CT-3311", "Conversión de Energía 3", 3),
                ("CO-3121", "Probabilidades para Ingenieros", 3),
                ("CT-4381", "Laboratorio de Conversión de Energía 1", 2),
                ("EC-3188", "Laboratorio de Electrónica Digital", 2),
                ("CT-4211", "Sistemas de Potencia 3", 3),
                ("CT-4311", "Conversión de Energía 4", 3),
                ("CT-4441", "Generación de Potencia 1", 3),
                ("CT-4212", "Instalaciones de Media y Baja Tensión", 3),
                ("CT-4382", "Laboratorio de Conversión de Energía 2", 2),
                ("CT-4351", "Controladores de Potencia", 3),
                ("CT-5442", "Generación de Potencia 2", 3),
                ("CT-4222", "Sistemas de Protección", 3),
                ("CT-4611", "Taller de Proyectos", 3)
            ],
            "Año 5": [
                ("CE-3114", "Economía de la Empresa", 3),
                ("CT-4111", "Instalaciones de Alta Tensión", 3),
                ("CT-5215", "Líneas de Transmisión", 3)
            ]
        }
    }

    for carrera_id, anos in pensums.items():
        for ano_nombre, lista_materias in anos.items():
            for codigo, nombre, creditos in lista_materias:
                # Asigna de 1 a 5 cupos disponibles aleatorios para simular demanda
                cupos_rand = random.randint(1, 5)
                cursor.execute("""
                    INSERT INTO materias (codigo, nombre, creditos, ano, carrera_id, cupos_max, cupos_disponibles)
                    VALUES (?, ?, ?, ?, ?, 30, ?)
                """, (codigo, nombre, creditos, ano_nombre, carrera_id, cupos_rand))

    # 6. Historial de materias aprobadas (Aprobar años anteriores según el ano_actual del estudiante)
    cursor.execute("SELECT id, carrera_id, ano_actual FROM usuarios WHERE rol = 'estudiante'")
    estudiantes = cursor.fetchall()

    for est_id, carrera_id, ano_actual in estudiantes:
        # Aprobación de materias de todos los años anteriores al actual
        for past_year in range(1, ano_actual):
            string_ano = f"Año {past_year}"
            cursor.execute("SELECT id FROM materias WHERE carrera_id = ? AND ano = ?", (carrera_id, string_ano))
            mats_pasadas = cursor.fetchall()
            for m in mats_pasadas:
                nota_rand = random.choice([3, 4, 5])
                cursor.execute("""
                    INSERT INTO historial_materias (usuario_id, materia_id, nota, estado)
                    VALUES (?, ?, ?, 'pasada')
                """, (est_id, m[0], nota_rand))

    conn.commit()
    conn.close()
    print("¡Base de datos dacex.db inicializada con éxito con los nuevos pensums y 20 estudiantes!")

if __name__ == '__main__':
    inicializar_base_de_datos()