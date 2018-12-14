#include "Menu.h"
#include <ctime>
#include "TimeMeasure.h"
#include <iostream>

using namespace std;

int main()
{
	srand(time(nullptr));

	Menu menu;

	menu.ChooseOptionMenu();

	system("pause");
	return 0;
}