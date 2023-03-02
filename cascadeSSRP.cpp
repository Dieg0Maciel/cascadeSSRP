#include<iostream>
#include<fstream>
#include<vector>
#include<random>
#include<deque>
#include<omp.h>
#define n_threads 4

int biasedCoin(double bias, std::mt19937& generator){
    std::bernoulli_distribution flip(bias);
    return flip(generator);
}

int biasedDice(std::vector<int>& frequencies, std::mt19937& generator){
    std::discrete_distribution<> dist(frequencies.begin(), frequencies.end());
    return dist(generator);
}

std::vector<int> slice(std::vector<int>& v, int k){
    std::vector<int> output(v.begin(), v.begin() + k + 1);
    return output;
}

std::vector<int> ssrp(
    int numberOfStates, 
    std::vector<int>& frequencies,
    std::vector<double>& lambda,
    std::mt19937& generator	
){
    std::vector<int> counts(numberOfStates, 0);
    std::deque<int> stack;
    stack.push_front(numberOfStates + 1);
    while(stack.size() > 0){
	int k = stack.front();
	stack.pop_front();
	std::vector<int> sliced = slice(frequencies,k-1);
	k = biasedDice(sliced, generator);
	counts[k - 1] += 1;
	if(k != 1){
	    double delta = lambda[k - 1] - std::floor(lambda[k - 1]);
	    int mu = (biasedCoin(delta, generator) == 1) ? std::floor(lambda[k - 1]) + 1 : std::floor(lambda[k - 1]);
	    for(int i = 0; i < mu; i++){
		stack.push_front(k);
	    }
	}
    }
    return counts;
}

std::vector<int> simulation(
    int numberOfStates, 
    int numberOfRestarts,
    std::vector<int>& frequencies,
    std::vector<double>& lambda
){
    std::random_device device;   
    std::mt19937 generator(device());
    std::vector<int> counts(numberOfStates, 0);
    #pragma omp parallel for num_threads(n_threads)
    for(int i = 0; i < numberOfRestarts; i++){
	std::vector<int> new_counts = ssrp(numberOfStates, frequencies, lambda, generator);
	for(int j = 0; j < numberOfStates; j++){
	    counts[j] += new_counts[j];
	}
    }
    return counts;
}

void saveArrayToCSV(
    std::string name, 
    std::vector<int>& vect
) {
    name.append(".csv");
    std::ofstream ofs(name, std::ofstream::out);
    for(auto x = vect.begin(); x != vect.end(); x++){
	ofs << *x << "\n";
    }
}

std::vector<int> readIntCSV(std::string file_name){
    std::vector<int> v;
    std::ifstream file; 
    file.open(file_name);  
    while (file.good()) { 
	std::string xString; 
	std::getline(file, xString, '\n'); 
	int x;
	x = std::atoi(xString.c_str());
	v.push_back(x);
    }
    v.pop_back();
    return v;
}


std::vector<double> readDoubleCSV(std::string file_name){
    std::vector<double> v;
    std::ifstream file; 
    file.open(file_name);  
    while (file.good()) { 
	std::string xString; 
	std::getline(file, xString, '\n'); 
	double x;
	x = std::atof(xString.c_str());
	v.push_back(x);
    }
    v.pop_back();
    return v;
}


int main() {
    std::string fileName1 = "parameters.csv";
    std::string fileName2 = "frequencies.csv";
    std::string fileName3 = "lambda.csv";
    
    std::vector<int> parameters = readIntCSV(fileName1);	
    int numberOfStates = parameters[0];
    int numberOfRestarts = parameters[1];
    std::vector<int> frequencies = readIntCSV(fileName2);
    std::vector<double> lambda = readDoubleCSV(fileName3);


    std::vector<int> counts;
    counts = simulation(numberOfStates, numberOfRestarts, frequencies, lambda);
    saveArrayToCSV("counts", counts);

    std::cout << "Done!\n";
    return 0;
}
