#pragma once

class Algorithm
{
private:
	double stopTime; //kryterium stopu
	int mutationChoice;
public:
	Algorithm();

	Algorithm(double stop_time, int mutation_choice);

	~Algorithm();

	double stop_time() const;
	void set_stop_time(double stop_time);
};

