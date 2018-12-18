#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

double coolTemp = 0, finalTemp = 0;
int startOption = -1, stopTime = 0, randOption = -1;
std::string filename;
bool diverse = false;

Menu::Menu() : option(NULL)
{
}


Menu::~Menu()
= default;

void Menu::ChooseOptionMenu()
{
	system("cls");
	string temp;
	cout << "[1] Wczytaj dane z pliku" << endl;
	cout << "[2] Losuj macierz" << endl;
	cout << "[3] Wyswietl wczytane dane" << endl;
	cout << "[4] Wybierz kryterium stopu: " << stopTime << endl;
	cout << "[5] Wybierz temperature chlodzenia oraz minimalna: " <<
		coolTemp << ", " << finalTemp << endl;
	cout << "[6] Wybierz rozwiazywnaie algorytmu";
	if (randOption == -1)
	{
		cout << endl;
	}
	else if (randOption == 1)
	{
		cout << ": Random Swap" << endl;
	}
	else if (randOption == 2)
	{
		cout << ": Random Insert" << endl;
	}
	else if (randOption == 3)
	{
		cout << ": Random Reverse" << endl;
	}
	cout << "[7] Wybierz generowanie poczatkowego rozwiazania";
	if (startOption == -1)
	{
		cout << endl;
	}
	else if (startOption == 1)
	{
		cout << ": Greedy solution" << endl;
	}
	else if (startOption == 2)
	{
		cout << ": Random solution" << endl;
	}
	cout << "[8] Dywersyfikacja";
	if(diverse)
	{
		cout << " - ON" << endl;
	}else
	{
		cout << " - OFF" << endl;
	}
	cout << "[9] Simulated Annealing algorithm" << endl;
	cout << "[0] Wyjscie" << endl;
	cout << "Wybierz zadanie do uruchomienia: ";
	cin >> temp;

	option = atoi(temp.c_str()); //konwersja ze stringa na int

	switch (option)
	{
	case 1:

		system("cls");
		std::cout << "Podaj nazwe pliku z rozszerzeniem [.atsp]: ";
		cin.ignore();
		getline(std::cin, filename);
		graph.clearMatrix();
		graph.readFromFile(filename);
		system("pause");
		ChooseOptionMenu();
		break;
	case 2:
		system("cls");
		graph.clearMatrix();
		graph.setMatrix(graph.generateMatrix(chooseSize()));
		Graph::printMatrix(graph.getMatrix());
		system("pause");
		ChooseOptionMenu();
		break;
	case 3:
		system("cls");
		if (graph.getSize() >= 2) {
			Graph::printMatrix(graph.getMatrix());
		}
		else
		{
			cout << "Graf nie zostal wczytany lub jest za maly" << endl;
		}
		system("pause");
		ChooseOptionMenu();
		break;
	case 4:
		system("cls");
		cout << "Wpisz kryterium stopu w sekundach: ";
		cin >> stopTime;
		system("pause");
		ChooseOptionMenu();
		break;
	case 5:
		system("cls");
		cout << "Wpisz temperature chlodzenia: ";
		cin >> coolTemp;
		cout << "Wpisz temperature minimalna: ";
		cin >> finalTemp;
		system("pause");
		ChooseOptionMenu();
		break;
	case 6:
		system("cls");
		cout << "Wybierz rozwiazywanie algorytmu: " << endl;
		cout << "[1] Random Swap" << endl;
		cout << "[2] Random Insert" << endl;
		cout << "[3] Random Reverse" << endl;
		cin >> randOption;
		system("pause");
		ChooseOptionMenu();
		break;
	case 7:
		system("cls");
		cout << "Wybierz generowanie poczatkowego rozwiazania algorytmu: " << endl;
		cout << "[1] Greedy solution" << endl;
		cout << "[2] Random solution" << endl;
		cin >> startOption;
		system("pause");
		ChooseOptionMenu();
		break;
	case 8:
		system("cls");
		diverse = !diverse;
		ChooseOptionMenu();
		break;
	case 9:
		system("cls");
		simulatedAnnealing = SimulatedAnnealing(coolTemp, finalTemp, graph.getMatrix(), stopTime, randOption, startOption);
		if (simulatedAnnealing.getCurrentTemp() > 0 || simulatedAnnealing.getCoolingTemp() > 0 || simulatedAnnealing.getMinTemp() > 0) {
			if(stopTime == 0)
			{
				stopTime = 60;
				simulatedAnnealing.set_stop_time(stopTime);
			}
			result = simulatedAnnealing.find_solution(simulatedAnnealing.stop_time(), diverse);
			cout << "Czas znalezienia najnizszego kosztu sciezki: " << result.bestSolutionTime / 1000000 << " [s]" << endl;
			cout << "Temperatura w trakcie znalezienia najlepszego rozwiazania: " << result.finalTemp << endl;
			cout << "Koszt sciezki: " << result.cost << endl;
			printPath(result.path);
		}
		else
		{
			cout << "Wprowadz temperature chlodzenia oraz minimalna w celu uruchomienia algorytmu" << endl;
		}
		system("pause");
		ChooseOptionMenu();
		break;
	case 0:
		exit(0);
	default:
		cout << "Wpisz odpowiedni numer." << endl;
		system("pause");
		system("cls");
		ChooseOptionMenu();
	}
}

int Menu::chooseCity() const
{
	int source;
	cout << "Z ktorego miasta rozpoczac podroz? Wierzcholki: " << 0 << " - " << graph.getSize() - 1 << " ";
	cin >> source;
	while (true)
	{
		if (source >= 0 && source <= graph.getSize() - 1)
		{
			break;
		}
		cout << "Podaj prawidlowy numer wierzcholka! Wierzcholki: " << 0 << " - " << graph.getSize() - 1 << " ";
		cin >> source;
	}

	return source;
}

int Menu::chooseSize()
{
	int size;

	cout << "Jaki ma byc rozmiar macierzy?: ";
	cin >> size;
	while (true)
	{
		if (size >= 3)
		{
			break;
		}
		cout << "Podaj prawidlowy rozmiar macierzy! >= 3: ";
		cin >> size;
	}

	return size;
}

void Menu::printPath(std::vector<int> path)
{
	std::cout << "Droga miedzy miastami: ";
	for (int i = 0; i < path.size(); i++)
	{
		if (i != path.size() - 1) {
			std::cout << path[i] << " - ";
		}
		else
		{
			std::cout << path[i];
		}
	}

	std::cout << std::endl;
}

