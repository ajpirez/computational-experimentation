# Entorno de ejecución

Características de la máquina donde se ejecutó el experimento de la semana 2.

| Característica | Valor |
| --- | --- |
| Procesador | 11th Gen Intel Core i7-11800H @ 2.30 GHz |
| Memoria RAM | 15.7 GB |
| Sistema operativo | Microsoft Windows 10 Pro |
| Arquitectura | AMD64 |

## Compiladores y runtimes

| Lenguaje | Herramienta | Versión |
| --- | --- | --- |
| C++ | g++ (MSYS2) | 14.1.0, compilado con `-O2` |
| Go | go | 1.26.5 windows/amd64 |
| Java | javac / java (Oracle/OpenJDK) | 17.0.12 |
| Python | CPython | 3.12.10 |

Las cuatro implementaciones se ejecutaron en esta misma máquina, una tras otra, sin contenedores.

## Imágenes Docker

Cada lenguaje tiene su propio `Dockerfile`. La imagen se construye a mano e incluye solo lo necesario para compilar o ejecutar esa implementación.

| Imagen local | Publicada en Docker Hub | Base | Qué contiene |
| --- | --- | --- | --- |
| `matrix-bench-cpp:1.0` | `94031728605/matrix-bench-cpp:1.0` | `gcc:14.2` | `g++ -O2` y `cpp/main.cpp` |
| `matrix-bench-go:1.0` | `94031728605/matrix-bench-go:1.0` | `golang:1.26` | binario compilado de `go/main.go` |
| `matrix-bench-java:1.0` | `94031728605/matrix-bench-java:1.0` | `eclipse-temurin:17-jdk` | `java/Main.java` compilado con Java 17 |
| `matrix-bench-python:1.0` | `94031728605/matrix-bench-python:1.0` | `python:3.12-slim` | `python/main.py` sobre CPython 3.12 |
