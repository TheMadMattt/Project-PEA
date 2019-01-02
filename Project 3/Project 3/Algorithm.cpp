#include "Algorithm.h"


Algorithm::Algorithm(): stopTime(-1), mutationChoice(-1)
{
}

Algorithm::Algorithm(int stop_time, int mutation_choice):stopTime(stop_time), mutationChoice(mutation_choice)
{
}


Algorithm::~Algorithm()
= default;

int Algorithm::stop_time() const
{
	return stopTime;
}

void Algorithm::set_stop_time(double stop_time)
{
	stopTime = stop_time;
}

int Algorithm::getMutationChoice() const
{
	return mutationChoice;
}

void Algorithm::set_mutation_choice(int mutation_choice)
{
	mutationChoice = mutation_choice;
}
