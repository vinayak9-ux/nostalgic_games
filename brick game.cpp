#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include <limits>
#include<vector>
#undef max
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

void Clear() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearscreen() {

	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

using namespace std;
enum direction {STOP=0,UPPERLEFT=1,LOWERLEFT=2,UPERRIGHT=3,LOWERRIGHT=4,DOWN=9};
class ball {

private:
	int x, y, originalx, originaly;
	direction dir;

public:

	ball(int x, int y) {
		this->x = x;
		this->y = y;
		originalx = x;
		originaly = y;
		dir = STOP;
	}
	inline int getx() { return x;}
	inline int gety() { return y; }
	inline direction getdirection() { return dir; }
	void changedirection(direction p) { dir = p; }
	void randomdirection() { dir = (direction)((rand() % 4) + 1); }
	void reset() { x = originalx; y = originaly;
	dir = STOP;

	}
	void move() {
	
		switch (dir)
		{
		case STOP:
			break;
		case DOWN:
			y++;
			break;
		case UPPERLEFT:
			y--;
			x--;
			break;
		case LOWERLEFT:
			y++;
			x--;
			break;
		case UPERRIGHT:
			x++;
			y--;
			break;
		case LOWERRIGHT:
			x++;
			y++;
			break;
		}
	}

};
class player {

private:
	int x, y, originalx, originaly;
public:
	player(int x,int y) {
		this->x = x;
		this->y = y;
		originalx = x;
		originaly = y;
	}
	void reset() { x = originalx; y = originaly; }
	inline int getx() { return x; }
	inline int gety() { return y; }
	void moveleft() { x=x-2; }
	void moveright() { x=x+2; }
};
class block {
private:
	int x, y;

public:
	block(int x, int y) {
		this->x = x;
		this->y = y;

	}
	void reset() { x = y = -5; }
	inline int getx() { return x; }
	inline int gety() { return y; }

};
class gameengine{

	private:
		int h,w,score,live;
		player* player1;
		ball* cball;
		block* bl1,*bl2, * bl3, * bl4, * bl5, * bl6;
		char left, right;
		bool game;

public:
	gameengine(int h,int w) {
		srand(time(NULL));
		this->h = h;
		this-> w = w;
		player1 = new player((w / 2)-4, h - 3);
		cball = new ball(w / 2, h / 2);
		bl1 = new block(7, 3);
		bl2 = new block(20, 3);
		bl3 = new block(5, 5);
		bl4 = new block(31, 5);
		bl5 = new block(18, 5);
		bl6 = new block(30, 3);
		score = 0;
		left = 'a';
		right = 'd';
		live = 5;
		game = false;
}
	~gameengine() {
		delete cball, player1,bl1;
	}

	void draw() {
		clearscreen();
		for (int i = 0; i < w ; i++) { cout << "\xB2";}
		cout << "\n";
		

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++) {
			
			
				if (j == 0 || j == w - 1) { cout << "\xB2"; }
				else if (cball->getx() == j && cball->gety() == i) { cout << "o"; }
				else if (player1->getx() == j && player1->gety() == i) { cout << "\xDC"; }
				else if (player1->getx() + 1 == j && player1->gety() == i || player1->getx() + 2 == j && player1->gety() == i || player1->getx() + 3 == j && player1->gety() == i) { cout << "\xDC"; }
				else if (player1->getx() + 4 == j && player1->gety() == i || player1->getx() + 5 == j && player1->gety() == i || player1->getx() + 6 == j && player1->gety() == i) { cout << "\xDC"; }
				else if (player1->getx() + 7 == j && player1->gety() == i || player1->getx() + 8 == j && player1->gety() == i || player1->getx() + 9 == j && player1->gety() == i)  { cout << "\xDC"; }
				else if (bl1->getx() == j && bl1->gety() == i || bl1->getx() + 1 == j && bl1->gety() == i || bl1->getx()+2 == j && bl1->gety() == i || bl1->getx() + 3 == j && bl1->gety() == i) { cout << "\xDC"; }
				else if (bl2->getx() == j && bl2->gety() == i || bl2->getx() + 1 == j && bl2->gety() == i || bl2->getx()+2 == j && bl2->gety() == i || bl2->getx() + 3 == j && bl2->gety() == i) { cout << "\xDC"; }
				else if (bl3->getx() == j && bl3->gety() == i || bl3->getx() + 1 == j && bl3->gety() == i || bl3->getx()+2 == j && bl3->gety() == i || bl3->getx() + 3 == j && bl3->gety() == i) { cout << "\xDC"; }
				else if (bl4->getx() == j && bl4->gety() == i || bl4->getx() + 1 == j && bl4->gety() == i || bl4->getx()+2 == j && bl4->gety() == i || bl4->getx() + 3 == j && bl4->gety() == i) { cout << "\xDC"; }
				else if (bl5->getx() == j && bl5->gety() == i || bl5->getx() + 1 == j && bl5->gety() == i || bl5->getx()+2 == j && bl5->gety() == i || bl5->getx() + 3 == j && bl5->gety() == i) { cout << "\xDC"; }
				else if (bl6->getx() == j && bl6->gety() == i || bl6->getx() + 1 == j && bl6->gety() == i || bl6->getx()+2 == j && bl6->gety() == i || bl6->getx() + 3 == j && bl6->gety() == i) { cout << "\xDC"; }
				else { cout << " "; }
			
			}
			cout << "\n";
		}
	for (int i = 0; i < w; i++){ cout << "\xB2";}
	cout << "\n"<<"THE SCORE IS :"<<score<<"    "<<"THE REMAINING LIVES ARE :"<<live<<"\n";
	
	}

	void input() {
		cball->move();
		char current;
		if (_kbhit()) {
		
			current = _getch();
			if (current == 'a') {
				if (player1->getx() > 2) { player1->moveleft(); }
			}
			if (current == 'd') { 
				if (player1->getx()+12 < w) { player1->moveright(); }
			}
			if (current == 'q') { game = true; }
			if (cball->getdirection() == STOP) {
				cball->changedirection(DOWN);
			
			}
		}
	}

	void logic() {

		for (int i = 0; i < 10; i++)
		{
			if (cball->getx() == player1->getx()+i && cball->gety() == player1->gety()-1) {
			
				if (i == 0 || i == 1) {
				

					if (cball->getdirection() == LOWERRIGHT ||  cball->getdirection()==DOWN) { cball->changedirection(UPPERLEFT); }
					else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPPERLEFT); }
				}
				else if (i == 8 || i == 9) {
				
				if (cball->getdirection() == LOWERRIGHT || cball->getdirection() == DOWN) {cball->changedirection(UPERRIGHT);}
				else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPERRIGHT);}
				}
				else {

					if (cball->getdirection() == LOWERRIGHT || cball->getdirection() == DOWN) { cball->changedirection(UPERRIGHT); }
					else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPPERLEFT); }
				}

				
			}
		}

		for (int i = 0; i < 4; i++) {
		
			if (cball->getx() == bl1->getx() + i && cball->gety() == bl1->gety()) {
			
				if (cball->getdirection() == UPERRIGHT) { cball->changedirection(LOWERRIGHT); }
				else if (cball->getdirection() == UPPERLEFT) { cball->changedirection(LOWERLEFT); }
				else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPPERLEFT); }
				else if (cball->getdirection() == LOWERRIGHT) { cball->changedirection(UPERRIGHT); }
				bl1->reset();
				score++;
			}
			if (cball->getx() == bl2->getx() + i && cball->gety() == bl2->gety()) {

				if (cball->getdirection() == UPERRIGHT) { cball->changedirection(LOWERRIGHT); }
				else if (cball->getdirection() == UPPERLEFT) { cball->changedirection(LOWERLEFT); }
				else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPPERLEFT); }
				else if (cball->getdirection() == LOWERRIGHT) { cball->changedirection(UPERRIGHT); }
				bl2->reset();
				score++;
			}

			if (cball->getx() == bl3->getx() + i && cball->gety() == bl3->gety()) {

				if (cball->getdirection() == UPERRIGHT) { cball->changedirection(LOWERRIGHT); }
				else if (cball->getdirection() == UPPERLEFT) { cball->changedirection(LOWERLEFT); }
				else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPPERLEFT); }
				else if (cball->getdirection() == LOWERRIGHT) { cball->changedirection(UPERRIGHT); }
				bl3->reset();
				score++;
			}

			if (cball->getx() == bl4->getx() + i && cball->gety() == bl4->gety()) {

				if (cball->getdirection() == UPERRIGHT) { cball->changedirection(LOWERRIGHT); }
				else if (cball->getdirection() == UPPERLEFT) { cball->changedirection(LOWERLEFT); }
				else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPPERLEFT); }
				else if (cball->getdirection() == LOWERRIGHT) { cball->changedirection(UPERRIGHT); }
				bl4->reset();
				score++;
			}
			if (cball->getx() == bl5->getx() + i && cball->gety() == bl5->gety()) {

				if (cball->getdirection() == UPERRIGHT) { cball->changedirection(LOWERRIGHT); }
				else if (cball->getdirection() == UPPERLEFT) { cball->changedirection(LOWERLEFT); }
				else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPPERLEFT); }
				else if (cball->getdirection() == LOWERRIGHT) { cball->changedirection(UPERRIGHT); }
				bl5->reset();
				score++;
			}
			if (cball->getx() == bl6->getx() + i && cball->gety() == bl6->gety()) {

				if (cball->getdirection() == UPERRIGHT) { cball->changedirection(LOWERRIGHT); }
				else if (cball->getdirection() == UPPERLEFT) { cball->changedirection(LOWERLEFT); }
				else if (cball->getdirection() == LOWERLEFT) { cball->changedirection(UPPERLEFT); }
				else if (cball->getdirection() == LOWERRIGHT) { cball->changedirection(UPERRIGHT); }
				bl6->reset();
				score++;
			}
		}


		if (cball->gety() == 1) {
		
			if (cball->getdirection() == UPERRIGHT) { cball->changedirection(LOWERRIGHT); }
		    if(cball->getdirection() == UPPERLEFT) { cball->changedirection(LOWERLEFT); }
			}
        if (cball->getx() == 1) {
			if (cball->getdirection() == UPPERLEFT) { cball->changedirection(UPERRIGHT); }
			if (cball->getdirection() == LOWERLEFT) { cball->changedirection(LOWERRIGHT); }

		}
		if (cball->getx() == w - 2) {
			if (cball->getdirection() == UPERRIGHT) { cball->changedirection(UPPERLEFT); }
			if (cball->getdirection() == LOWERRIGHT) { cball->changedirection(LOWERLEFT); }

		}

		if (cball->gety() == h) {
			cball->reset();
			player1->reset();
			live--;
			Clear();
		}

		if (live == 0 || score == 6) {
		
			game = true;
		}
    }


	void run() {
	
		while (!game) {
			draw();
			input();
			logic();
		
	}


	}

};

int main() {

	gameengine c(30, 40);
	c.run();
}