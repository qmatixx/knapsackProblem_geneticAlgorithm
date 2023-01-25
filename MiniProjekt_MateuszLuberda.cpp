#include <iostream>
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
using namespace std;

int main()
{
	//string fileName = "size=-1.txt";
	//string fileName = "differentSize.txt";
	//string fileName = "badMaxWeight.txt";
	//string fileName = "badSize.txt";
	//string fileName = "empty.txt";
	//string fileName = "tooBigSize.txt";
	//string fileName = "1.txt";
    string fileName = "Lista6.txt";
	//string fileName = "doesntexist.txt";
	int popSize = 200;
	float crossProb = 0.6f;
	float mutProb = 0.1f;
	int iterationLimit = 1000;
	try {
		CKnapsackProblem knapsackProblem(fileName);
		knapsackProblem.printValues();
		knapsackProblem.printWeights();
		try {
			CGeneticAlgorithm geneticAlgorithm(&knapsackProblem, popSize, crossProb, mutProb, iterationLimit);
			geneticAlgorithm.execute();
			geneticAlgorithm.showSolution();
		}
		catch (invalid_argument& e) {
			cout << e.what() << endl;
		}
	}
	catch (invalid_argument& e) {
		cout << e.what() << endl;
	}
}