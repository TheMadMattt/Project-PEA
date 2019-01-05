#include "Menu.h"
#include <ctime>
#include <iostream>
#include "TimeMeasure.h"

using namespace std;

int main()
{
	srand(time(nullptr));

	/*Menu menu;
	
	menu.ChooseOptionMenu();*/

	double mutationRatio = 0.01, crossingRatio = 0.8;

	int mutationChoice = 2, populationSize = 20;

	result results;
	Graph graph;
	Genetic algorithm;
	int size = 5;
	vector<result> vect;

	graph.readFromFile("ftv47.atsp");
	for (int y = 10; y <= 30; y += 10) {
		const int stopTime = y;
		cout << "Czas algorytmu: " << stopTime << endl;

		//SWAP

		mutationChoice = 1, populationSize = 20;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv47timeSwap20.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 40;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv47timeSwap40.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 60;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv47timeSwap60.txt", stopTime);
		vect.clear();
		results.path.clear();

		//SCRAMBLE

		mutationChoice = 2, populationSize = 20;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv47timeScramble20.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 40;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv47timeScramble40.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 60;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv47timeScramble60.txt", stopTime);
		vect.clear();
		results.path.clear();
	}

	graph.clearMatrix();
	graph.readFromFile("ftv170.atsp");
	for (int y = 10; y <= 30; y += 10) {
		const int stopTime = y;
		cout << "Czas algorytmu: " << stopTime << endl;

		//SWAP

		mutationChoice = 1, populationSize = 20;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv170timeSwap20.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 40;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv170timeSwap40.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 60;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv170timeSwap60.txt", stopTime);
		vect.clear();
		results.path.clear();

		//SCRAMBLE

		mutationChoice = 2, populationSize = 20;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv170timeScramble20.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 40;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv170timeScramble40.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 60;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv170timeScramble60.txt", stopTime);
		vect.clear();
		results.path.clear();
	}

	graph.clearMatrix();
	graph.readFromFile("rbg403.atsp");
	for (int y = 10; y <= 30; y += 10) {
		const int stopTime = y;
		cout << "Czas algorytmu: " << stopTime << endl;

		//SWAP

		mutationChoice = 1, populationSize = 20;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv403timeSwap20.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 40;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv403timeSwap40.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 60;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv403timeSwap60.txt", stopTime);
		vect.clear();
		results.path.clear();

		//SCRAMBLE

		mutationChoice = 2, populationSize = 20;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv403timeScramble20.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 40;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv403timeScramble40.txt", stopTime);
		vect.clear();
		results.path.clear();

		populationSize = 60;

		for (int i = 0; i < size; i++)
		{
			algorithm = Genetic(stopTime, mutationChoice, mutationRatio, crossingRatio, populationSize, graph.getMatrix());
			results = algorithm.find_solution(stopTime);
			cout << results.cost << endl;
			vect.push_back(results);
		}
		TimeMeasure::saveToFile(vect, "ftv403timeScramble60.txt", stopTime);
		vect.clear();
		results.path.clear();
	}

	system("pause");
	return 0;
}