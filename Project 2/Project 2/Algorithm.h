#pragma once

class Algorithm
{
private:
	double stopTime;
	int chooseRandomOption;
	int chooseStartingOption;
public:
	Algorithm();

	Algorithm(double stop_time, int choose_random_option, int choose_starting_option);

	~Algorithm();

	double stop_time() const;
	void set_stop_time(double stop_time);

	int choose_random_option() const;
	void set_choose_random_option(int choose_random_option);
	int choose_starting_option() const;
	void set_choose_starting_option(int choose_starting_option);
};

