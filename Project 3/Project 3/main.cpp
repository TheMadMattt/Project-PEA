#include "Menu.h"
#include <ctime>
#include <iostream>
#include "TimeMeasure.h"

using namespace std;

int main()
{
	srand(time(nullptr));

	Menu menu;

	menu.ChooseOptionMenu();

	system("pause");
	return 0;
}