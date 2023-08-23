# NUMERICAL SIMULATION OF SAMPLE SPACE REDUCING PROCESSES
## Overview
Sample Space Reducing Processes (SSRPs) reduce their sample space as they progress over time. They where first studied in [`[1]`](https://www.pnas.org/doi/abs/10.1073/pnas.1420946112), a generalization of the SSRPs called "Cascade SSRPs" was presented in [`[2]`](https://www.nature.com/articles/s41598-017-09836-4).  In [`[3]`](https://www.nature.com/articles/s41598-018-28962-1)  were studied how driving rates determine the statistics of driven non-equilibrium systems with stationary distributions. We can use the following diagram to give a simple representation of SSRPs

![](/images/ssrp.png)

* In (a) a ball bounces downwards a staircase with N = 10 stairs (states). At each timestep the ball randomly choses one of the stairs below its current position. In this
picture the prior probability q_i. Once the ball reaches the lowest step, it is restarted.

* In (b) we see the *cascading picture*,  whenever a ball hits a state i, it multiplies and creates λ(i) − 1 balls, that start their downward moves independently. 

## Algorithm
In order to create an algorithm for the the reduction of the sample space we can use the interpretation given by [`[1]`](https://www.pnas.org/doi/abs/10.1073/pnas.1420946112). Suppose we start with N = 20, we can think about this process as throwing a 20-faced biased dice (icosahedron). The probability distribution of the biased dice is given by an array of ``frequencies`` of 20 components. Suppose in the first throw we get a 13, the reducing of the sample space forces us to take the 12-faced dice (dodecahedron) and reduce of array of ``frequencies`` to a slice from ``frequencies[0]`` to ``frequencies[13 - 1]``. If in the next throw we get 9 we must continue with an 8-faced dice. If we throw a 7, that forces us to take the 6-faced dice. If the following throw gives a 5 we take a 4-faced. If the next throw we get a 3, it forces us to use a 2-faced dice (coin). The process ends when we throw a 1 for the first time.

![](/images/biaseddice.png)

The throwing of a biased dice is given by the function
```
int biasedCoin(double bias, std::mt19937& generator){
    std::bernoulli_distribution flip(bias);
    return flip(generator);
}
```
And the slicing of the array of frequencies can be implemented with the function
```
std::vector<int> slice(std::vector<int>& v, int k){
    std::vector<int> output(v.begin(), v.begin() + k + 1);
    return output;
}
```
The array ``lambda`` of N = 20 components contains the number of processes (balls) which is created in a cascade process. The value ``lambda[i]`` is not necessarily an integer
The file "cascadeSSRP.cpp" contains a numerical simulation of a cascade SSRP which is executed by the script "simulation.py". It compares the numerical simulation with theoretical predictions reproducing the results in Figure 2(b) of [this article](https://www.nature.com/articles/s41598-018-28962-1).


## References
* [`[1]`](https://www.pnas.org/doi/abs/10.1073/pnas.1420946112) Corominas-Murtra, Bernat, Rudolf Hanel, and Stefan Thurner. "Understanding scaling through history-dependent processes with collapsing sample space." Proceedings of the National Academy of Sciences 112.17 (2015): 5348-5353.
  - [Free arxiv preprint version](https://arxiv.org/abs/1407.2775) (PrePrint)

* [`[2]`](https://www.nature.com/articles/s41598-017-09836-4) Corominas-Murtra, Bernat, Rudolf Hanel, and Stefan Thurner. "Sample space reducing cascading processes produce the full spectrum of scaling exponents." Scientific Reports 7.1 (2017): 11223.
  - [Free arxiv preprint version](https://arxiv.org/abs/1703.10100) (PrePrint)

* [`[3]`](https://www.nature.com/articles/s41598-018-28962-1) Corominas-Murtra, Bernat, et al. "How driving rates determine the statistics of driven non-equilibrium systems with stationary distributions." Scientific Reports 8.1 (2018): 10837.
  - [Free arxiv preprint version](https://arxiv.org/abs/1706.10202) (PrePrint)



