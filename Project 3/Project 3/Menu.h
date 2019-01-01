#pragma once
#include "matrix.h"
#include "Genetic.h"


class Menu
{
private:
	int option;
	Genetic genetic;
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

