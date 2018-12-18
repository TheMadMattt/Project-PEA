#include "Converter.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <utility>

//Konwerter dla plikow .atsp

//autor: Antoni Sterna

//www: http://staff.iiar.pwr.wroc.pl/antoni.sterna/pea/PEA_testy.htm

Converter::Converter() = default;


Converter::~Converter()
= default;

void Converter::error_exit(const std::string& msg)
{
	std::cout << msg << std::endl;
	system("PAUSE");
}

int Converter::header_get_size(std::ifstream& file) const
{
	int     header_lines = 0;
	int     size = 0;
	std::string  line;

	for (;;)
	{
		getline(file, line);
		if (file.fail() || line.empty())
			error_exit("File READ error - HEADER");

		if (line.find("DIMENSION") != std::string::npos)
		{
			std::istringstream in_ss(line);
			std::string tmp;
			in_ss >> tmp;
			in_ss >> size;
		}
		else
			if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos)
				if (size <= 0)
					error_exit("File READ error - SIZE");
				else
					return(size);

		if (++header_lines >= 7)
			error_exit("File READ error - HEADER");
	}
}

int Converter::value_digits(int val)
{
	int width = 0;

	if (val == 0)
		return(1);

	while (val)
	{
		val /= 10;
		width++;
	}

	return(width);
}

std::string Converter::convert(std::string FILE_IN)
{
	this->FILE_IN = FILE_IN;
	std::ifstream    file_in;
	std::ofstream    file_out;
	int         size;
	int         width;
	int         diagonal = 0;
	int         dist, dist_max;
	c_v_v_i     city_distance;
	std::string fileToOpen;

	file_in.open(FILE_IN);
	if (!file_in.is_open()) {
		error_exit("File OPEN error - FILE_IN");
	}
	else {

		size = header_get_size(file_in);

		city_distance.resize(size);
		for (int i = 0; i < size; i++)
			city_distance[i].resize(size);

		dist_max = 0;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				file_in >> dist;
				if (file_in.fail())
					error_exit("File READ error - DATA");

				if (i == j)
				{
					if (i == 0)
						diagonal = dist;
					else
						if (dist != diagonal)
							std::cout << "WARNING: Diagonal data inconsistent (" << i << "," << j << ")" << std::endl << std::endl;
					dist = 0;
				}

				city_distance[i][j] = dist;

				if (dist > dist_max)
					dist_max = dist;
			}

		file_in.close();

		fileToOpen = FILE_OUT + std::to_string(size) + ".txt";

		file_out.open(fileToOpen);
		if (!file_out.is_open())
			error_exit("File OPEN error - FILE_OUT");

		width = value_digits(dist_max);

		file_out << size << std::endl;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				if (j == 0)
					file_out << std::setw(width) << city_distance[i][j];
				else
					file_out << std::setw(width + 1) << city_distance[i][j];

			file_out << std::endl;
		}

		file_out.close();

		std::cout << "Size = " << size << std::endl;
		std::cout << "Conversion OK" << std::endl << std::endl;
		
	}
	return fileToOpen;
}
