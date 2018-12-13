#pragma once
#include "BruteForce.h"
#include "BranchNBound.h"
#include "matrix.h"


class Menu
{
private:
	int option;
	Graph graph;
	BruteForce salesmanBF;
	BranchNBound salesmanBnB;
public:
	Menu();
	~Menu();
	void ChooseOptionMenu();
	int chooseCity() const;
	static int chooseSize();
	static void printPath(std::vector<int> path);
};

