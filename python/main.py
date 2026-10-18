#!/usr/bin/env python3
"""Naive matrix multiplication benchmark (Park–Miller seed 42)."""

from __future__ import annotations

import argparse
import time
from pathlib import Path

MOD = 2147483647
MULT = 16807
SEED = 42


def next_state(x: int) -> int:
    return (MULT * x) % MOD


def generate(n: int, seed: int = SEED) -> tuple[list[list[float]], list[list[float]], int]:
    x = seed
    a: list[list[float]] = []
    for _i in range(n):
        row: list[float] = []
        for _j in range(n):
            x = next_state(x)
            row.append(x / MOD)
        a.append(row)
    b: list[list[float]] = []
    for _i in range(n):
        row = []
        for _j in range(n):
            x = next_state(x)
            row.append(x / MOD)
        b.append(row)
    return a, b, x


def multiply(a: list[list[float]], b: list[list[float]], n: int) -> list[list[float]]:
    c = [[0.0] * n for _ in range(n)]
    for i in range(n):
        ai = a[i]
        ci = c[i]
        for j in range(n):
            s = 0.0
            for k in range(n):
                s += ai[k] * b[k][j]
            ci[j] = s
    return c


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out", default="results/python.csv")
    parser.add_argument("--n", type=int, default=None, help="single N; default 500,1000,1500")
    parser.add_argument("--reps", type=int, default=10)
    parser.add_argument("--print-a00", action="store_true")
    args = parser.parse_args()

    if args.print_a00:
        a, _b, _ = generate(2, SEED)
        print(f"{a[0][0]:.17g} {a[0][1]:.17g} {a[1][0]:.17g} {a[1][1]:.17g}")
        return

    sizes = [args.n] if args.n is not None else [500, 1000, 1500]
    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)

    with out_path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("language,N,repetition,time_seconds\n")
        for n in sizes:
            a, b, _ = generate(n, SEED)
            for r in range(1, args.reps + 1):
                t0 = time.perf_counter()
                multiply(a, b, n)
                seconds = time.perf_counter() - t0
                f.write(f"python,{n},{r},{seconds:.10f}\n")
                f.flush()
                print(f"python N={n} rep={r} {seconds:.10f} s", flush=True)


if __name__ == "__main__":
    main()
