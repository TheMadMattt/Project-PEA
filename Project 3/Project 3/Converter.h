#pragma once
#include <string>
#include <vector>

typedef std::vector<int>     c_v_i;              // vector of int
typedef std::vector<c_v_i>   c_v_v_i;

class Converter
{
private:
	std::string FILE_IN;
	std::string FILE_OUT = "tsp_";
public:
	Converter();
	~Converter();
	static void error_exit(const std::string &msg);
	int header_get_size(std::ifstream &file) const;
	static int value_digits(int val);
	std::string convert(std::string FILE_IN);
};

