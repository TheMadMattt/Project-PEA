#pragma once
#include <vector>
#include "SimulatedAnnealing.h"

class TimeMeasure
{
private: 
	double PCFreq;
	__int64 CounterStart;
public:
	TimeMeasure();
	~TimeMeasure();
	double getCounter() const;
	void startCounting();
	static void saveToFile(std::vector<result> &czasy, std::string path, int whichIt);
};

