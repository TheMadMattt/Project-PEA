#include "SimulatedAnnealing.h"
#include <complex>
#include <random>
#include <ctime>
#include <utility>
#include <chrono>
#include <iostream>


SimulatedAnnealing::SimulatedAnnealing(): currentTemp(-1), coolingTemp(-1), minTemp(-1)
{
}

SimulatedAnnealing::SimulatedAnnealing(double cooling_temp, double min_temp,
	std::vector<std::vector<int>> vectors, double stopTime, int randOption, int startOption)
	: coolingTemp(cooling_temp), minTemp(min_temp), matrix(std::move(vectors))
{
	this->iterations = pow(matrix.size(), 2) / 4;
	this->set_stop_time(stopTime);
	this->set_choose_random_option(randOption);
	this->set_choose_starting_option(startOption);
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

result SimulatedAnnealing::find_solution(int stopTime, bool diverse)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	bool exitLoop = false;
	int maxSwaps = 2000;
	int maxAcceptedSwaps = 1000;
	int noIterationChange = 0;
	auto start = std::chrono::high_resolution_clock::now();
	switch (this->choose_starting_option())
	{
	case 1:
		startingSolutionGreedy();
		break;
	case 2:
		startingSolutionRand();
		break;
	default: startingSolutionRand();
	}
	result finalResult = currentResult;
	int prevCurrentCost = currentResult.cost;
	int prevBestCost = currentResult.cost;
	this->currentTemp = 1.5*currentResult.cost;
	double startingTemp = currentTemp;
	while (!exitLoop)
	{
		auto swapsTried = 0;
		auto swapsAccepted = 0;
		while(swapsTried < maxSwaps && swapsAccepted < maxAcceptedSwaps)
		{
			switch(this->choose_random_option()){
			case 1: 
				randomSwap();
				break;
			case 2:
				randomInsert();
				break;
			case 3:
				randomReverse();
				break;
			default: randomSwap();
			}
			swapsTried++;
			currentResult.cost = calculatePathCost(currentResult.path);
			if(currentResult.cost < bestResult.cost || distribution(generator) < probability())
			{
				swapsAccepted++;
				bestResult = currentResult;
				if(bestResult.cost < finalResult.cost)
				{
					bestResult.bestSolutionTime = std::chrono::duration_cast<std::chrono::microseconds>
						(Clock::now() - start).count();
					bestResult.finalTemp = currentTemp;
					finalResult = bestResult;

				}
			}
			if (std::chrono::duration_cast<std::chrono::seconds>
				(Clock::now() - start).count() >= stopTime)
			{
				exitLoop = true;
				break;
			}
		}
		if(exitLoop)
		{
			break;
		}
		const auto swapsRatio = static_cast<double>(swapsAccepted) / swapsTried;
		if(prevCurrentCost == currentResult.cost)
		{
			noIterationChange++;
		}else
		{
			noIterationChange = 0;
		}
		prevCurrentCost = currentResult.cost;

		currentTemp *= coolingTemp;

		if(diverse && (noIterationChange >= 10 || swapsRatio < minTemp || currentTemp < minTemp))
		{
			if(prevBestCost != finalResult.cost)
			{
				std::cout << "Reached local minimum - starting over from best path (best " << finalResult.cost << ")\n";
				currentResult = finalResult;
				prevBestCost = finalResult.cost;

				currentTemp = startingTemp;
			}else
			{
				std::cout << "Best path doesn't improve - starting over from best path and increasing temperature (best " << finalResult.cost << ")\n";
				currentResult = finalResult;

				startingTemp *= 100;
				currentTemp = startingTemp;
				maxSwaps *= 10;
				maxAcceptedSwaps *= 10;
			}
		}
	}
	return finalResult;
}

double SimulatedAnnealing::probability() const
{
	const double power = -((currentResult.cost - bestResult.cost) / currentTemp);
	return exp(power);
}

std::vector<int> SimulatedAnnealing::getUnvisited(std::vector<int> path)
{
	std::vector<bool> visited(matrix.size(), false);	// true if vert visited in path
	for (auto i : path)
	{
		visited[i] = true;
	}
	std::vector<int> unvisited;
	for (auto i = 0; i < matrix.size(); i++)
		if (!visited[i])
			unvisited.push_back(i);

	return unvisited;
}

void SimulatedAnnealing::startingSolutionGreedy()
{
	currentResult.path.clear();
	currentResult.cost = 0;

	currentResult.path.resize(1, 0);
	auto v = 0;
	while (currentResult.path.size() < static_cast<unsigned>(matrix.size()))
	{
		auto current_best = INT_MAX;
		auto best_u = 0;
		for (auto u : getUnvisited(currentResult.path))
		{
			if (matrix[v][u] < current_best)
			{
				best_u = u;
				current_best = matrix[v][u];
			}
		}
		v = best_u;
		currentResult.path.push_back(v);
	}

	currentResult.path.push_back(currentResult.path[0]);

	currentResult.cost = calculatePathCost(currentResult.path);
	bestResult = currentResult;
}

void SimulatedAnnealing::startingSolutionRand()
{
	currentResult.path.clear();
	currentResult.cost = 0;

	currentResult.path.resize(matrix.size() + 1);

	for(int i=0; i < matrix.size(); i++)
	{
		currentResult.path[i] = i;
	}
	currentResult.path[currentResult.path.size() - 1] = 0;

	std::shuffle(currentResult.path.begin() + 1, currentResult.path.end() - 1, std::mt19937(std::random_device()()));

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

void SimulatedAnnealing::randomReverse()
{
	const int cityNumber = bestResult.path.size();
	int a = rand() % (cityNumber - 2) + 1;
	int b = rand() % (cityNumber - 2) + 1;

	while (a == b)
		b = rand() % (cityNumber - 2) + 1;

	result tempResult = bestResult;

	if (a < b) {
		std::reverse(tempResult.path.begin() + a, tempResult.path.begin() + b);
	}else
	{
		std::reverse(tempResult.path.begin() + b , tempResult.path.begin() + a);
	}

	currentResult = std::move(tempResult);
}

int SimulatedAnnealing::calculatePathCost(std::vector<int> path)
{
	double pathCost = 0;
	for (int i = 0; i < path.size()-1; i++)
	{
		pathCost += matrix[path[i]][path[i+1]];
	}
	return pathCost;
}