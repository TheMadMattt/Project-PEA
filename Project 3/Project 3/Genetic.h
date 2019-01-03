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

struct compareCostMutation	//struktura pozwalajaca na wybranie najmniejszego kosztu wierzcholka (potrzebne w kolejce priorytetowej)
{
	bool operator()(const result& l, const result& r) const
	{
		return l.cost > r.cost;
	}
};

struct compareCostCrossing	//struktura pozwalajaca na wybranie najmniejszego kosztu wierzcholka (potrzebne w kolejce priorytetowej)
{
	bool operator()(const result& l, const result& r) const
	{
		return l.cost < r.cost;
	}
};

typedef std::priority_queue<result, std::vector<result>, compareCostMutation> queue;

class Genetic : public Algorithm
{
private:
	double mutationRatio;
	double crossingRatio;
	int populationSize;

	std::vector<std::vector<int>> matrix;

	result bestResult;
public:
	Genetic();

	Genetic(int stop_time, int mutation_choice, double mutation_ratio, double crossing_ratio,
		int population_size, std::vector<std::vector<int>> vectors);

	~Genetic();

	std::vector<result> createPopulation();
	result swap(int stopTime);
	result scramble(int stopTime);
	result inversion(int stopTime);
	result mutationAlgorithm(int stopTime);

	result cross(const std::vector<int>& parent1, std::vector<int> parent2);
	result crossingAlgorithm(int stopTime);

	int calculateCost(std::vector<int> path);

	double getMutationRatio() const;
	void set_mutation_ratio(double mutation_ratio);

	double getCrossingRatio() const;
	void set_crossing_ratio(double crossing_ratio);

	int getPopulationSize() const;
	void set_population_size(int population_size);
};

