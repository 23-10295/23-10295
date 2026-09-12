# Cómo procesamos los datos de los sensores

Cada sensor manda varias lecturas por lote, sus microsensores, y de ahí
tenemos que sacar un solo número, el macondo. El problema es que algún
microsensor puede fallar y tirar una lectura rara, así que no alcanza con
promediar todo tal cual.

Lo resolvimos en tres pasos:

1. Sacamos la mediana de las lecturas del sensor. La usamos en vez del
   promedio porque un valor raro casi no la mueve. Si un microsensor se
   vuelve loco y tira un número absurdo, la mediana ni lo nota.
2. Con esa mediana como referencia, descartamos las lecturas que se
   alejan demasiado de ella, más de un porcentaje que llamamos radio de
   tolerancia. Lo dejamos en 7.5%, adentro del 5 al 10% que sugiere la
   entrevista. Esas lecturas que se alejan las tratamos como fallas.
3. El macondo final es el promedio de lo que quedó después de filtrar.
   Si el radio resulta tan estricto que descarta todo, usamos todas las
   lecturas originales para no quedarnos sin nada.

O sea: mediana, filtrar por distancia a esa mediana, promediar lo que
sobrevivió.

## Y el costo de procesar

Para un sensor con N microsensores lo único que pesa un poco es ordenar
para sacar la mediana, que es O(N log N). El resto es lineal, O(N). Como N
es chico, 6 u 8 según el modelo de sensor, esto es prácticamente
instantáneo comparado con los 2 segundos que separan un lote del
siguiente. Sobra margen de tiempo aunque después suban la frecuencia de
muestreo.

## Por qué está separado en su propio archivo

El algoritmo vive en Sintesis.ts, separado del resto, detrás de un tipo
bien simple: entra el arreglo de lecturas y el radio, sale el macondo. Así
si la agencia trae su propio modelo lo podemos probar o cambiar sin tocar
nada más del sistema.
