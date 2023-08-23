# NUMERICAL SIMULATION OF SAMPLE SPACE REDUCING PROCESSES
## Overview
Sample Space Reducing Processes reduce their sample space as they progress over time. We can
use the following diagram to give a simple representation of them

![](/images/ssrp.png)

* In (a) a ball bounces downwards a staircase with N = 10 stairs (states). At each timestep the ball randomly choses one of the stairs below its current position. In this
picture the prior probability q_i. Once the ball reaches the lowest step, it is restarted.

* In (b) we see the *cascading picture*,  whenever a ball hits a state i, it multiplies and creates λ(i) − 1 new balls, that start their downward moves independently. 

## Algorithm
The file "cascadeSSRP.cpp" contains a numerical simulation of a cascade SSRP which is executed by the script "simulation.py". It compares the numerical simulation with theoretical predictions reproducing the results in Figure 2(b) of [this article](https://www.nature.com/articles/s41598-018-28962-1).


## References
Sample space reducing processes(SSRPs) are processes that reduce their sample space as they progress over time. They where first studied in:
* [`[1]`](https://www.pnas.org/doi/abs/10.1073/pnas.1420946112) Corominas-Murtra, Bernat, Rudolf Hanel, and Stefan Thurner. "Understanding scaling through history-dependent processes with collapsing sample space." Proceedings of the National Academy of Sciences 112.17 (2015): 5348-5353.
* [Corominas-Murtra, Bernat, Rudolf Hanel, and Stefan Thurner. "Understanding scaling through history-dependent processes with collapsing sample space." arXiv preprint arXiv:1407.2775 (2014).](https://arxiv.org/abs/1407.2775) (PrePrint)

A generalization of the SSRPs called "Cascade SSRPs" was presented in:
* [Corominas-Murtra, Bernat, Rudolf Hanel, and Stefan Thurner. "Sample space reducing cascading processes produce the full spectrum of scaling exponents." Scientific Reports 7.1 (2017): 11223.](https://www.nature.com/articles/s41598-017-09836-4)
* [Corominas-Murtra, Bernat, Rudolf Hanel, and Stefan Thurner. "Sample space reducing cascading processes produce the full spectrum of scaling exponents." arXiv preprint arXiv:1703.10100 (2017).](https://arxiv.org/abs/1703.10100) (PrePrint)

The cascade sample space reducing processes are studied in:
* [Corominas-Murtra, Bernat, et al. "How driving rates determine the statistics of driven non-equilibrium systems with stationary distributions." Scientific Reports 8.1 (2018): 10837.](https://www.nature.com/articles/s41598-018-28962-1)
* [Corominas-Murtra, Bernat, et al. "How driving rates determine the statistics of driven non-equilibrium systems with stationary distributions." arXiv preprint arXiv:1706.10202 (2017).](https://arxiv.org/abs/1706.10202) (PrePrint)



