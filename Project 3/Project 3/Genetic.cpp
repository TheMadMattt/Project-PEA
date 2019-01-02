#include "Genetic.h"
#include <random>
#include <strstream>
#include <iostream>


Genetic::Genetic() :mutationRatio(-1), populationSize(-1)
{
}

Genetic::Genetic(double stop_time, int mutation_choice, double mutation_ratio
	, int population_size, std::vector<std::vector<int>> vectors)
	: Algorithm(stop_time, mutation_choice),
	mutationRatio(mutation_ratio),
	populationSize(population_size),
	matrix(std::move(vectors))
{
}

Genetic::~Genetic()
= default;

std::priority_queue<result, std::vector<result>, compareCost> Genetic::createPopulation()
{
	std::priority_queue<result, std::vector<result>, compareCost> pq;

	for (int i = 0; i < populationSize; i++)
	{
		result population;
		for (int y = 0; y < matrix.size(); y++)
		{
			population.path.push_back(y);
		}
		population.path.push_back(population.path[0]);
		std::shuffle(population.path.begin() + 1, population.path.end() - 1, std::mt19937(std::random_device()()));

		population.cost = calculateCost(population.path);

		pq.push(population);
	}

	return pq;
}

result Genetic::swap(int stopTime)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 1.0); //losowanie liczb z przedzialu <0;1.0>
	std::priority_queue<result, std::vector<result>, compareCost> pq = createPopulation();
	bool exitLoop = false;
	bestResult = pq.top();

	const auto start = std::chrono::high_resolution_clock::now();
	while (!exitLoop) {
		result population = pq.top();
		pq.pop();

		const int cityNumber = bestResult.path.size();
		int a = rand() % (cityNumber - 2) + 1;
		int b = rand() % (cityNumber - 2) + 1;

		while (a == b)
			b = rand() % (cityNumber - 2) + 1;

		if (distribution(generator) < mutationRatio)
		{
			std::swap(population.path.at(a), population.path.at(b));
		}

		population.cost = calculateCost(population.path);

		pq.push(population);

		if (population.cost < bestResult.cost)
		{
			bestResult = population;
			bestResult.bestSolutionTime = std::chrono::duration_cast<std::chrono::microseconds>
				(Clock::now() - start).count();
		}

		if (std::chrono::duration_cast<std::chrono::seconds>
			(Clock::now() - start).count() >= stopTime) //zakonczenie algorytmu jezeli czas dzialania jest wiekszy niz zadany
		{
			exitLoop = true;
		}
	}

	return bestResult;
}

result Genetic::scramble(int stopTime)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 1.0); //losowanie liczb z przedzialu <0;1.0>
	std::priority_queue<result, std::vector<result>, compareCost> pq = createPopulation();
	bool exitLoop = false;
	bestResult = pq.top();

	const auto start = std::chrono::high_resolution_clock::now();
	while (!exitLoop)
	{
		result population = pq.top();
		pq.pop();

		const int cityNumber = population.path.size();
		int a = rand() % (cityNumber - 2) + 1;
		int b = rand() % (cityNumber - 2) + 1;

		while (a == b)
			b = rand() % (cityNumber - 2) + 1;

		if (distribution(generator) < mutationRatio)
		{
			if (a < b) {
				std::shuffle(population.path.begin() + a, population.path.begin() + b,
				             std::mt19937(std::random_device()()));
			}
			else
			{
				std::shuffle(population.path.begin() + b, population.path.begin() + a,
				             std::mt19937(std::random_device()()));
			}
		}

		population.cost = calculateCost(population.path);

		pq.push(population);

		if (population.cost < bestResult.cost)
		{
			bestResult = population;
			bestResult.bestSolutionTime = std::chrono::duration_cast<std::chrono::microseconds>
				(Clock::now() - start).count();
		}

		if (std::chrono::duration_cast<std::chrono::seconds>
			(Clock::now() - start).count() >= stopTime) //zakonczenie algorytmu jezeli czas dzialania jest wiekszy niz zadany
		{
			exitLoop = true;
		}
	}

	return bestResult;
}

result Genetic::mutate(int stopTime)
{
	switch (getMutationChoice())
	{
	case 1:
		bestResult = swap(stopTime);
		break;
	case 2:
		bestResult = scramble(stopTime);
		break;
	default:
		bestResult = swap(stopTime);
		break;
	}

	return bestResult;
}

/*result Genetic::crossover(int stopTime)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 1.0); //losowanie liczb z przedzialu <0;1.0>
	std::priority_queue<result, std::vector<result>, compareCost> pq = createPopulation();
	bool exitLoop = false;
	bestResult = pq.top();

	const auto start = std::chrono::high_resolution_clock::now();
	while (!exitLoop)


	return bestResult;
}*/

int Genetic::calculateCost(std::vector<int> path)
{
	//obliczenie kosztu zadanej sciezki
	int pathCost = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		pathCost += matrix[path[i]][path[i + 1]];
	}
	return pathCost;
}

double Genetic::getMutationRatio() const
{
	return mutationRatio;
}

void Genetic::set_mutation_ratio(double mutation_ratio)
{
	mutationRatio = mutation_ratio;
}

int Genetic::getPopulationSize() const
{
	return populationSize;
}

void Genetic::set_population_size(int population_size)
{
	populationSize = population_size;
}
