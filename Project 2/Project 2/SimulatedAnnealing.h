#pragma once
#include <vector>

struct result
{
	std::vector<int> path;
	int cost = 0;
};

class SimulatedAnnealing
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

	SimulatedAnnealing(double current_temp, double cooling_temp, double min_temp,
	                   std::vector<std::vector<int>> vectors);

	~SimulatedAnnealing();
	double getCoolingTemp() const;
	void set_cooling_temp(double cooling_temp);
	double getCurrentTemp() const;
	void set_current_temp(double current_temp);
	double getMinTemp() const;
	void set_min_temp(double min_temp);
	int getIterations() const;
	void set_iterations(int iterations);
	result find_solution(double stopTime, int option);
	double probability() const;
	void startingSolution();
	void randomSwap();
	void randomInsert();
	void randomReverse();
	int calculatePathCost(std::vector<int> path);
};

