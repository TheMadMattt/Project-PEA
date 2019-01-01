#pragma once
#include "Algorithm.h"
#include <vector>
#include <chrono>
#include <queue>

typedef std::chrono::high_resolution_clock Clock;

struct result
{
	std::vector<int> path;
	int cost = 0;
	double bestSolutionTime = 0;
};

struct compareCost	//struktura pozwalajaca na wybranie najmniejszego kosztu wierzcholka (potrzebne w kolejce priorytetowej)
{
	bool operator()(const result& l, const result& r) const
	{
		return l.cost > r.cost;
	}
};

class Genetic : public Algorithm
{
private:
	double mutationRatio;
	int populationSize;

	std::vector<std::vector<int>> matrix;

	result bestResult;
public:
	Genetic();

	Genetic(double stop_time, int mutation_choice, double mutation_ratio,
		int population_size, std::vector<std::vector<int>> vectors);

	~Genetic();

	std::priority_queue<result, std::vector<result>, compareCost> createPopulation();
	result swap(int stopTime);
	result scramble(int stopTime);
	result findSolution(int stopTime);

	int calculateCost(std::vector<int> path);

	double getMutationRatio() const;
	void set_mutation_ratio(double mutation_ratio);

	int getPopulationSize() const;
	void set_population_size(int population_size);
};

