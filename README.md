# Laboratorio: suma máxima de un subarreglo

## 1. Implementación

Hice tres versiones para encontrar la suma máxima de un subarreglo contiguo: la cúbica, la cuadrática y la lineal, que usa el algoritmo de Kadane.

En la cúbica usé tres bucles: dos para escoger dónde empieza y termina el subarreglo, y otro para sumar sus elementos. En la cuadrática usé dos bucles, porque fui guardando la suma mientras avanzaba. En Kadane recorrí el arreglo una sola vez y en cada posición elegí entre seguir con la suma que llevaba o empezar de nuevo desde ese elemento.

Después probé las tres versiones con 100 arreglos pequeños al azar, de entre 2 y 20 elementos. Los números estuvieron entre −100 y 100. Para que cada arreglo tuviera positivos y negativos, puse un positivo al inicio y un negativo en la segunda posición. En cada prueba pasé el mismo arreglo a las tres funciones y mostré las sumas que devolvieron.

## 2. Medición

Para las pruebas usé un equipo con un Intel Core i5-12450H y 15 GiB de RAM. Compilé con GCC 16.2.1, C++17 y optimización de nivel 2.

Empecé con 1000 elementos y fui duplicando la cantidad: 2000, 4000, 8000 y así sucesivamente. Usé números al azar entre −100 y 100 y reinicié la semilla en 12345 para cada arreglo. De esta forma, las tres versiones recibieron los mismos datos cuando trabajaron con el mismo tamaño.

Medí una vez cada versión para cada tamaño. Solo conté el tiempo que tardó la función, sin incluir la creación del arreglo ni la impresión de los resultados. También guardé y mostré la suma de cada llamada.

Los tiempos están en milisegundos. Para sacar la razón, dividí cada tiempo entre el anterior. En la primera fila dejé un guion porque todavía no había otro tiempo con el cual dividir.

### Versión cúbica

| n | Tiempo (ms) | Razón respecto al anterior |
| ---: | ---: | ---: |
| 1 000 | 61.306200 | — |
| 2 000 | 346.066033 | 5.645 |
| 4 000 | 2 725.345870 | 7.875 |
| 8 000 | 21 857.473809 | 8.020 |

### Versión cuadrática

| n | Tiempo (ms) | Razón respecto al anterior |
| ---: | ---: | ---: |
| 1 000 | 0.301636 | — |
| 2 000 | 1.088482 | 3.609 |
| 4 000 | 4.358524 | 4.004 |
| 8 000 | 17.465304 | 4.007 |
| 16 000 | 70.142112 | 4.016 |
| 32 000 | 275.705374 | 3.931 |
| 64 000 | 1 179.923156 | 4.280 |
| 128 000 | 4 393.492755 | 3.724 |

### Versión lineal: Kadane

| n | Tiempo (ms) | Razón respecto al anterior |
| ---: | ---: | ---: |
| 1 000 | 0.001023 | — |
| 2 000 | 0.001967 | 1.923 |
| 4 000 | 0.003992 | 2.029 |
| 8 000 | 0.007819 | 1.959 |
| 16 000 | 0.015772 | 2.017 |
| 32 000 | 0.031477 | 1.996 |
| 64 000 | 0.068556 | 2.178 |
| 128 000 | 0.125084 | 1.825 |
| 256 000 | 0.275872 | 2.205 |
| 512 000 | 0.584947 | 2.120 |
| 1 024 000 | 1.058766 | 1.810 |
| 2 048 000 | 2.170175 | 2.050 |
| 4 096 000 | 4.306032 | 1.984 |
| 8 192 000 | 8.588629 | 1.995 |
| 16 384 000 | 17.573196 | 2.046 |
| 32 768 000 | 34.421874 | 1.959 |

### Lo que se ve en las razones

En la cúbica, las dos últimas razones salieron cerca de 7,88 y 8,02. O sea, al duplicar el arreglo, el tiempo aumentó unas ocho veces. Por eso el crecimiento que deduje fue **Θ(n³)**.

En la cuadrática, las razones estuvieron cerca de cuatro. Al poner el doble de elementos, el tiempo fue aproximadamente cuatro veces mayor. Esto corresponde a un crecimiento **Θ(n²)**.

En Kadane, las razones estuvieron cerca de dos. Al duplicar la cantidad de elementos, el tiempo también se duplicó aproximadamente. Por eso su crecimiento es **Θ(n)**.

Las razones no salieron exactas, ya que los tiempos pueden cambiar según la carga del equipo, la velocidad del procesador y la caché. Además, como hice una sola medición por tamaño, cualquier pequeña variación se nota más cuando el tiempo es muy corto.

Con la cúbica llegué hasta 8000 elementos, donde ya tardaba casi 22 segundos. El siguiente tamaño habría tardado unos 175 segundos, así que paré ahí. Con la cuadrática llegué hasta 128 000 elementos, que tomó unos 4,39 segundos; duplicarlo otra vez habría tomado unos 17,57 segundos. Estos fueron los límites que elegí para la prueba. Con Kadane llegué hasta 32 768 000 elementos antes de pasar a la prueba de 10⁸.

## 3. Predicción

Para calcular cuánto tardaría cada versión con 100 millones de elementos, usé el último tiempo de cada tabla y el crecimiento que encontré:

**Tiempo estimado = tiempo medido × (tamaño objetivo / tamaño medido)ᵖ**

Puse p = 3 para la cúbica, p = 2 para la cuadrática y p = 1 para Kadane. Reemplazando los datos, quedó así:

- **Cúbica:** 21 857.473809 × (100 000 000 / 8 000)³ ms.
- **Cuadrática:** 4 393.492755 × (100 000 000 / 128 000)² ms.
- **Kadane:** 34.421874 × (100 000 000 / 32 768 000) ms.

| Versión | Tiempo predicho para n = 10⁸ | ¿Menos de un minuto? |
| --- | ---: | :---: |
| Cúbica | 4.269e+13 s ≈ 1.35 millones de años | No |
| Cuadrática | 2681575.168 s ≈ 31.04 días | No |
| Kadane | 105.047223 ms ≈ 0.105 s | Sí |

Estos tiempos son aproximados y dependen de que el crecimiento siga igual. Sobre todo en la cúbica, estoy pasando de un arreglo pequeño a uno muchísimo más grande, así que la cifra sirve para darse una idea de lo que tardaría. Para pasar de segundos a años usé años de 365 días.

### Lo que predije y lo que tardó

Solo ejecuté Kadane con 100 millones de elementos, porque fue la única versión que, según la predicción, terminaría en menos de un minuto. Primero generé el arreglo y luego medí una llamada a la función, igual que antes. La suma máxima que salió fue 645 213.

| Tiempo predicho | Tiempo medido | Diferencia absoluta | Error respecto a la predicción |
| ---: | ---: | ---: | ---: |
| 105.047223 ms | 109.723937 ms | 4.676714 ms | 4.45 % |

Kadane tardó un 4,45 % más de lo que había calculado. La diferencia fue pequeña y el resultado quedó cerca de la predicción.

Con estas pruebas vi que Kadane pudo trabajar con 100 millones de elementos en unos 0,11 segundos en mi equipo. Para la cuadrática calculé unos 31 días y para la cúbica alrededor de 1,35 millones de años, así que no las ejecuté con ese tamaño.
