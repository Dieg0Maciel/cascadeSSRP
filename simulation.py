import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import os

from collections import deque
from typing import List


def cumulative(q: np.ndarray) -> np.ndarray:
    output: List[float] = [0.0] * len(q)
    output[0] = q[0]
    for i in range(1, len(q)):
        output[i] = output[i - 1] + q[i]
    return np.array(output)


def recursionFactors(
    n_1: int, lamb: np.ndarray, q: np.ndarray, g: np.ndarray, numberOfStates: int
) -> np.ndarray:
    dp: List[float] = [0.0] * numberOfStates
    dp[0] = n_1 / q[0]
    for i in range(1, numberOfStates):
        dp[i] = dp[i - 1] * (1 / (1 + lamb[i] * q[i] / g[i - 1]))
    return np.array(dp)


def theoretical(
    n_1: int, lamb: np.ndarray, q: np.ndarray, g: np.ndarray, numberOfStates: int
) -> np.ndarray:
    f: np.ndarray = recursionFactors(n_1, lamb, q, g, numberOfStates)
    return np.array([q[i] * f[i] for i in range(numberOfStates)])


def main():
    # Parameters
    numberOfStates = 50
    states: np.ndarray = np.arange(1, numberOfStates + 1)
    numberOfRestarts: int = 10000
    parameters: List[int] = [numberOfStates, numberOfRestarts]
    pd.DataFrame(parameters).to_csv("parameters.csv", header=None, index=None)  # save

    # Array Lambda
    maxLambdaVal: float = 2.0
    beta: float = maxLambdaVal / len(states)
    lamb = np.array([0] + [beta * x for x in states])
    pd.DataFrame(lamb).to_csv("lambda.csv", header=None, index=None)  # save
    plt.plot(states, lamb[1:], "-b")
    plt.grid()
    plt.xlabel("states")
    plt.ylabel("lambda")
    plt.title("Lambda")
    plt.show()

    # Frequencies (Prior Distribution)
    frequencies: np.ndarray = np.array([0] + [1 for i in states])
    norm: int = sum(frequencies)
    q: np.ndarray = np.array([x / norm for x in frequencies[1:]])
    pd.DataFrame(frequencies).to_csv("frequencies.csv", header=None, index=None)  # save

    # Run Simulation
    os.system("g++ cascadeSSRP.cpp -o cascadeSSRP -fopenmp")
    os.system("./cascadeSSRP")
    os.system("rm parameters.csv")
    os.system("rm lambda.csv")
    os.system("rm frequencies.csv")
    os.system("rm cascadeSSRP")

    # Load Simulation
    counts = pd.read_csv("counts.csv", sep=",", header=None)
    counts = np.array(counts[0].tolist())
    os.system("rm counts.csv")

    # Simulated  Probability distribution
    n: np.ndarray = counts

    # Theoretical probability distribution
    g: np.ndarray = cumulative(q)
    n_theo: np.ndarray = theoretical(n[0], lamb, q, g, numberOfStates)

    # Plot Simulation VS Theoretical
    plt.plot(states, n, ".b")
    plt.plot(states, n_theo, "--r")
    plt.grid()
    plt.xlabel("States")
    plt.ylabel("State visits")
    # plt.xscale('log')
    plt.yscale("log")
    plt.legend(["simulation", "theoretical"])
    plt.title("Uniform q and linear lambda")
    plt.show()


if __name__ == "__main__":
    main()
