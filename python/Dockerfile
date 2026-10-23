FROM python:3.12-slim

LABEL org.opencontainers.image.title="Benchmark naive de matrices en Python"
LABEL org.opencontainers.image.description="Multiplicación naive NxN en Python. Mide solo el producto y escribe language,N,repetition,time_seconds."
LABEL org.opencontainers.image.source="https://github.com/ajpirez/computational-experimentation"
LABEL org.opencontainers.image.authors="Alejandro Jesús Pirez Prendes"
LABEL org.opencontainers.image.documentation="https://github.com/ajpirez/computational-experimentation"

WORKDIR /app
COPY main.py .
RUN mkdir -p /results

ENTRYPOINT ["python", "-u", "main.py"]
CMD ["--out", "/results/python.csv"]
