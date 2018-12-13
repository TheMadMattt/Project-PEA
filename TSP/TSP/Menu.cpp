#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

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
	cout << "[3] Brute Force TSP" << endl;
	cout << "[4] Branch and Bound TSP" << endl;
	cout << "[5] Losuj macierz" << endl;
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
		Graph::printMatrix(graph.getMatrix());
		system("pause");
		ChooseOptionMenu();
		break;
	case 2:
		system("cls");
		if (graph.getSize() >= 2) {
			Graph::printMatrix(graph.getMatrix());
		}else
		{
			cout << "Graf nie zostal wczytany lub jest za maly" << endl;
		}
		system("pause");
		ChooseOptionMenu();
		break;
	case 3:
		system("cls");
		salesmanBF.clearBuffor();
		if (graph.getSize() >= 2) {
			salesmanBF = BruteForce::bruteForceTSP(graph.getMatrix(), chooseCity());
			printPath(salesmanBF.getPath());
			cout << "Koszt przejscia miedzy miastami: " << salesmanBF.getWeight() << endl;
		}else
		{
			cout << "Graf nie zostal wczytany lub jest za maly" << endl;
		}
		system("pause");
		ChooseOptionMenu();
		break;
	case 4:
		system("cls");
		salesmanBnB.clearBuffor();
		if (graph.getSize() >= 2) {
			salesmanBnB = salesmanBnB.BranchNBoundTSP(graph.getMatrix(), chooseCity());
			if (salesmanBnB.getCorrectPath()) {
				printPath(salesmanBnB.getPath());
				cout << "Koszt przejscia miedzy miastami: " << salesmanBnB.getWeight() << endl;
			}else
			{
				cout << "Nie znaleziono sciezki, algorytm znalazl najmniejsza wage rowna: " << salesmanBnB.getWeight() << endl;
				cout << "Znaleziono " << ((double)salesmanBnB.getPath().size() / graph.getMatrix().size())*100 << "% sciezki." << endl;
				printPath(salesmanBnB.getPath());
			}
		}
		else
		{
			cout << "Graf nie zostal wczytany lub jest za maly" << endl;
		}
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

