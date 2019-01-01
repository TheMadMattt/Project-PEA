#include "Menu.h"
#include <ctime>

using namespace std;

int main()
{
	srand(time(nullptr));

	Menu menu;

	menu.ChooseOptionMenu();

	system("pause");
	return 0;
}