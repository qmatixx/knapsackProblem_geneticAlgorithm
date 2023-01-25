#include <iostream>
#include <fstream>
#include "CKnapsackProblem.h"
using namespace std;

CKnapsackProblem::CKnapsackProblem(string& fileName) {
	ifstream loadedFile(fileName);
	if (!loadedFile.good())
		throw invalid_argument("File ''" + fileName + "'' doesn't exist");
	if (loadedFile.peek() == ifstream::traits_type::eof())
		throw invalid_argument("File ''" + fileName + "'' is empty");
	loadedFile.close();
	loadFromFile(fileName);
}

CKnapsackProblem::~CKnapsackProblem() {
	if (pd_weights != NULL)
		delete[] pd_weights;
	if (pd_values != NULL)
		delete[] pd_values;
}

double CKnapsackProblem::calculateFitness(bool* pi_genotype) {
	double solutionValue = 0;
	double solutionWeight = 0;
	for (int i = 0; i < size; i++) {
		if (pi_genotype[i] == true) {
			solutionValue += pd_values[i];
			solutionWeight += pd_weights[i];
		}
	}
	if (solutionWeight > maxWeight)
		return 0;
	return solutionValue;
}

int CKnapsackProblem::getSize() {
	return size;
}

double CKnapsackProblem::getMaxWeight() {
	return maxWeight;
}

void CKnapsackProblem::printWeights() {
	cout << "Weights: ";
	for (int i = 0; i < size; i++)
		cout << pd_weights[i] << " ";
	cout << endl;
}

void CKnapsackProblem::printValues() {
	cout<<"Values: ";
	for (int i = 0; i < size; i++)
		cout << pd_values[i] << " ";
	cout << endl;
}

void CKnapsackProblem::loadFromFile(string& fileName) {
	ifstream loadedFile(fileName);
	//CHECKING FIRST TWO PARAMETERS
	if (loadedFile >> size) {}
	else throw invalid_argument("Size must be an integer");
	if (size < 0) throw invalid_argument("Size must be bigger than 0");
	if (loadedFile >> maxWeight) {}
	else throw invalid_argument("MaxWeight must be a double number");
	//MAIN LOOP
	double value, weight;
	pd_values = new double[size];
	pd_weights = new double[size];
	int i = 0;
	bool flag = true;
	while (loadedFile >> value)
	{
		flag = false;
		pd_values[i] = value;
		if (loadedFile >> weight) {
			pd_weights[i] = weight;
			flag = true;
		}
		i++;
	}
	//CHECKING OTHER EXCEPTIONS
	if (flag == false) throw invalid_argument("Size of values and size of weights must be the same");
	if (i != size) throw invalid_argument("Size of values and weights have to be the same as size");
	loadedFile.close();
}