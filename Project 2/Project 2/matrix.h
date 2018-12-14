#pragma once
#include <vector>
#include "Converter.h"

class Graph
{
private:
	Converter converter;
	int size;
	std::vector<std::vector<int>> matrix;
public:
	Graph();
	~Graph();
	void clearMatrix();
	void setMatrix(std::vector<std::vector<int>> matrix);
	std::vector<std::vector<int>> getMatrix() const;
	std::vector<std::vector<int>> generateMatrix(int size);
	static int randomNumber();
	int getSize() const;
	static void printMatrix(std::vector<std::vector<int>> matrix);
	void readFromFile(std::string filename);
};

