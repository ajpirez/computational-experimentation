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

## Implementación

Las cuatro implementaciones están en `cpp/`, `go/`, `java/` y `python/`. Usan el mismo algoritmo, el mismo tipo de 64 bits, la misma semilla y el mismo criterio de reloj. No usan librerías de multiplicación de matrices.

Los resultados de cada lenguaje quedan en:

- `results/cpp.csv`
- `results/go.csv`
- `results/java.csv`
- `results/python.csv`

Cada archivo tiene las columnas `language`, `N`, `repetition` y `time_seconds`.

Las características de la máquina y las versiones de los compiladores están en `ENVIRONMENT.md`.

## Cómo ejecutar con Docker

Hace falta Docker. Cada imagen se construye a mano con su `Dockerfile`. Dentro van el compilador o el intérprete y el programa de ese lenguaje. La corrida escribe un CSV en la carpeta `results/` del equipo.

### Construcción

Desde la raíz del repositorio:

```text
docker build -t matrix-bench-cpp:1.0 cpp
docker build -t matrix-bench-go:1.0 go
docker build -t matrix-bench-java:1.0 java
docker build -t matrix-bench-python:1.0 python
```

### Corrida completa

N = 500, 1000 y 1500, con 10 repeticiones. En PowerShell:

```text
New-Item -ItemType Directory -Force -Path results

docker run --rm -v "${PWD}/results:/results" matrix-bench-cpp:1.0 --out /results/cpp.csv
docker run --rm -v "${PWD}/results:/results" matrix-bench-go:1.0 -out /results/go.csv
docker run --rm -v "${PWD}/results:/results" matrix-bench-java:1.0 --out /results/java.csv
docker run --rm -v "${PWD}/results:/results" matrix-bench-python:1.0 --out /results/python.csv
```

Go usa `-out`. Los otros tres usan `--out`. El archivo que sale tiene las columnas `language`, `N`, `repetition` y `time_seconds`.

La corrida de Python con N = 1500 puede tardar varias horas.

### Prueba corta

Sirve para comprobar que el contenedor genera el CSV, con una sola matriz pequeña:

```text
docker run --rm -v "${PWD}/results:/results" matrix-bench-cpp:1.0 --n 50 --reps 1 --out /results/cpp.csv
docker run --rm -v "${PWD}/results:/results" matrix-bench-go:1.0 -n 50 -reps 1 -out /results/go.csv
docker run --rm -v "${PWD}/results:/results" matrix-bench-java:1.0 --n 50 --reps 1 --out /results/java.csv
docker run --rm -v "${PWD}/results:/results" matrix-bench-python:1.0 --n 50 --reps 1 --out /results/python.csv
```

### Publicar en Docker Hub

Las cuatro imágenes están en la cuenta `94031728605`, etiqueta `1.0`:

- https://hub.docker.com/r/94031728605/matrix-bench-cpp
- https://hub.docker.com/r/94031728605/matrix-bench-go
- https://hub.docker.com/r/94031728605/matrix-bench-java
- https://hub.docker.com/r/94031728605/matrix-bench-python

Para volver a publicarlas, sustituye `usuario` por el nombre de la cuenta:

```text
docker login -u usuario

docker tag matrix-bench-cpp:1.0 usuario/matrix-bench-cpp:1.0
docker tag matrix-bench-go:1.0 usuario/matrix-bench-go:1.0
docker tag matrix-bench-java:1.0 usuario/matrix-bench-java:1.0
docker tag matrix-bench-python:1.0 usuario/matrix-bench-python:1.0

docker push usuario/matrix-bench-cpp:1.0
docker push usuario/matrix-bench-go:1.0
docker push usuario/matrix-bench-java:1.0
docker push usuario/matrix-bench-python:1.0
```

En la página de cada repositorio, el campo de descripción corta puede quedar así:

| Repositorio | Descripción |
| --- | --- |
| `matrix-bench-cpp` | Multiplicación naive de matrices NxN en C++. Mide solo el producto. |
| `matrix-bench-go` | Multiplicación naive de matrices NxN en Go. Mide solo el producto. |
| `matrix-bench-java` | Multiplicación naive de matrices NxN en Java. Mide solo el producto. |
| `matrix-bench-python` | Multiplicación naive de matrices NxN en Python. Mide solo el producto. |

La descripción larga de cada imagen ya viaja en las etiquetas de la imagen (`org.opencontainers.image.title` y `org.opencontainers.image.description`). Se leen con `docker inspect matrix-bench-cpp:1.0`.

## Cómo ejecutar en la máquina local

Desde la raíz del repositorio:

```text
g++ -O2 -o cpp/main.exe cpp/main.cpp
cpp/main.exe --out results/cpp.csv

cd go
go build -o main.exe .
cd ..
go/main.exe -out results/go.csv

javac -d java java/Main.java
java -cp java Main --out results/java.csv

python python/main.py --out results/python.csv
```

Cada corrida completa usa N = 500, 1000 y 1500, con 10 repeticiones por tamaño. Para una prueba corta:

```text
python python/main.py --n 50 --reps 1 --out results/python.csv
```