# Benchmark reproducible de multiplicación de matrices NxN

## Objetivo

Comparar el tiempo de ejecución del algoritmo naive de multiplicación de matrices cuadradas NxN en C++, Go, Java y Python, con implementaciones equivalentes y bajo las mismas condiciones de entrada y de medición.

## Pregunta de investigación

¿Existen diferencias estadísticamente significativas en el tiempo de ejecución del algoritmo naive de multiplicación de matrices NxN entre implementaciones equivalentes desarrolladas en C++, Go, Java y Python, y cómo varían estas diferencias según el tamaño de la matriz?

## Hipótesis

- **H₀:** El lenguaje de implementación no produce diferencias estadísticamente significativas en el tiempo de ejecución del algoritmo de multiplicación de matrices.
- **H₁:** Al menos uno de los lenguajes presenta un tiempo de ejecución significativamente diferente de los demás.

El nivel de significación del contraste es α = 0.05.

## Variables



### Independientes


| Variable                | Niveles               |
| ----------------------- | --------------------- |
| Lenguaje                | C++, Go, Java, Python |
| Tamaño de la matriz (N) | 500, 1000, 1500       |




### Dependiente

Tiempo de ejecución de la multiplicación, en segundos. Cada medición queda identificada por el lenguaje, el valor de N y el número de repetición.

### Controladas

- Algoritmo naive, con el mismo orden de bucles en los cuatro lenguajes.
- Tipo de dato real de 64 bits (`double` en C++ y Java, `float64` en Go, `float` en Python).
- Mismas matrices de entrada, generadas con la misma semilla.
- Misma forma de medir el tiempo.
- Sin librerías de multiplicación de matrices.
- Misma máquina para las cuatro implementaciones.



## Diseño experimental

El diseño es factorial completo. Se cruzan los 4 lenguajes con los 3 tamaños y cada combinación se repite 10 veces. En total son 120 mediciones.

La unidad experimental es una multiplicación, para un lenguaje, un N y una repetición. Las matrices A y B ya están creadas cuando empieza esa medición.

### Algoritmo

```text
para i en 0 … N−1:
    para j en 0 … N−1:
        C[i][j] ← 0
        para k en 0 … N−1:
            C[i][j] ← C[i][j] + A[i][k] × B[k][j]
```

El recorrido es i, j, k en los cuatro lenguajes. La multiplicación se hace con ese bucle, sin BLAS, NumPy, Eigen ni otra librería equivalente.

### Matrices de entrada

La semilla es 42. Los valores se obtienen con el generador de Park–Miller:

```text
x ← (16807 · x) mod 2147483647
valor ← x / 2147483647
```

Primero se llena A por filas y después B, siguiendo con el mismo generador. Así las cuatro implementaciones usan las mismas matrices. A y B quedan terminadas antes de medir.

### Medición

El tiempo empieza justo antes de la multiplicación y termina cuando C ya está calculada. Generar o inicializar las matrices no forma parte del tiempo registrado.