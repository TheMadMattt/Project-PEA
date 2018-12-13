#include "BruteForce.h"
#include <iostream>
#include <algorithm>


BruteForce::BruteForce(): minimalPathCost(INT_MAX)
{
}


BruteForce::~BruteForce()
{
	path.clear();
}

BruteForce BruteForce::bruteForceTSP(std::vector<std::vector<int>> graph, int startingCity)
{
	BruteForce buff;
	std::vector<int> tab;	//do przechowywania wszystkich wierzcholkow poza startowym
	std::vector<int> path;	//do przechowywania sciezki
	int minimum = INT_MAX;	//minimalny koszt sciezki

	for (int i = 0; i < graph.size(); i++)
	{
		if (i != startingCity)
		{
			tab.push_back(i); //do wektora dodajemy pozosta�e wierzcho�ki (wszystkie opr�cz startowego)
		}
	}

	do
	{
		int currentWeight = 0;
		int nextCity = startingCity;

		path.push_back(startingCity);	//Pierwszy wierzcho�ek drogi to wierzcho�ek startowy
		for (int i = 0; i < graph.size() -1; i++)		//wyliczenie aktualnej wagi
		{
			currentWeight += graph[nextCity][tab[i]];
			nextCity = tab[i];
			path.push_back(tab[i]);		//Dodanie do �cie�ki kolejnego wierzcho�ka
		}
		currentWeight += graph[nextCity][startingCity]; //powrot z ostatniego miasta do poczatkowego
		path.push_back(startingCity); //Ostatni element �cie�ki do wierzcho�ek startowy - �cie�ka kompletna
		if (currentWeight < minimum)	//Sprawdzenie czy waga �cie�ki jest wi�ksza lub mniejsza od minimalnej
		{
			buff.path = path;	//uaktualnienie sciezki
		}
		else
		{
			path.clear(); //wyczyszczenie sciezki w celu znalezienia nowej
		}

		minimum = std::min(minimum, currentWeight);		//porownanie minimalnej wagi do aktualnej i wybor mniejszej
	} while (std::next_permutation(tab.begin(), tab.end()));		//kolejne permutacje zadanej tablicy (n-1)! -> poniewaz asymetryczne
	buff.minimalPathCost = minimum;

	return buff;
}

int BruteForce::getWeight() const
{
	return minimalPathCost;
}

void BruteForce::clearBuffor()
{
	this->minimalPathCost = INT_MAX;
	this->path.clear();
}

std::vector<int> BruteForce::getPath() const
{
	return path;
}
