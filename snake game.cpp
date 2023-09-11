#include<windows.h>
#include<conio.h>
#include<iostream>


using namespace std;

bool gameover;
const int width = 20;
const int height = 15;
int x, y, fruitx, fruity;
enum direc { STOP,LEFT,RIGHT,UP,DOWN };
direc dir;
int score;
int tailx[100];
int taily[100];
int ntail;
void ClearScreen() {



	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);



}
void setup() {
	ntail = 0;
	gameover = false;

	x = width / 2;
	y = height / 2;
	fruitx = (rand() % width);
	fruity = (rand() % height);
	score = 0;

}

void draw() {
	system("cls");

	for (int i = 0; i < width; i++) {
	std::cout<<"#";
	}
	cout << "\n";

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
		
			if (j == 0 || j == width - 1) {
				std::cout << "#";

			}
			else if (i == y && j == x) {
				std::cout << "O";
			
			}
			else if (i == fruity && j == fruitx) {
				std::cout << "F";
			}else{

				bool staus = false;

				for (int k = 0; k < ntail; k++) {
				
				
					if (tailx[k] == j && taily[k] == i) {
						cout << "o";
						staus = true;
					}
				}
				if (!staus) {
					std::cout << " ";
				}
			}

			
		
		}
		std::cout << "\n";
	}
	

	for (int i = 0; i < width; i++) {
		std::cout << "#";
	}


	cout << "\n";
	cout << "the current score is:" << score;
	cout << " x:" << x << "  y:" << y;









}
void input() {


	if (_kbhit()) {

		switch (_getch()) {

		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		}

	}
}

void logic() {

	for (int i = ntail; i > 0; i--) {
	
		tailx[i] = tailx[i - 1];
		taily[i] = taily[i - 1];
	}


	tailx[0] = x;
	taily[0] = y;



	switch (dir) {

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
	
	}



	if (fruitx == x && fruity == y) {

		score = score + 10;
		ntail++;
		fruitx = rand() % width;
		fruity = rand() % height;
	}

	if ((x<0 || x>width) || (y < 0 || y>height)) {
			gameover = true;
		}

     
	for (int i = 0; i < ntail; i++) {
	
	
		if (tailx[i] == x && taily[i] == y) {
		
			gameover = true;
		}
	
	}





	}

int main() {
	setup();
	while (!gameover) {
	
	
		draw();
		input();
		logic();
	
	
	}


	return 0;
}