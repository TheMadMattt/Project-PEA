#pragma once

class Algorithm
{
private:
	double stopTime;
public:
	Algorithm();
	~Algorithm();

	double stop_time() const;
	void set_stop_time(double stop_time);
};

