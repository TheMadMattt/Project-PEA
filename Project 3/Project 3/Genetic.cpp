#include "Genetic.h"



Genetic::Genetic():mutationRatio(-1)
{
}

Genetic::Genetic(double stop_time, int mutation_choice, double mutation_ratio, std::vector<std::vector<int>> vectors)
	: Algorithm(stop_time, mutation_choice),
	mutationRatio(mutation_ratio),
	matrix(std::move(vectors))
{
}

Genetic::~Genetic()
= default;

int Genetic::calculateCost(std::vector<int> path)
{
	//obliczenie kosztu zadanej sciezki
	double pathCost = 0;
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
