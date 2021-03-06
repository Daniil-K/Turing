#include "stdafx.h"
#include <vector>
#include <conio.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

vector <char> alp; // алфавит
vector <char> tape; // лента
vector <string> sost;// строка состояний 
vector < vector <string> > tabl; // таблица
int kol; // количество состояний

void fill_alp()
{
	char el_alp;
	cout << "Введите алфавит: ";
	while (1)
	{
		cin >> el_alp;
		if (el_alp == '.')
			break;
		alp.push_back(el_alp);
	}
	cout << "Алфавит: ";
	for (int i = 0; i < alp.size(); i++)
		cout << alp[i] << ' ';
	cout << endl;
	cout << endl;
}

void fill_tape()
{
	int q = 0; // счётчик неправильных элементов
	char el_tape = ' ';
	cout << "Введите ленту: ";
	while (1)
	{
		cin >> el_tape;
		if (el_tape == '.')
			break;
		tape.push_back(el_tape);
	}
	cout << "Лента: ";
	for (int i = 0; i < tape.size(); i++)
	{
		cout << tape[i] << ' ';
	}
	cout << endl;
	cout << endl;
}

void proverka()
{	int shet = 0;
	for (int i = 0; i < tape.size(); i++)
	{
		int rew = 0;
		for (int j = 0; j < alp.size(); j++)
		{
			if (tape[i] == alp[j])
				rew++;
		}
		if (rew == 0)
			{
				tape.erase(tape.begin() + i);
				shet++;
				i--;
			}
	}
	cout << "Вы ввели " << shet << " неправильных элементов." << endl;
	cout << "Лента после проверки: ";
	for (int i = 0; i < tape.size(); i++)
	{
		cout << tape[i] << ' ';
	}
	cout << endl;
}

void fill_states()
{
	string state;
	cout << "Введите количество состояний: ";
	cin >> kol;

	for (int i = 0; i < kol; i++)
	{
		cout << "Введите " << i + 1 << " состояние(для каждого элемента): ";
		vector <string> sta; // временный вектор для вводимого состояния
		for (int x = 0; x < alp.size(); x++)
		{
			cin >> setw(3) >> state;
			if (state == ".")
				state = "   ";
			sta.push_back(state);
			sost.push_back(state);
		}

		tabl.push_back(sta);
	}

	cout << '\t' << '\t' << '\t' << '\t' << "Таблица состояний" << endl;
	cout << " " << " |";

	for (int i = 0; i < alp.size(); i++)
	{
		cout << "  " << alp[i] << "  |";
	}

	for (int i = 0; i < kol; i++)
	{
		cout << endl;
		cout << i + 1 << " | ";
		for (int x = 0; x < alp.size(); x++)
		{
			cout << tabl[i][x] << " | ";
		}
	}
	cout << endl;
}

void parseString(string com, char &newSym, int &dir, int &newSt)  // Считывание состояния и изменение
{
	newSym = com[0];

	if (com[1] == 'l')
		dir = dir - 1;
	if (com[1] == 'n')
		dir = dir;
	if (com[1] == 'r')
		dir = dir + 1;

	newSt = com[2];
	newSt = newSt - 48;
}

void machine()
{
	string command;
	int curPos; // текущая позиция в ленте
	int curState; // текущее состояние
	cout << "Введите номер элемента, который будет начальным: ";
	cin >> curPos;
	cout << "Введите номер состояния, которое будет начальным: ";
	cin >> curState;
	char symbol;
	int nom;
	while(true)
	{
		symbol = tape[curPos];
		for (int i = 0; i < alp.size(); i++)
		{
			if (symbol == alp[i])
			{
				nom = i;
				break;
			}	
		}
		for (int k = 0; k < kol; k++)
		{
			for (int x = 0; x < alp.size(); x++)
			{
				command = tabl[curState - 1][nom];
			}
		}

		nom = curPos;
		cout << "Command: " << command << endl;
		parseString(command, symbol, nom, curState);
		tape[curPos] = symbol;
		curPos = nom;
		if (curPos > tape.size())
			break;
		if (curState == 0)
			break;
	}
	cout << "Лента после преобразований: ";
	for (int v = 0; v < tape.size(); v++)
	{
		cout << tape[v] << ' ';
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << '\t' << '\t' << '\t' << "Машина Тьюринга" << endl;;
	fill_alp();
	fill_tape();
	proverka();
	fill_states();
	machine();
	return 0;
}