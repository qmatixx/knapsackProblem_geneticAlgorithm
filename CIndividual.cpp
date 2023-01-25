#include <iostream>
#include <vector>
#include "CGeneticAlgorithm.h"
using namespace std;


//FITNESS=-1 MEANS NOT CALCULATED, FITNESS=0 MEANS WEIGHT IS TO BIG, >0 MEANS IT'S ITS FITNESS
CIndividual::CIndividual(CKnapsackProblem* knapsackProblem) {
	fitness = -1;
	size = knapsackProblem->getSize();
	pb_genotype = new bool[size];
	generateGenotype(knapsackProblem);
}

CIndividual::CIndividual(bool* pb_genotype, int size) {
	this->pb_genotype = pb_genotype;
	fitness = -1;
	this->size = size;
}

CIndividual::CIndividual(const CIndividual& pcOther) {
	fitness = pcOther.fitness;
	size = pcOther.size;
	pb_genotype = new bool[size];
	for (int i = 0; i < size; i++) {
		pb_genotype[i] = pcOther.pb_genotype[i];
	}
}

CIndividual::~CIndividual() {
	if (pb_genotype != NULL)
		delete pb_genotype;
}

void CIndividual::calculateFitness(CKnapsackProblem* knapsackProblem) {
	fitness = knapsackProblem->calculateFitness(pb_genotype);
}

void CIndividual::mutate(float mutProb) {
	for (int i = 0; i < size; i++) {
		if (rand() % 100 < mutProb * 100) {
			if (pb_genotype[i] == true)
				pb_genotype[i] = false;
			else
				pb_genotype[i] = true;
		}
	}
}

pair<CIndividual*, CIndividual*> CIndividual::crossover(const CIndividual& parent, float crossProb) {
	if (rand() % 100 < crossProb * 100) {
		bool* pb_genotypeChildOne = new bool[size];
		bool* pb_genotypeChildTwo = new bool[size];
		int crossingPoint = rand() % size;
		for (int i = 0; i < crossingPoint; i++) {
			pb_genotypeChildOne[i] = pb_genotype[i];
			pb_genotypeChildTwo[i] = parent.pb_genotype[i];
		}
		for (int i = crossingPoint; i < size; i++) {
			pb_genotypeChildTwo[i] = pb_genotype[i];
			pb_genotypeChildOne[i] = parent.pb_genotype[i];
		}
		return make_pair(new CIndividual(pb_genotypeChildOne, size), new CIndividual(pb_genotypeChildTwo, size));
	}
	return make_pair(new CIndividual(*this), new CIndividual(parent));
}

double CIndividual::getFitness() {
	return fitness;
}

void CIndividual::generateGenotype(CKnapsackProblem* knapsackProblem) {
	for (int i = 0; i < knapsackProblem->getSize(); i++) {
		int random = rand() % 2;
		if (random == 0)
			pb_genotype[i] = false;
		else
			pb_genotype[i] = true;
	}
}

void CIndividual::showIndividual() {
	cout << "CIndividual:" << endl << "Genotype: ";
	for (int i = 0; i < size; i++) {
		cout << pb_genotype[i];
	}
	cout << endl << "Fitness: " << getFitness() << endl;
}

