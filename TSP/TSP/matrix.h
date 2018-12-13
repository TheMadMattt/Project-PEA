#pragma once
#include <vector>

class Graph
{
private:
	int size;
	std::vector<std::vector<int>> matrix;
public:
	Graph();
	~Graph();
	void clearMatrix();
	std::vector<std::vector<int>> createMatrix();
	void setMatrix(std::vector<std::vector<int>> matrix);
	std::vector<std::vector<int>> getMatrix() const;
	std::vector<std::vector<int>> generateMatrix(int size);
	static int randomNumber();
	int getSize() const;
	static void printMatrix(std::vector<std::vector<int>> matrix);
	void readFromFile();
};

