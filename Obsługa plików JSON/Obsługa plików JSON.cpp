#include <nlohmann/json.hpp>

#include<fstream>
#include <iostream>
//#include <json/json.h>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <time.h>

using json = nlohmann::json;

const char ESC = 27;
const char UP = 72;
const char DOWN = 80;
const char ENTER = 13;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void GoToXY(short x, short y) {
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void GoToX(short x) {
	SetConsoleCursorPosition(hStdOut, {x});
}
std::string _Menu[] = { "New Game", "High score", "Options", "Exit" };

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int Game(int score)
{
	srand(time(NULL));
	int x, y, num, count;
	x = 1 + rand() % 100;
	y = 1 + rand() % 100;
	count = 0;



	while (true)
	{
		std::cout << "Policz: "<<  x << " + " << y << " = ";
		std::cin >> num;
		if (x + y == num)
		{
			count += 1;
			x = 1 + rand() % 100;
			y = 1 + rand() % 100;
		}
		else
		{
			std::cout << "Score: " << count;
			score = count;
			count = 0;
			break;
		}
	}

	return score;
}

void sortJ(json objJson)
{

	std::string Name;
	int num;
	std::ofstream Out("Menu.json", std::ios::app);
	int len;
	json js;

	for (int i = 0; i < sizeof(objJson); i++)
	{
		for (int j = 0; j < i - 1; j++)
		{
			if (objJson[j]["Score"] > objJson[j + 1]["Score"])
			{

				Name = objJson[j]["Name"];
				num = objJson[j]["Score"];
				objJson[j] = objJson[j + 1];
				objJson[j + 1]["Name"] = Name;
				objJson[j + 1]["Score"] = num;
			}
		}
	}

	Out << std::setw(4) << objJson;

}
void print(int active_menu)
{

	nlohmann::json objJson;
	nlohmann::json newJson;
	std::ifstream High_score("Menu.json");
	std::ofstream Out("Menu.json", std::ios::app);
	std::ofstream ofs;
	High_score >> objJson;
	std::string Name;
	int num;
	int score = 0;
	int kk;
	system("CLS");
	GoToXY(40, 12);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	int y = 13;
	std::string New_Name;
	std::string Blind;
	json j;
	switch (active_menu)
	{
	case 0:
		std::cin >> New_Name;
		//std::cin >> score;
		score = Game(score);
		
		objJson[0]["Name"] = New_Name;
		objJson[0]["Score"] = score;
		ofs.open("Menu.json", std::ofstream::out | std::ofstream::trunc);

		Out << std::setw(4) << objJson;
		break;
	case 1:
		//sortJ(objJson);
		for (int i = 0; i < 5; i++)
		{
			Name = objJson[i]["Name"];
			num = objJson[i]["Score"];
			
			std::cout << Name << ": " << num << std::endl;
			GoToXY(40, y);
			y += 1;
		}
		break;
	case 2:
	default:
		break;
	}
	_getch();
	system("CLS");
	
}
void menu(int active_menu) {

	bool time = true;
	while (time)
	{
		int x = 40, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < 4; i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			std::cout << _Menu[i] << std::endl;
			if (i == 3)
				time = false;
		}

	}

}


int main() {
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	SetConsoleTitle(L"Json Pliki");
	char ch;
	while (true)
	{

		menu(active_menu);
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESC:
			exit(0);
		case UP:
			if (active_menu > 0)
				active_menu--;
			break;
		case DOWN:
			if (active_menu < 3)
				active_menu++;
			break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				print(active_menu);
				break;
			case 1:
				print(active_menu);
				break;
			case 2:
				print(active_menu);
				break;
			case 3:
				exit(0);
			}
		}
	}

	return 0;

}
