#pragma once
#include <vector>
#include "Algorithm.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

struct result
{
	std::vector<int> path;
	int cost = 0;
	double bestSolutionTime = 0;
	double finalTemp = 0;
};

class SimulatedAnnealing : public Algorithm
{
private:
	double currentTemp;
	double coolingTemp;
	double minTemp;
	int iterations;

	std::vector<std::vector<int>> matrix;

	result finalResult;
	result currentResult;
	result bestResult;
public:
	SimulatedAnnealing();

	SimulatedAnnealing(double cooling_temp, double min_temp,
	                   std::vector<std::vector<int>> vectors, double stopTime, int randOption, int startOption);

	~SimulatedAnnealing();
	double getCoolingTemp() const;
	void set_cooling_temp(double cooling_temp);
	double getCurrentTemp() const;
	void set_current_temp(double current_temp);
	double getMinTemp() const;
	void set_min_temp(double min_temp);
	int getIterations() const;
	void set_iterations(int iterations);
	result find_solution(double stopTime, int chooseRandomOption, int startingSolutionOption);
	double probability() const;
	void startingSolutionGreedy();
	void startingSolutionRand();
	void randomSwap();
	void randomInsert();
	void randomReverse();
	int calculatePathCost(std::vector<int> path);
};

