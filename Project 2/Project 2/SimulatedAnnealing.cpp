#include "SimulatedAnnealing.h"
#include <complex>
#include <random>
#include <ctime>
#include <utility>
#include <iostream>


SimulatedAnnealing::SimulatedAnnealing(): currentTemp(-1), coolingTemp(-1), minTemp(-1)
{
}

SimulatedAnnealing::SimulatedAnnealing(double current_temp, double cooling_temp, double min_temp,
                                       std::vector<std::vector<int>> vectors)
	: currentTemp(current_temp),
	coolingTemp(cooling_temp),
	minTemp(min_temp),
	matrix(std::move(vectors))
{
	this->iterations = pow(matrix.size(), 2) / 4;
}

SimulatedAnnealing::~SimulatedAnnealing()
= default;

double SimulatedAnnealing::getCoolingTemp() const
{
	return coolingTemp;
}

void SimulatedAnnealing::set_cooling_temp(double cooling_temp)
{
	coolingTemp = cooling_temp;
}

double SimulatedAnnealing::getCurrentTemp() const
{
	return currentTemp;
}

void SimulatedAnnealing::set_current_temp(double current_temp)
{
	currentTemp = current_temp;
}

double SimulatedAnnealing::getMinTemp() const
{
	return minTemp;
}

void SimulatedAnnealing::set_min_temp(double min_temp)
{
	minTemp = min_temp;
}

int SimulatedAnnealing::getIterations() const
{
	return iterations;
}

void SimulatedAnnealing::set_iterations(int iterations)
{
	this->iterations = iterations;
}

result SimulatedAnnealing::find_solution(double stopTime, int option)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	startingSolution();
	finalResult = currentResult;
	const clock_t start = clock();
	while (currentTemp > minTemp)
	{
		for (int i = 0; i < iterations; i++)
		{
			if (option == 1) {
				randomSwap();
			}else if(option == 2)
			{
				randomInsert();
			}
			currentResult.cost = calculatePathCost(currentResult.path);
			if(currentResult.cost < bestResult.cost || distribution(generator) < probability())
			{
				bestResult = currentResult;
				if(bestResult.cost < finalResult.cost)
				{
					finalResult = bestResult;
				}
			}
		}

		if(((double)(clock() - start)/CLOCKS_PER_SEC) == stopTime && stopTime > 0)
		{
			break;
		}
	}
	return finalResult;
}

double SimulatedAnnealing::probability() const
{
	const double power = -((currentResult.cost - bestResult.cost) / currentTemp);
	return exp(power);
}

void SimulatedAnnealing::startingSolution()
{
	currentResult.path.clear();
	currentResult.cost = 0;

	int min = INT_MAX;
	int city_x = 0, city_y = 0;
	std::vector<bool> visited(matrix.size(), false);
	currentResult.path.resize(matrix.size() + 1);

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int y = 0; y < matrix.size(); y++)
		{
			if (matrix[i][y] < min && matrix[i][y] > 0)
			{
				min = matrix[i][y];
				city_x = i;
			}
		}
	}

	currentResult.path[0] = city_x;
	visited[city_x] = true;

	for (int i = 1; i < matrix.size(); i++)
	{
		min = INT_MAX;
		for (int y = 0; y < matrix.size(); y++)
		{
			if (!visited[y] && matrix[city_x][y] < min && matrix[city_x][y] > 0)
			{
				min = matrix[city_x][y];
				city_y = y;
			}
		}
		visited[city_y] = true;
		city_x = city_y;
		currentResult.path[i] = city_x;
	}
	currentResult.path[matrix.size()] = currentResult.path[0];

	currentResult.cost = calculatePathCost(currentResult.path);
	bestResult = currentResult;
}

void SimulatedAnnealing::randomSwap()
{
	const int cityNumber = bestResult.path.size();
	int cityA = std::rand() % (cityNumber - 2) + 1;
	int cityB = std::rand() % (cityNumber - 2) + 1;

	while (cityA == cityB) cityB = std::rand() % (cityNumber - 2) + 1;

	currentResult.path = bestResult.path;
	const int temp = currentResult.path[cityA];
	currentResult.path[cityA] = currentResult.path[cityB];
	currentResult.path[cityB] = temp;
}

void SimulatedAnnealing::randomInsert()
{
	const int cityNumber = bestResult.path.size();
	int a = rand() % (cityNumber - 2) + 1;
	int b = rand() % (cityNumber - 2) + 1;

	while (a == b)
		b = rand() % (cityNumber - 2) + 1;

	result tempResult = bestResult;
	const auto it = tempResult.path.begin();
	const int tmp = tempResult.path[a];
	tempResult.path.erase(it + a);
	tempResult.path.insert(it + b, tmp);

	currentResult = std::move(tempResult);
}

int SimulatedAnnealing::calculatePathCost(std::vector<int> path)
{
	double pathCost = 0;
	int previous = 0;
	for (int i = 0; i < path.size(); i++)
	{
		pathCost += matrix[previous][path[i]];
		previous = path[i];
	}
	pathCost += matrix[previous][0];
	return pathCost;
}



