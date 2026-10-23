FROM golang:1.26

LABEL org.opencontainers.image.title="Benchmark naive de matrices en Go"
LABEL org.opencontainers.image.description="Multiplicación naive NxN en Go. Mide solo el producto y escribe language,N,repetition,time_seconds."
LABEL org.opencontainers.image.source="https://github.com/ajpirez/computational-experimentation"
LABEL org.opencontainers.image.authors="Alejandro Jesús Pirez Prendes"
LABEL org.opencontainers.image.documentation="https://github.com/ajpirez/computational-experimentation"

WORKDIR /src
COPY go.mod main.go ./
RUN go build -o /usr/local/bin/matrix-bench . \
    && mkdir -p /results

WORKDIR /app
ENTRYPOINT ["matrix-bench"]
CMD ["-out", "/results/go.csv"]
