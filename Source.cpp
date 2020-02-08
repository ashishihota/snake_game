#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>

using namespace std;

bool game_over;
const int heigth = 20;
const int weidth = 20;

int x, y, fx, fy, score,ntail;
int tailx[100], taily[100];

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void setup() {
	srand(time(0));
	game_over = false;
	dir = STOP;
	ntail = 0;
	x = weidth / 2;
	y = heigth / 2;
	fx = rand() % weidth;
	fy = rand() % heigth;
	score = 0;
}
void draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < weidth + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < heigth; i++)
	{
		for (int j = 0; j < weidth; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fy && j == fx)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == weidth - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < weidth + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}
void input() {
	if (_kbhit()) {
		switch (_getch()){
		case 'j' :
			dir = LEFT;
			break;
		case 'k' :
			dir = DOWN;
			break;
		case 'l' :
			dir = RIGHT;
			break;
		case 'i' :
			dir = UP;
			break;
		case 'x' : 
			game_over = true;
		default:
				break;
		}
	}
}

void logic() {
	int prevX = tailx[0];
	int prevY = taily[0];
	int prev2X, prev2Y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < ntail; i++)
	{
		prev2X = tailx[i];
		prev2Y = taily[i];
		tailx[i] = prevX;
		taily[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	for (int i = 0; i < ntail; i++) {
		if (tailx[i] == i && taily[i] == i) game_over = true;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x < 0 || x > weidth - 1 || y < 0 || y > heigth - 1) {
		game_over = true;
	}

	if (x == fx && y == fy) {
		score += 10;
		fx = rand() % weidth;
		fy = rand() % heigth;
		ntail++;
		ntail++;
	}
}

int main() {
	setup();
	while (!game_over) {
		draw();
		input();
		logic();
		Sleep(200);
	}
	return 0;
}