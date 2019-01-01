#include "Algorithm.h"


Algorithm::Algorithm(): stopTime(-1), mutationChoice(-1)
{
}

Algorithm::Algorithm(double stop_time, int mutation_choice):stopTime(stop_time), mutationChoice(mutation_choice)
{
}

Algorithm::~Algorithm()
= default;

double Algorithm::stop_time() const
{
	return stopTime;
}

void Algorithm::set_stop_time(double stop_time)
{
	stopTime = stop_time;
}