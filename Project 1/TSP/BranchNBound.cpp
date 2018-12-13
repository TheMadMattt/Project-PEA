#include "BranchNBound.h"
#include "matrix.h"
#include <queue>


BranchNBound::BranchNBound() : minimalPathCost(INT_MAX), startCity(0), correctPath(false)
{
}


BranchNBound::~BranchNBound()
= default;

BranchNBound BranchNBound::BranchNBoundTSP(const std::vector<std::vector<int>>& matrix, int startingCity)
{
	BranchNBound salesman;
	bool tspFinish;
	std::priority_queue<BnB, std::vector<BnB>, compareCost> vectors; //kolejka priorytetowa ktora zawiera struktury od najmniejszego kosztu do najwiekszego
	const BnB firstMatrix = reduceFirstMatrix(matrix, startingCity, matrix.size()); //wyliczenie pierwszej macierzy redukcji oraz kosztu startowego wierzcho³ka, z której bêdziemy korzystaæ w algorytmie
	vectors.push(firstMatrix); //dodanie struktury do vektora (kolejki)
	this->startCity = startingCity; //zapisanie miasta startowego

	do
	{
		BnB currentMatrix = vectors.top(); //pobranie wierzcholka o najmniejszej wadze
		vectors.pop(); //usuniecie go z kolejki priorytetowej
		for(int i=0;i<currentMatrix.matrix.size();i++)
		{
			if(!currentMatrix.visited[i])
			{
				BnB newMatrix;
				newMatrix.cost = 0; //ustawienie kosztu wierzcholka na 0
				newMatrix.vertex = i; //ustawienie wierzcholka
				newMatrix.path = currentMatrix.path; //przypisanie juz utworzonej drogi do nowej struktury
				newMatrix.path.push_back(i); //dodanie wierzcholka do drogi
				newMatrix.visited = currentMatrix.visited; //przypisanie odwiedzonych wierzcholkow do nowej struktury
				newMatrix.visited[i] = true; //ustawienie wierzcholka jako odwiedzonego
				newMatrix.matrix = setInfinity(currentMatrix.matrix, currentMatrix.vertex, i); //ustawienie nieskonczonosci (-1) na w zadanym wierzu i kolumnie
				newMatrix = reduceMatrix(newMatrix); //zredukowanie macierzy
				newMatrix.cost = calculateCost(currentMatrix.matrix, currentMatrix.cost, newMatrix.cost, currentMatrix.vertex, i);
				//obliczenie kosztu dla wierzcholka
				vectors.push(newMatrix); //dodanie nowej struktury do wektora (kolejki)
			}
		}

		salesman.minimalPathCost = currentMatrix.cost; //przypisanie aktualnego kosztu sciezki
		salesman.path = currentMatrix.path; //przypisanie aktualnej sciezki

		if (vectors.size() >= 1000000)
		{
			salesman.correctPath = false; //sciezka nie znaleziona
			break;
		}

		salesman.correctPath = true;
		tspFinish = isVisited(currentMatrix.visited); //sprawdzenie czy zostaly odwiedzone wszystkie wierzcholki
	} while (tspFinish); //jezeli wszystkie wierzcholki zostaly odwiedzone petla konczy dzialanie

	salesman.startCity = this->startCity;
	if (salesman.correctPath) {
		salesman.path.push_back(salesman.startCity); //dodanie miasta startowego jako ostatniego miasta w celu zamkniecia sciezki
	}

	return salesman;
}

BnB BranchNBound::reduceFirstMatrix(std::vector<std::vector<int>> matrix, int startingCity, int size)
{
	BnB firstMatrix;
	int reducedCost = 0;
	//ustawienie -1 na przekatnych macierzy
	for(int i=0;i<matrix.size();i++)
	{
		for(int y=0;y<matrix.size();y++)
		{
			if(i==y)
			{
				matrix[i][y] = -1; //ustawienie przekatnej macierzy jako -1 w celu poprawnosci wykonania algorytmu
			}
		}
	}

	std::vector<int> row(size, INT_MAX);
	std::vector<int> col(size, INT_MAX);

	//wybranie najmniejszej wartosci z wiersza
	for (int i = 0; i < size; i++)
	{
		for (int y = 0; y < size; y++)
		{
			if (row[i] > matrix[i][y] && matrix[i][y] >= 0)
			{
				row[i] = matrix[i][y]; 
			}
		}
	}

	//odjecie najmniejszej wartosci z wiersza od pozostalych
	for (int i = 0; i < size; i++)
	{
		for (int y = 0; y < size; y++)
		{
			if (matrix[i][y] > 0) {
				matrix[i][y] -= row[i];
			}
		}
	}

	//wybranie najmniejszej wartosci z kolumny
	for (int i = 0; i < size; i++)
	{
		for (int y = 0; y < size; y++)
		{
			if (col[i] > matrix[y][i] && matrix[y][i] >= 0)
			{
				col[i] = matrix[y][i];
			}
		}
	}

	//odjecie najmniejszej wartosci z kolumny od pozostalych
	for (int i = 0; i < size; i++)
	{
		for (int y = 0; y < size; y++)
		{
			if (matrix[y][i] > 0)
			{
				matrix[y][i] -= col[i];
			}
		}
	}

	//wyliczenie kosztu startowego wierzcholka
	for (int i = 0; i < size; i++)
	{
		reducedCost += col[i] + row[i];
	}

	//przypisanie danych
	firstMatrix.matrix = matrix;
	firstMatrix.path.push_back(startingCity);
	firstMatrix.visited = std::vector<bool>(size, false);
	firstMatrix.visited[startingCity] = true;
	firstMatrix.vertex = startingCity;
	firstMatrix.cost = reducedCost;

	return firstMatrix;
}

