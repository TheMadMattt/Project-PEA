#pragma once
#include <vector>

class BruteForce
{
private:
	int minimalPathCost;
	std::vector<int> path;
public:
	BruteForce();
	~BruteForce();
	static BruteForce bruteForceTSP(std::vector<std::vector<int>> graph, int startingCity); //algorytm brute force
	int getWeight() const;
	void clearBuffor(); //czyszczenie sciezki oraz kosztu
	std::vector<int> getPath() const; //zwrocenie sciezki
};

