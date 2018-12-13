#pragma once
#include <vector>

struct BnB	//struktura obslugujaca wszystkie wierzcholki - ich macierze, koszty, sciezke, odwiedzone wierzcholki
{
	std::vector<std::vector<int>> matrix;
	std::vector<int> path;
	int cost;
	int vertex;
	std::vector<bool> visited;
};

struct compareCost	//struktura pozwalajaca na wybranie najmniejszego kosztu wierzcholka (potrzebne w kolejce priorytetowej)
{
	bool operator()(const BnB& l, const BnB& r) const
	{
		return l.cost > r.cost;
	}
};

class BranchNBound
{
private:
	int minimalPathCost;	//minimalny koszt sciezki
	int startCity;	//miato z ktorego rozpoczynamy podroz
	std::vector<int> path;	//sciezka
	bool correctPath;	//zmienna sprawdzajaca czy udalo sie znalezc sciezke
public:
	BranchNBound();
	~BranchNBound();
	BranchNBound BranchNBoundTSP(const std::vector<std::vector<int>>& matrix, int startingCity); //funkcja g³ówna do TSP
	static BnB reduceFirstMatrix(std::vector<std::vector<int>> matrix, int startingCity, int size); //pierwsza redukcja zadanej macierzy
	static BnB reduceMatrix(BnB branch); //redukcja macierzy
	std::vector<std::vector<int>> setInfinity(std::vector<std::vector<int>> matrix, int startingCity, int vertex) const; //ustawienie nieskonczonosci (-1) w zadanym wierszu i kolumnie
	static bool checkVec(std::vector<int> vec); //sprawdzenie czy zadany wiersz/kolumna posiada 0 lub -1
	static int getMinimum(std::vector<int> vec); //zwraca minimalny element z zadanego wiersza/kolumny
	static int calculateCost(std::vector<std::vector<int>> matrix, int startingCityCost, int reductionCost, int vertexA, int vertexB); //wyliczenie kosztu wierzcholka
	static bool isVisited(std::vector<bool> visited); //sprawdzenie czy zostaly odwiedzone wszystkie wierzcholki
	void clearBuffor(); //czyszczenie sciezki, kosztu
	std::vector<int> getPath() const;
	int getWeight() const;
	bool getCorrectPath() const;
};