BnB BranchNBound::reduceMatrix(BnB branch)
{
	int reduce;
	int reductionCost = 0;
	std::vector<int> col;

	for (int i = 0; i < branch.matrix.size(); i++)
	{
		if (!checkVec(branch.matrix[i])) //sprawdzenie czy w wierszu istnieja zera, jesli tak to zredukowany
		{
			reduce = getMinimum(branch.matrix[i]); //znalezienie minimum
			reductionCost += reduce; //zaktualizowanie kosztu redukcji
			for (int y = 0; y < branch.matrix.size(); y++)
			{
				if (branch.matrix[i][y] > 0) {
					branch.matrix[i][y] -= reduce; //odjecie od pozostalych wartosci wartosci minimalnej w celu zredukowania wiersza
				}
			}
		}
	}

	for (int i = 0; i < branch.matrix.size(); i++)
	{
		col.clear();
		for (int y = 0; y < branch.matrix.size(); y++)
		{
			col.push_back(branch.matrix[y][i]); //utworzenie pomocniczej zmiennej w cely przechowywania kolumn
		}
		if (!checkVec(col)) //sprawdzenie czy w wierszu istnieja zera, jesli tak to zredukowany
		{
			reduce = getMinimum(col);
			reductionCost += reduce;
			for (int y = 0; y < branch.matrix.size(); y++)
			{
				if (branch.matrix[y][i] > 0) {
					branch.matrix[y][i] -= reduce; //odjecie od pozostalych wartosci wartosci minimalnej w celu zredukowania kolumny
				}
			}
		}
	}

	branch.cost = reductionCost; //przypisanie kosztu redukcji

	return branch;
}

std::vector<std::vector<int>> BranchNBound::setInfinity(std::vector<std::vector<int>> matrix, int startingCity, int vertex) const
{
	//ustawienie nieskonczonosci (-1) w zadanym wierszu i kolumnie oraz na przejsciu z wierzcholka do wierzcholka poczatkowego
	for(int i=0;i<matrix.size(); i++)
	{
		matrix[startingCity][i] = -1;
		matrix[i][vertex] = -1;
	}
	//matrix[vertex][startingCity] = -1;
	matrix[vertex][this->startCity] = -1;

	return matrix;
}

int BranchNBound::calculateCost(std::vector<std::vector<int>> matrix, int startingCityCost, int reductionCost, int vertexA, int vertexB)
{
	const int finalCost = matrix[vertexA][vertexB] + startingCityCost + reductionCost; //obliczenie kosztu wierzcholka

	return finalCost;
}

bool BranchNBound::isVisited(std::vector<bool> visited)
{
	//sprawdzenie czy zosaly odwiedzone wszystkie wierzcholki
	for(int i=0; i < visited.size(); i++)
	{
		if(!visited[i])
		{
			return true;
		}
	}
	return false;
}

void BranchNBound::clearBuffor()
{
	this->minimalPathCost = 0;
	this->startCity = NULL;
	this->path.clear();
}

std::vector<int> BranchNBound::getPath() const
{
	return path;
}

int BranchNBound::getWeight() const
{
	return minimalPathCost;
}

bool BranchNBound::getCorrectPath() const
{
	return correctPath;
}

bool BranchNBound::checkVec(std::vector<int> vec)
{
	//srawdzenie czy w zadanym wektorze istnieja 0 lub -1, jesli tak to zredukowany
	int minus = 0;
	for(int i=0;i<vec.size(); i++)
	{
		if(vec[i] == 0) //jezeli w wierszu lub kolumnie jest conajmniej jedno 0 to zredukowane
		{
			return true;
		}
		if(vec[i] == -1)
		{
			minus++;
			if (minus == vec.size()) //jezeli w calym wierszu lub kolumnie sa -1 to zredukowane
			{
				return true;
			}
		}
	}
	return false;
}

int BranchNBound::getMinimum(std::vector<int> vec)
{
	int min = INT_MAX;
	for (int i : vec)
	{
		if(min> i && i > 0)
		{
			min = i;
		}
	}
	return min;		//zwroc minimalna wartosc z zadanego wektora
}

