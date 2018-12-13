#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

double coolTemp, startingTemp, finalTemp;

Menu::Menu(): option(NULL)
{
}


Menu::~Menu()
= default;

void Menu::ChooseOptionMenu()
{
	system("cls");
	string temp;
	cout << "[1] Wczytaj dane z pliku" << endl;
	cout << "[2] Wyswietl wczytane dane" << endl;
	cout << "[3] Wprowadz kryterium stopu" << endl;
	cout << "[4] Wprowadz temperature chlodzenia, poczatkowa oraz minimalna" << endl;
	cout << "[5] Losuj macierz" << endl;
	cout << "[6] Wypisz wprowadzone dane" << endl;
	cout << "[0] Wyjscie" << endl;
	cout << "Wybierz zadanie do uruchomienia: ";
	cin >> temp;

	option = atoi(temp.c_str()); //konwersja ze stringa na int

	switch (option)
	{
	case 1:
		system("cls");
		cin.ignore();
		graph.clearMatrix();
		graph.readFromFile();
		system("pause");
		ChooseOptionMenu();
		break;
	case 2:
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
	case 3:
		system("cls");
		double stopTime;
		cout << "Wpisz kryterium stopu w sekundach: ";
		cin >> stopTime;
		algorithm.set_stop_time(stopTime);
		system("pause");
		ChooseOptionMenu();
		break;
	case 4:
		system("cls");
		cout << "Wpisz temperature chlodzenia: ";
		cin >> coolTemp;
		cout << "Wpisz temperature poczatkowa: ";
		cin >> startingTemp;
		cout << "Wpisz temperature minimalna: ";
		cin >> finalTemp;
		system("pause");
		ChooseOptionMenu();
		break;
	case 5:
		system("cls");
		graph.clearMatrix();
		graph.setMatrix(graph.generateMatrix(chooseSize()));
		Graph::printMatrix(graph.getMatrix());
		system("pause");
		ChooseOptionMenu();
		break;
	case 6:
		system("cls");
		SAalgorithm = SimulatedAnnealing(startingTemp, coolTemp, finalTemp, graph.getMatrix());
		if (startingTemp != SAalgorithm.getCurrentTemp())
		{
			SAalgorithm.set_current_temp(startingTemp);
		}
		if (SAalgorithm.getCurrentTemp() > 0 || SAalgorithm.getCoolingTemp() > 0 || SAalgorithm.getMinTemp() > 0){
			int solution;
			cout << "Wybierz opcje rozwiazywania algorytmu: " << endl;
			cout << "[1] Random Swap" << endl;
			cout << "[2] Random Insert" << endl;
			cout << "[3] Random Reverse" << endl;
			cin >> solution;
			result = SAalgorithm.find_solution(algorithm.stop_time(), solution);
			cout << result.cost << endl;
			printPath(result.path);
		}else
		{
			cout << "Wprowadz temperature chlodzenia, poczatkowa oraz minimalna w celu uruchomienia algorytmu" << endl;
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
	cout << "Z ktorego miasta rozpoczac podroz? Wierzcholki: " << 0 << " - " << graph.getSize()-1 << " ";
	cin >> source;
	while (true)
	{
		if (source >= 0 && source <= graph.getSize()-1)
		{
			break;
		}
		cout << "Podaj prawidlowy numer wierzcholka! Wierzcholki: " << 0 << " - " << graph.getSize()-1 << " ";
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
