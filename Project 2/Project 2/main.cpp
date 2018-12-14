#include "Menu.h"
#include <ctime>
#include "TimeMeasure.h"
#include <iostream>

using namespace std;

int main()
{
	srand(time(nullptr));

	/*double coolTemp = 0.9999, finalTemp = 0.0001;
	int stopTime = 0, randOption = 1, startOption = 1;

	result results;
	Graph graph;
	SimulatedAnnealing sa;
	int size = 10;
	vector<result> vect;

	graph.readFromFile("ftv47.atsp");
	for(int i=0; i < size; i++)
	{
		sa = SimulatedAnnealing(coolTemp, finalTemp, graph.getMatrix(), stopTime, randOption, startOption);
		results = sa.find_solution(0, 1, 1);
		vect.push_back(results);
		cout << results.cost << endl;
	}
	TimeMeasure::saveToFile(vect, "ftv47time.txt");*/


	Menu menu;

	menu.ChooseOptionMenu();

	system("pause");
	return 0;
}