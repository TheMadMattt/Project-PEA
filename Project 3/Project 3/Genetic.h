#pragma once
#include "Algorithm.h"
#include <vector>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

struct result
{
	std::vector<int> population;
	int cost = 0;
	double bestSolutionTime = 0;
};

class Genetic : public Algorithm
{
private:
	double mutationRatio;

	std::vector<std::vector<int>> matrix;

	result bestResult;
public:
	Genetic();

	Genetic(double stop_time, int mutation_choice, double mutation_ratio, std::vector<std::vector<int>> vectors);

	~Genetic();

	int calculateCost(std::vector<int> path);

	double getMutationRatio() const;
	void set_mutation_ratio(double mutation_ratio);
};

