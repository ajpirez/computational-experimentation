FROM gcc:14.2

LABEL org.opencontainers.image.title="Benchmark naive de matrices en C++"
LABEL org.opencontainers.image.description="Multiplicación naive NxN en C++. Mide solo el producto y escribe language,N,repetition,time_seconds."
LABEL org.opencontainers.image.source="https://github.com/ajpirez/computational-experimentation"
LABEL org.opencontainers.image.authors="Alejandro Jesús Pirez Prendes"
LABEL org.opencontainers.image.documentation="https://github.com/ajpirez/computational-experimentation"

WORKDIR /app
COPY main.cpp .
RUN g++ -O2 -o main main.cpp \
    && mkdir -p /results

ENTRYPOINT ["./main"]
CMD ["--out", "/results/cpp.csv"]
