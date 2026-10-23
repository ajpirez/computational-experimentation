FROM eclipse-temurin:17-jdk

LABEL org.opencontainers.image.title="Benchmark naive de matrices en Java"
LABEL org.opencontainers.image.description="Multiplicación naive NxN en Java. Mide solo el producto y escribe language,N,repetition,time_seconds."
LABEL org.opencontainers.image.source="https://github.com/ajpirez/computational-experimentation"
LABEL org.opencontainers.image.authors="Alejandro Jesús Pirez Prendes"
LABEL org.opencontainers.image.documentation="https://github.com/ajpirez/computational-experimentation"

WORKDIR /app
COPY Main.java .
RUN javac Main.java \
    && mkdir -p /results

ENTRYPOINT ["java", "Main"]
CMD ["--out", "/results/java.csv"]
