#include "Algorithm.h"


Algorithm::Algorithm(): stopTime(-1), chooseRandomOption(1), chooseStartingOption(1)
{
}

Algorithm::Algorithm(double stop_time, int choose_random_option, int choose_starting_option)
: stopTime(stop_time), chooseRandomOption(choose_random_option), chooseStartingOption(choose_starting_option)
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

int Algorithm::choose_random_option() const
{
	return chooseRandomOption;
}

void Algorithm::set_choose_random_option(int choose_random_option)
{
	chooseRandomOption = choose_random_option;
}

int Algorithm::choose_starting_option() const
{
	return chooseStartingOption;
}

void Algorithm::set_choose_starting_option(int choose_starting_option)
{
	chooseStartingOption = choose_starting_option;
}
