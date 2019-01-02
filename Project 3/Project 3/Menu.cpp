#include "Menu.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;

double mutationRatio = -1;
int stopTime = -1, mutationChoice = -1, populationSize = -1;
string filename;

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
	cout << "[4] Wybierz kryterium stopu: " << stopTime<< endl;
	cout << "[5] Wybierz rozwiazywnaie algorytmu";
	if (mutationChoice == -1)
	{
		cout << endl;
	}
	else if (mutationChoice == 1)
	{
		cout << ": Swap" << endl;
	}
	else if (mutationChoice == 2)
	{
		cout << ": Scramble" << endl;
	}
	cout << "[6] Ustaw wspolczynnik mutacji: " << mutationRatio << endl;
	cout << "[7] Ustaw wielkosc populacji: " << populationSize << endl;
	cout << "[8] Genetic mutation algorithm" << endl;
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
		cout << "[1] Swap" << endl;
		cout << "[2] Scramble" << endl;
		cout << "Wybierz sposob rozwiazywania algorytmu: " << endl;
		cin >> mutationChoice;
		system("pause");
		ChooseOptionMenu();
		break;
	case 6:
		system("cls");
		cout << "Wpisz wspolczynnik mutacji: ";
		cin >> mutationRatio;
		system("pause");
		ChooseOptionMenu();
		break;
	case 7:
		system("cls");
		cout << "Wpisz wielkosc populacji: ";
		cin >> populationSize;
		system("pause");
		ChooseOptionMenu();
		break;
	case 8:
		system("cls");
		genetic = Genetic(stopTime,mutationChoice, mutationRatio, populationSize, graph.getMatrix());
		if (genetic.getMutationRatio() > 0 && genetic.getPopulationSize() > 0) {
			if(stopTime <= 0)
			{
				stopTime = 60;
				genetic.set_stop_time(stopTime);
			}
			result = genetic.mutate(genetic.stop_time());
			cout << "Czas znalezienia najnizszego kosztu sciezki: " << result.bestSolutionTime / 1000000 << " [s]" << endl;
			cout << "Koszt sciezki: " << result.cost << endl;
			printPath(result.path);
		}
		else
		{
			cout << "Ustaw wspolczynnik mutacji oraz wielkosc populacji" << endl;
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

