package main

import (
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

const (
	mod  int64 = 2147483647
	mult int64 = 16807
	seed int64 = 42
)

func nextState(x int64) int64 {
	return (mult * x) % mod
}

func generate(n int, start int64) (A, B []float64, state int64) {
	A = make([]float64, n*n)
	B = make([]float64, n*n)
	x := start
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			x = nextState(x)
			A[i*n+j] = float64(x) / float64(mod)
		}
	}
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			x = nextState(x)
			B[i*n+j] = float64(x) / float64(mod)
		}
	}
	return A, B, x
}

func multiply(A, B, C []float64, n int) {
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			sum := 0.0
			for k := 0; k < n; k++ {
				sum += A[i*n+k] * B[k*n+j]
			}
			C[i*n+j] = sum
		}
	}
}

func main() {
	outPath := flag.String("out", "results/go.csv", "CSV output path")
	nFlag := flag.String("n", "", "single N (default: 500,1000,1500)")
	reps := flag.Int("reps", 10, "repetitions per N")
	printA00 := flag.Bool("print-a00", false, "print first four A cells and exit")
	flag.Parse()

	if *printA00 {
		A, _, _ := generate(2, seed)
		fmt.Printf("%.17g %.17g %.17g %.17g\n", A[0], A[1], A[2], A[3])
		return
	}

	sizes := []int{500, 1000, 1500}
	if *nFlag != "" {
		parts := strings.Split(*nFlag, ",")
		sizes = sizes[:0]
		for _, p := range parts {
			v, err := strconv.Atoi(strings.TrimSpace(p))
			if err != nil {
				fmt.Fprintf(os.Stderr, "N inválido: %v\n", err)
				os.Exit(1)
			}
			sizes = append(sizes, v)
		}
	}

	f, err := os.Create(*outPath)
	if err != nil {
		fmt.Fprintf(os.Stderr, "No se pudo abrir %s: %v\n", *outPath, err)
		os.Exit(1)
	}
	defer f.Close()
	fmt.Fprintln(f, "language,N,repetition,time_seconds")

	for _, n := range sizes {
		A, B, _ := generate(n, seed)
		C := make([]float64, n*n)
		for r := 1; r <= *reps; r++ {
			t0 := time.Now()
			multiply(A, B, C, n)
			seconds := time.Since(t0).Seconds()
			fmt.Fprintf(f, "go,%d,%d,%.10f\n", n, r, seconds)
			fmt.Printf("go N=%d rep=%d %.10f s\n", n, r, seconds)
		}
	}
}
