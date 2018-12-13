#include "matrix.h"
#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <set>


Graph::Graph(): size(0)
{
}


Graph::~Graph()
{
	matrix.clear();
}

void Graph::clearMatrix()
{
	matrix.clear();
}

void Graph::setMatrix(std::vector<std::vector<int>> matrix)
{
	this->matrix = matrix;
}

void Graph::printMatrix(std::vector<std::vector<int>> matrix)
{
	std::cout << "Ilosc miast: " << matrix.size() << std::endl;
	std::cout << std::setw(12);
	for (int i = 0; i < matrix.size(); i++)
	{
		std::cout << i+1 << std::setw(5);
	}
	std::cout << std::endl;

	for(int i=0; i<2*matrix.size(); i++)
	{
		std::cout << "---";
	}
	std::cout << std::endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		std::cout << std::setw(4) <<  i + 1 << " | ";
		std::cout << std::setw(5);
		for (int y = 0; y < matrix.size(); y++)
		{
			if (y < matrix.size() - 1) {
				std::cout << matrix[i][y] << std::setw(5);
			}else
			{
				std::cout << std::setw(5) << matrix[i][y];
			}
		}
		
		if(i == matrix.size() -1)
		{
			std::cout << std::endl;
		}else
		{
			std::cout << std::endl << std::endl;
		}
	}
	std::cout << std::setw(5);

	for (int i = 0; i < 2 * matrix.size(); i++)
	{
		std::cout << "---";
	}
	std::cout << std::endl;
}

void Graph::readFromFile()
{
	std::ifstream file;
	std::cout << "Podaj nazwe pliku z rozszerzeniem [.atsp]: ";
	std::string filename;
	int value;
	getline(std::cin, filename);

	filename = converter.convert(filename);

	file.open(filename, std::ios::in);

	if (file.good()) {

		file >> size;
		if(file.fail())
		{
			std::cout << "Blad wczytywania rozmiaru" << std::endl;
		}
		else {
			matrix.resize(size, std::vector<int>(size));
			int it = 0;
			while (!file.eof())
			{
				for (int y = 0; y < size; y++) {
					file >> value;
					if(file.fail())
					{
						std::cout << "Blad wczytywania danych" << std::endl;
						break;
					}
					else {
						matrix[it][y] = value;
					}
				}
				it++;
			}

			std::cout << "Dane zostaly wczytane prawidlowo " << std::endl << std::endl;

		}
	}else
	{
		std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
	}

	file.close();
}

int Graph::getSize() const
{
	return size;
}

std::vector<std::vector<int>> Graph::getMatrix() const
{
	return matrix;
}

std::vector<std::vector<int>> Graph::generateMatrix(int size)
{
	std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
	this->size = size;

	for(int i=0;i<size; i++)
	{
		for(int y=0;y<size;y++)
		{
			if(i==y)
			{
				matrix[i][y] = 0;
			}
			else {
				matrix[i][y] = randomNumber();
			}
		}
	}

	return matrix;
}

int Graph::randomNumber()
{
	return rand() % 100;
}
