#include "Genetic.h"
#include <random>


Genetic::Genetic() :mutationRatio(-1), populationSize(-1)
{
}

Genetic::Genetic(int stop_time, int mutation_choice, double mutation_ratio, double crossing_ratio
	, int population_size, std::vector<std::vector<int>> vectors)
	: Algorithm(stop_time, mutation_choice),
	mutationRatio(mutation_ratio),
	crossingRatio(crossing_ratio),
	populationSize(population_size),
	matrix(std::move(vectors))
{
}

Genetic::~Genetic()
= default;

std::vector<result> Genetic::createPopulation()
{
	std::vector<result> populationVec;
	for (int i = 0; i < populationSize; i++)
	{
		result population;
		for (int y = 0; y < matrix.size(); y++)
		{
			population.path.push_back(y);
		}
		std::shuffle(population.path.begin(), population.path.end(), std::mt19937(std::random_device()()));
		population.path.push_back(population.path[0]);

		population.cost = calculateCost(population.path);

		populationVec.push_back(population);
	}

	return populationVec;
}

result Genetic::swap(result subject)
{
	const int cityNumber = subject.path.size();
	int a = rand() % (cityNumber - 2) + 1;
	int b = rand() % (cityNumber - 2) + 1;

	while (a == b)
		b = rand() % (cityNumber - 2) + 1;

	std::swap(subject.path.at(a), subject.path.at(b));
	subject.cost = calculateCost(subject.path);

	return subject;
}

result Genetic::scramble(result subject)
{
	const int cityNumber = subject.path.size();
	int a = rand() % (cityNumber - 2) + 1;
	int b = rand() % (cityNumber - 2) + 1;

	while (a == b)
		b = rand() % (cityNumber - 2) + 1;

	if (a > b)
	{
		const int temp = b;
		b = a;
		a = temp;
	}
	std::shuffle(subject.path.begin() + a, subject.path.begin() + b,
		std::mt19937(std::random_device()()));
	subject.cost = calculateCost(subject.path);

	return subject;
}

result Genetic::inversion(result subject)
{
	const int cityNumber = subject.path.size();
	int a = rand() % (cityNumber - 2) + 1;
	int b = rand() % (cityNumber - 2) + 1;

	while (a == b)
		b = rand() % (cityNumber - 2) + 1;

	if (a > b)
	{
		const int temp = b;
		b = a;
		a = temp;
	}

	std::reverse(subject.path.begin() + a, subject.path.begin() + b);
	subject.cost = calculateCost(subject.path);

	return subject;
}

result Genetic::findSolution(int stopTime)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 1.0); //losowanie liczb z przedzialu <0;1.0>
	std::vector<result> popVec = createPopulation();
	std::sort(popVec.begin(), popVec.end(), compareCost());

	bool exitLoop = false;
	bestResult = popVec.at(0);
	const auto start = std::chrono::high_resolution_clock::now();
	while (!exitLoop) {

		if (distribution(generator) < crossingRatio)
		{
			result parent1 = popVec.at(rand() % popVec.size());
			result parent2 = popVec.at(rand() % popVec.size());

			result child = cross(parent1.path, parent2.path);
			popVec.push_back(child);
		}

		if (distribution(generator) < mutationRatio) {
			int index = rand() % popVec.size();
			result subject = popVec.at(index);
			switch (getMutationChoice())
			{
			case 1:
				subject = swap(subject);
				break;
			case 2:
				subject = scramble(subject);
				break;
			case 3:
				subject = inversion(subject);
				break;
			default:
				subject = swap(subject);
				break;
			}
			popVec.at(index) = subject;
		}

		std::sort(popVec.begin(), popVec.end(), compareCost());

		result newBest = popVec.at(0);

		if(newBest.cost < bestResult.cost)
		{
			bestResult = newBest;
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

result Genetic::cross(const std::vector<int>& parent1, const std::vector<int>& parent2)
{
	result child1, child2;
	std::vector<bool> child1Visited, child2Visited;

	child1Visited.resize(matrix.size(),false);
	child2Visited.resize(matrix.size(),false);

	int half = matrix.size()/2;

	for (int i = 0; i < half; i++)
	{
		child1.path.push_back(parent1.at(i));
		child1Visited.at(child1.path.at(i)) = true;

		child2.path.push_back(parent2.at(i));
		child2Visited.at(child2.path.at(i)) = true;
	}

	for (int i = 0; i < parent1.size()-1; i++)
	{
		if(!child1Visited[parent2.at(i)])
		{
			child1.path.push_back(parent2.at(i));
		}
		if(!child2Visited[parent1.at(i)])
		{
			child2.path.push_back(parent1.at(i));
		}
	}

	child1.path.push_back(child1.path.at(0));
	child2.path.push_back(child2.path.at(0));

	child1.cost = calculateCost(child1.path);
	child2.cost = calculateCost(child2.path);

	if(child1.cost < child2.cost)
	{
		return child1;
	}

	return child2;
}

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

double Genetic::getCrossingRatio() const
{
	return crossingRatio;
}

void Genetic::set_crossing_ratio(double crossing_ratio)
{
	crossingRatio = crossing_ratio;
}

int Genetic::getPopulationSize() const
{
	return populationSize;
}

void Genetic::set_population_size(int population_size)
{
	populationSize = population_size;
}
