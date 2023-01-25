#pragma once
#include <iostream>
#include <vector>
#include "CIndividual.h"
#include "CSmartPointer.h"
using namespace std;

class CGeneticAlgorithm {
public:
	CGeneticAlgorithm(CKnapsackProblem* knapsackProblem, int popSize, float crossProb, float mutProb, int iterationLimit);
	~CGeneticAlgorithm();
	void execute();
	void showSolution();
private:
	void generatePopulation();
	void calculateFitnesses();
	void findSolution();
	void doCrosses();
	void doMutates();
	pair<int, int> findParentsPositions();
	CKnapsackProblem* knapsackProblem;
	int popSize;
	float crossProb;
	float mutProb;
	int iterationLimit;
	vector<CMySmartPointer<CIndividual>> population;
	CMySmartPointer<CIndividual> solution;
};