#include "Algorithm.h"


Algorithm::Algorithm(): stopTime(-1)
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
