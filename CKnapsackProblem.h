#pragma once
#include <iostream>
using namespace std;

class CKnapsackProblem {
public:
	CKnapsackProblem(string& fileName);
	~CKnapsackProblem();
	double calculateFitness(bool* pi_genotype);
	int getSize();
	double getMaxWeight();
	void printWeights();
	void printValues();
private:
	void loadFromFile(string& fileName);
	double* pd_weights;
	double* pd_values;
	int size;
	double maxWeight;
};