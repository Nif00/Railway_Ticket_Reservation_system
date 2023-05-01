#include "utils.h"
#include <windows.h>
#include <conio.h>

void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


int main()
{
	int Set[] = { 7,7,7,7 };   //Default colors
	int counter = 3;
	char key;

	for (int i = 0;;)
	{
		gotoxy(10, 5);
		color(Set[0]);
		cout << "1. Campaign";

		gotoxy(10, 6);
		color(Set[1]);
		cout << "2. Train";

		gotoxy(10, 7);
		color(Set[2]);
		cout << "3. Ticket";

		gotoxy(10, 8);
		color(Set[3]);
		cout << "4. Passenger";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 4))   //72 = up arrow key
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 3))   //80 = down arrow key
		{
			counter++;
		}
		if (key == '\r')   //carriage return = enter key
		{
			if (counter == 1)
			{
				cout << " Campaign selection is open";
			}
			if (counter == 2)
			{
				cout << " Train selection is open";
			}
			if (counter == 3)
			{
				cout << " Ticket selection is open";
			}
			if (counter == 4)
			{
				cout << " Passenger selection is open";
			}
		}
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;

		if (counter == 1)
		{
			Set[0] = 12;
		}
		if (counter == 2)
		{
			Set[1] = 12;   //12 is red
		}
		if (counter == 3)
		{
			Set[2] = 12;
		}
		if (counter == 4)
		{
			Set[3] = 12;
		}
	}
	return 0;
}