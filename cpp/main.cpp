#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

static constexpr long long MOD = 2147483647LL;
static constexpr long long MULT = 16807LL;
static constexpr long long SEED = 42LL;

struct Matrices {
    std::vector<double> A;
    std::vector<double> B;
    long long state;
};

static long long next_state(long long x) {
    return (MULT * x) % MOD;
}

static Matrices generate(int n, long long seed) {
    Matrices m;
    m.A.resize(static_cast<size_t>(n) * n);
    m.B.resize(static_cast<size_t>(n) * n);
    long long x = seed;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            x = next_state(x);
            m.A[static_cast<size_t>(i) * n + j] = static_cast<double>(x) / static_cast<double>(MOD);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            x = next_state(x);
            m.B[static_cast<size_t>(i) * n + j] = static_cast<double>(x) / static_cast<double>(MOD);
        }
    }
    m.state = x;
    return m;
}

static void multiply(const std::vector<double>& A, const std::vector<double>& B,
                     std::vector<double>& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < n; ++k) {
                sum += A[static_cast<size_t>(i) * n + k] * B[static_cast<size_t>(k) * n + j];
            }
            C[static_cast<size_t>(i) * n + j] = sum;
        }
    }
}

int main(int argc, char* argv[]) {
    std::string out_path = "results/cpp.csv";
    std::vector<int> sizes = {500, 1000, 1500};
    int reps = 10;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--out" && i + 1 < argc) {
            out_path = argv[++i];
        } else if (arg == "--n" && i + 1 < argc) {
            sizes.clear();
            sizes.push_back(std::atoi(argv[++i]));
        } else if (arg == "--reps" && i + 1 < argc) {
            reps = std::atoi(argv[++i]);
        } else if (arg == "--print-a00") {
            Matrices m = generate(2, SEED);
            std::cout << std::setprecision(17) << m.A[0] << " " << m.A[1] << " "
                      << m.A[2] << " " << m.A[3] << "\n";
            return 0;
        }
    }

    std::ofstream out(out_path);
    if (!out) {
        std::cerr << "No se pudo abrir " << out_path << "\n";
        return 1;
    }
    out << "language,N,repetition,time_seconds\n";
    out << std::setprecision(10);

    for (int n : sizes) {
        Matrices mats = generate(n, SEED);
        std::vector<double> C(static_cast<size_t>(n) * n);
        for (int r = 1; r <= reps; ++r) {
            auto t0 = std::chrono::steady_clock::now();
            multiply(mats.A, mats.B, C, n);
            auto t1 = std::chrono::steady_clock::now();
            double seconds = std::chrono::duration<double>(t1 - t0).count();
            out << "cpp," << n << "," << r << "," << seconds << "\n";
            std::cout << "cpp N=" << n << " rep=" << r << " " << seconds << " s\n";
        }
    }
    return 0;
}
