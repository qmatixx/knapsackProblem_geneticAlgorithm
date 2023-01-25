#include <iostream>
#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include "CKnapsackProblem.h"
using namespace std;

CGeneticAlgorithm::CGeneticAlgorithm(CKnapsackProblem* knapsackProblem, int popSize, float crossProb, float mutProb, int iterationLimit) {
	if (popSize < 2) {
		throw invalid_argument("PopSize must be bigger than 1");
	}
	if (crossProb < 0 || crossProb > 1) {
		throw invalid_argument("CrossProbability must be bigger than 0 and smaller than 1");
	}
	if (mutProb < 0 || mutProb > 1) {
		throw invalid_argument("MutateProbability must be bigger than 0 and smaller than 1");
	}
	if (iterationLimit < 1) {
		throw invalid_argument("IterationLimit must be bigger than 1");
	}
	this->knapsackProblem = knapsackProblem;
	this->popSize = popSize;
	this->crossProb = crossProb;
	this->mutProb = mutProb;
	this->iterationLimit = iterationLimit;
	solution = CMySmartPointer<CIndividual>(new CIndividual(knapsackProblem));
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{

}

void CGeneticAlgorithm::execute() {
	generatePopulation();
	for (int i = 0; i < iterationLimit; i++) {
		calculateFitnesses();
		findSolution();
		doCrosses();
		doMutates();
	}
}

void CGeneticAlgorithm::showSolution() {
	solution->showIndividual();
}

void CGeneticAlgorithm::generatePopulation() {
	for (int i = 0; i < popSize; i++) {
		population.push_back(CMySmartPointer<CIndividual>(new CIndividual(knapsackProblem)));
	}
}

void CGeneticAlgorithm::calculateFitnesses() {
	for (int i = 0; i < popSize; i++) {
		population[i]->calculateFitness(knapsackProblem);
	}
}

void CGeneticAlgorithm::findSolution() {
	for (int i = 0; i < popSize; i++) {
		if (population[i]->getFitness() > solution->getFitness())
			solution = population[i];
	}
}

void  CGeneticAlgorithm::doCrosses() {
	vector<CMySmartPointer<CIndividual>> newPopulation;
	while (newPopulation.size() < popSize) {
		pair<int, int> parentPositions = findParentsPositions();
		int parentOnePos = parentPositions.first;
		int parentTwoPos = parentPositions.second;
		pair<CIndividual*, CIndividual*> children = population[parentOnePos]->crossover(*population[parentTwoPos], crossProb);
		newPopulation.push_back(children.first);
		if (newPopulation.size() < popSize)
			newPopulation.push_back(children.second);
	}
	population = newPopulation;
}

pair<int, int> CGeneticAlgorithm::findParentsPositions() {
	//FIRST PARENT
	int firstPos = rand() % popSize;
	int secondPos = rand() % popSize;
	while (firstPos == secondPos)
		secondPos = rand() % popSize;
	int parentOnePos;
	if (population[firstPos]->getFitness() > population[secondPos]->getFitness())
		parentOnePos = firstPos;
	else
		parentOnePos = secondPos;
	//SECOND PARENT
	firstPos = rand() % popSize;
	secondPos = rand() % popSize;
	while (firstPos == secondPos)
		secondPos = rand() % popSize;
	int parentTwoPos;
	if (population[firstPos]->getFitness() > population[secondPos]->getFitness())
		parentTwoPos = firstPos;
	else
		parentTwoPos = secondPos;
	//PARENTS HAVE TO BE DIFFERENT
	if (parentOnePos == parentTwoPos && parentTwoPos == firstPos)
		parentTwoPos = secondPos;
	else
		parentTwoPos = firstPos;
	return make_pair(parentOnePos, parentTwoPos);
}

void  CGeneticAlgorithm::doMutates() {
	for (int i = 0; i < popSize; i++) {
		population[i]->mutate(mutProb);
	}
}