#pragma once

class Algorithm
{
private:
	int stopTime; //kryterium stopu
	int mutationChoice;
public:
	Algorithm();

	Algorithm(double stop_time, int mutation_choice);

	~Algorithm();

	int stop_time() const;
	void set_stop_time(double stop_time);

	int getMutationChoice() const;
	void set_mutation_choice(int mutation_choice);
};

