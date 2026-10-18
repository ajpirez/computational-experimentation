import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class Main {
    static final long MOD = 2147483647L;
    static final long MULT = 16807L;
    static final long SEED = 42L;

    static long nextState(long x) {
        return (MULT * x) % MOD;
    }

    static class Matrices {
        double[] A;
        double[] B;
        long state;

        Matrices(double[] A, double[] B, long state) {
            this.A = A;
            this.B = B;
            this.state = state;
        }
    }

    static Matrices generate(int n, long seed) {
        double[] A = new double[n * n];
        double[] B = new double[n * n];
        long x = seed;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                x = nextState(x);
                A[i * n + j] = (double) x / (double) MOD;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                x = nextState(x);
                B[i * n + j] = (double) x / (double) MOD;
            }
        }
        return new Matrices(A, B, x);
    }

    static void multiply(double[] A, double[] B, double[] C, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double sum = 0.0;
                for (int k = 0; k < n; k++) {
                    sum += A[i * n + k] * B[k * n + j];
                }
                C[i * n + j] = sum;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        String outPath = "results/java.csv";
        List<Integer> sizes = new ArrayList<>();
        sizes.add(500);
        sizes.add(1000);
        sizes.add(1500);
        int reps = 10;
        boolean printA00 = false;

        for (int i = 0; i < args.length; i++) {
            if (args[i].equals("--out") && i + 1 < args.length) {
                outPath = args[++i];
            } else if (args[i].equals("--n") && i + 1 < args.length) {
                sizes.clear();
                sizes.add(Integer.parseInt(args[++i]));
            } else if (args[i].equals("--reps") && i + 1 < args.length) {
                reps = Integer.parseInt(args[++i]);
            } else if (args[i].equals("--print-a00")) {
                printA00 = true;
            }
        }

        if (printA00) {
            Matrices m = generate(2, SEED);
            System.out.printf(Locale.US, "%.17g %.17g %.17g %.17g%n", m.A[0], m.A[1], m.A[2], m.A[3]);
            return;
        }

        try (PrintWriter out = new PrintWriter(new FileWriter(outPath))) {
            out.println("language,N,repetition,time_seconds");
            for (int n : sizes) {
                Matrices mats = generate(n, SEED);
                double[] C = new double[n * n];
                for (int r = 1; r <= reps; r++) {
                    long t0 = System.nanoTime();
                    multiply(mats.A, mats.B, C, n);
                    long t1 = System.nanoTime();
                    double seconds = (t1 - t0) / 1_000_000_000.0;
                    out.printf(Locale.US, "java,%d,%d,%.10f%n", n, r, seconds);
                    System.out.printf(Locale.US, "java N=%d rep=%d %.10f s%n", n, r, seconds);
                }
            }
        }
    }
}
