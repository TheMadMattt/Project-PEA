#pragma once
#include "matrix.h"
#include "Algorithm.h"
#include "SimulatedAnnealing.h"

class Menu
{
private:
	int option;
	Algorithm algorithm;
	SimulatedAnnealing SAalgorithm;
	Graph graph;
	result result;
public:
	Menu();
	~Menu();
	void ChooseOptionMenu();
	int chooseCity() const;
	static int chooseSize();
	static void printPath(std::vector<int> path);
};

