# USB DB - Simulación para el exámen: tarea de Bases de Datos

Cuenta la leyenda que en el año 2042 hubo un cambio radical en la enseñanza.
Las universidades se adaptaron a la era de inteligencia artificial avanzada.
Robots y computadoras se han vuelto mucho más inteligented que nosotros.
Las máquinas deciden que deben preservar el (inferior) intelecto humano.
Por esa razón preservan la enseñanza. La USB es parte de la iniciativa.

En este nuevo mundo:

- Los estudiantes nunca raspan materias
- El implante neuronal hace que mejoren si tienen problemas
- Pero tambien alienta a los estudianteas a esforzarse
- Esto los obliga a pensar y desarrollar su intelecto
- Las notas van de 3 a 5

La estructura y funcionamiento de la USB corresponde al año 2019.
El repositorio contiene el catálogo de la USB, para que lo vean.
No pierdan tiempo estudiandolo: lo necesario esta en el código.

## Cómo usar el programa

Simplemente ejecútenlo sin argumentos. Verán este menu interactivo.

0 - reset
1 - divisiones
2 - departamentos
3 - asignaturas
4 - decanatos
5 - coordinaciones
6 - carreras
7 - estudiantes
8 - calificaciones
> - avanza
x - extend
t - todos
q0 - query 0
q1 - query 1
q2 - query 2
q3 - query 3
. - salir
<USB DB> 

La última línea "<USB DB> " es el prompt para que seleccionen un comando.
Simplemente dénle a la tecla del número 1 y luego al Enter

    <USB DB> 1

Verán la lista de las Divisiones de la universidad:las mismas del catálogo!
Repitan lo anterior para los números (entidades) del 2 al 6.
Noten los valores y campos de las tablas. Por ejemplo:

    { codigo: MA1111, departamento: MA, descripcion: Matemáticas I, uc: 4 }

Es uno de los "records" en la Tabla de Asignaturas, y se interpreta asi:
"MA1111" es una asignatura (Materia) del departamento "MA" (Matemáticas)
El título (descripcion) del curso es "Matemáticas I" y ..
.. vale 4 unidades de credito.

Al intentar con 7 y 8 (estudiantes y calificaciones) verán que no tienen nada.
La universidad acaba de "re-inventarse" y aun no ha comenzado.

El comando '>' (mayor que) hace que la universidad avance un año.
Nuevos estudiantes se registran. Los que ya están, avanzan al año siguiente.
Vuelvan a intentar el 7 y el 8 - verán que ahora tienen estudiantes y notas.

El comando 'x' permite eXtender las simulación por varios años hacia el futuro.
Tiene una sintaxis especial, de la forma x:<N>, donde <N> es un valor entero.
Por ejemplo:

    x:8

Avanza 8 años: 'x:8' es equivalente a usar '>' 8 veces.
No usen valores de N mayores que 20: ¡la base de datos crece rapidamente!
Su computadora (y su tiempo) lo van a apreciar.

Los comandos 'q0' a 'q3' van a ejecutar los queries que Uds. deben implementar.

Por último, olvidense del comando '0' (reset) y 't' (todos) .. no importan aqui.

## Reglas para la tarea

- No deben cambiar el codigo provisto en la tarea, excepto por Query.cxx
- Query.cxx es el archivo donde van a implementar los "queries" del examen.
- Ademas, sólo pueden llamar a funciones declaradas en los encabezados (*.h) ..
- .. excepto en los pocos casos donde el encabezado lo prohibe. Por ejemplo:

    // OJO: NO deben usar las funciones declaradas de aqui al final del archivo

- En caso de conseguir "bugs" en la tarea, reportenlos.
- Lean todo concuidado y no vacilen preguntar.
