#pragma once
#include <iostream>
#include "CKnapsackProblem.h"
using namespace std;

class CIndividual {
public:
	CIndividual(CKnapsackProblem* knapsackProblem);
	CIndividual(bool* pb_genotype, int size);
	CIndividual(const CIndividual& pcOther);
	~CIndividual();
	void calculateFitness(CKnapsackProblem* knapsackProblem);
	void mutate(float mutProb);
	pair<CIndividual*, CIndividual*> crossover(const CIndividual& partner, float crossProb);
	double getFitness();
	void showIndividual();
private:
	void generateGenotype(CKnapsackProblem* knapsackProblem);
	double fitness;
	int size;
	bool* pb_genotype;
};