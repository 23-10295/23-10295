import sqlite3
import random
from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'dacex_clave_secreta_para_sesiones'

def obtener_conexion_db():
    conn = sqlite3.connect('dacex.db')
    conn.row_factory = sqlite3.Row
    return conn

def init_db_extra():
    """Inicializa la tabla de inscripciones y simula cupos de materias si no existen."""
    conn = obtener_conexion_db()
    cursor = conn.cursor()
    
    # Crear tabla de inscripciones activas
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS inscripciones (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            usuario_id INTEGER,
            materia_id INTEGER,
            fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (usuario_id) REFERENCES usuarios (id),
            FOREIGN KEY (materia_id) REFERENCES materias (id)
        )
    """)
    
    # Agregar columnas de cupos en materias si no existen
    cursor.execute("PRAGMA table_info(materias)")
    columnas = [col[1] for col in cursor.fetchall()]
    
    if 'cupos_max' not in columnas:
        cursor.execute("ALTER TABLE materias ADD COLUMN cupos_max INTEGER DEFAULT 30")
    if 'cupos_disponibles' not in columnas:
        cursor.execute("ALTER TABLE materias ADD COLUMN cupos_disponibles INTEGER DEFAULT 30")
        conn.commit()
        
        # Simular asignación de cupos por los demás estudiantes (casi llenos: entre 1 y 5 cupos disponibles)
        cursor.execute("SELECT id FROM materias")
        materias = cursor.fetchall()
        for m in materias:
            cupos_restantes = random.randint(1, 5)
            cursor.execute("UPDATE materias SET cupos_disponibles = ? WHERE id = ?", (cupos_restantes, m['id']))
            
    conn.commit()
    conn.close()

# Ejecutar migración/actualización de la BD al arrancar
init_db_extra()

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        usuario = request.form.get('username', '').strip()
        clave = request.form.get('password', '').strip()
        tipo_usuario = request.form.get('tipo_usuario')
        
        conn = obtener_conexion_db()
        cursor = conn.cursor()
        usuario_db = cursor.execute("""
            SELECT u.*, COALESCE(u.carrera, c.nombre, 'Administración Central') AS carrera_nombre 
            FROM usuarios u 
            LEFT JOIN carreras c ON u.carrera_id = c.id 
            WHERE u.carnet = ? AND u.password = ? AND u.rol = ?
        """, (usuario, clave, tipo_usuario)).fetchone()
        conn.close()
        
        if usuario_db:
            session['usuario_id'] = usuario_db['id']
            session['carnet'] = usuario_db['carnet']
            session['nombre'] = usuario_db['nombre']
            session['rol'] = usuario_db['rol']
            session['indice'] = usuario_db['indice']
            session['carrera'] = usuario_db['carrera_nombre']
            return redirect(url_for('dashboard'))
        else:
            error = "Carnet/Usuario o contraseña incorrectos."
            
    return render_template('login.html', error=error)

@app.route('/dashboard')
def dashboard():
    if 'usuario_id' not in session:
        return redirect(url_for('login'))
        
    return render_template('dashboard.html', 
                           nombre=session.get('nombre'),
                           carnet=session.get('carnet'),
                           indice=session.get('indice'),
                           carrera=session.get('carrera'))

@app.route('/oferta', methods=['GET', 'POST'])
def oferta():
    if 'usuario_id' not in session:
        return redirect(url_for('login'))
        
    conn = obtener_conexion_db()
    cursor = conn.cursor()
    usuario_id = session['usuario_id']
    error = None
    
    # Verificar si el usuario ya realizó la inscripción
    inscripciones_previas = cursor.execute("""
        SELECT m.* FROM inscripciones i
        JOIN materias m ON i.materia_id = m.id
        WHERE i.usuario_id = ?
    """, (usuario_id,)).fetchall()
    
    if request.method == 'POST':
        if len(inscripciones_previas) > 0:
            conn.close()
            return redirect(url_for('estado_inscripcion'))
            
        materias_seleccionadas = request.form.getlist('materias')
        
        # Validar mínimo 3 y máximo 4
        if len(materias_seleccionadas) < 3 or len(materias_seleccionadas) > 4:
            error = "Debes seleccionar un mínimo de 3 y un máximo de 4 materias para procesar la inscripción."
        else:
            # Procesar la inscripción
            for m_id in materias_seleccionadas:
                cursor.execute("INSERT INTO inscripciones (usuario_id, materia_id) VALUES (?, ?)", (usuario_id, m_id))
                # Disminuir el cupo disponible
                cursor.execute("UPDATE materias SET cupos_disponibles = MAX(0, cupos_disponibles - 1) WHERE id = ?", (m_id,))
                
            conn.commit()
            conn.close()
            return redirect(url_for('estado_inscripcion'))

    # Obtener oferta disponible para el año del estudiante
    usuario = cursor.execute("SELECT carrera_id, ano_actual FROM usuarios WHERE id = ?", (usuario_id,)).fetchone()
    materias_oferta = []
    if usuario and usuario['carrera_id'] and usuario['ano_actual']:
        string_ano = f"Año {usuario['ano_actual']}"
        materias_oferta = cursor.execute("""
            SELECT * FROM materias 
            WHERE carrera_id = ? AND ano = ?
        """, (usuario['carrera_id'], string_ano)).fetchall()
        
    conn.close()
    
    return render_template('oferta.html', 
                           nombre=session.get('nombre'),
                           carnet=session.get('carnet'),
                           indice=session.get('indice'),
                           carrera=session.get('carrera'),
                           materias=materias_oferta,
                           inscritas=inscripciones_previas,
                           error=error)

@app.route('/materias-pasadas')
def materias_pasadas():
    if 'usuario_id' not in session:
        return redirect(url_for('login'))
        
    conn = obtener_conexion_db()
    cursor = conn.cursor()
    materias = cursor.execute("""
        SELECT m.codigo, m.nombre, m.creditos, m.ano, h.nota
        FROM historial_materias h
        JOIN materias m ON h.materia_id = m.id
        WHERE h.usuario_id = ? AND h.estado = 'pasada'
        ORDER BY m.ano, m.codigo
    """, (session['usuario_id'],)).fetchall()
    conn.close()
    
    return render_template('materias_pasadas.html',
                           nombre=session.get('nombre'),
                           carnet=session.get('carnet'),
                           indice=session.get('indice'),
                           carrera=session.get('carrera'),
                           materias=materias)

@app.route('/materias-por-pasar')
def materias_por_pasar():
    if 'usuario_id' not in session:
        return redirect(url_for('login'))
        
    conn = obtener_conexion_db()
    cursor = conn.cursor()
    
    usuario = cursor.execute("SELECT carrera_id FROM usuarios WHERE id = ?", (session['usuario_id'],)).fetchone()
    materias = []
    if usuario and usuario['carrera_id']:
        materias = cursor.execute("""
            SELECT m.* FROM materias m
            WHERE m.carrera_id = ?
            AND m.id NOT IN (
                SELECT materia_id FROM historial_materias WHERE usuario_id = ? AND estado = 'pasada'
            )
            ORDER BY m.ano, m.codigo
        """, (usuario['carrera_id'], session['usuario_id'])).fetchall()
        
    conn.close()
    
    return render_template('materias_por_pasar.html',
                           nombre=session.get('nombre'),
                           carnet=session.get('carnet'),
                           indice=session.get('indice'),
                           carrera=session.get('carrera'),
                           materias=materias)

@app.route('/pensum')
def pensum():
    if 'usuario_id' not in session:
        return redirect(url_for('login'))
        
    conn = obtener_conexion_db()
    cursor = conn.cursor()
    
    usuario = cursor.execute("SELECT carrera_id FROM usuarios WHERE id = ?", (session['usuario_id'],)).fetchone()
    materias = []
    if usuario and usuario['carrera_id']:
        materias = cursor.execute("""
            SELECT m.*, h.nota, h.estado
            FROM materias m
            LEFT JOIN historial_materias h ON m.id = h.materia_id AND h.usuario_id = ?
            WHERE m.carrera_id = ?
            ORDER BY m.ano, m.codigo
        """, (session['usuario_id'], usuario['carrera_id'])).fetchall()
        
    conn.close()
    
    return render_template('pensum.html',
                           nombre=session.get('nombre'),
                           carnet=session.get('carnet'),
                           indice=session.get('indice'),
                           carrera=session.get('carrera'),
                           materias=materias)

@app.route('/estado-inscripcion')
def estado_inscripcion():
    if 'usuario_id' not in session:
        return redirect(url_for('login'))
        
    conn = obtener_conexion_db()
    cursor = conn.cursor()
    usuario_id = session['usuario_id']
    
    usuario_info = cursor.execute("SELECT * FROM usuarios WHERE id = ?", (usuario_id,)).fetchone()
    
    stats = cursor.execute("""
        SELECT COUNT(*) as aprobadas, COALESCE(SUM(m.creditos), 0) as creditos_aprobados
        FROM historial_materias h
        JOIN materias m ON h.materia_id = m.id
        WHERE h.usuario_id = ? AND h.estado = 'pasada'
    """, (usuario_id,)).fetchone()
    
    # Obtener materias inscritas por el usuario en esta sesión
    materias_inscritas = cursor.execute("""
        SELECT m.*, i.fecha
        FROM inscripciones i
        JOIN materias m ON i.materia_id = m.id
        WHERE i.usuario_id = ?
    """, (usuario_id,)).fetchall()
    
    conn.close()
    
    return render_template('estado_inscripcion.html',
                           nombre=session.get('nombre'),
                           carnet=session.get('carnet'),
                           indice=session.get('indice'),
                           carrera=session.get('carrera'),
                           usuario=usuario_info,
                           stats=stats,
                           materias_inscritas=materias_inscritas)

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
