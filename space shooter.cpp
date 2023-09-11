#include <iostream>
#include<time.h>
#include <conio.h>
#include<windows.h>
#include <algorithm>  
#include <vector>       
#include <functional>  

using namespace std;

template<class T>
class myfun {

public:
	T operator()(int i) {
	
		return i - 2;
	}
};

template<class T>
class myfun1 {

public:
	T operator()(int i) {

		return i + 2;
	}
};
void clearscreen() {

	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
class ball {

private:
	int x, y, originalx, originaly;

public:

	ball(int x, int y) {
		this->x = x;
		this->y = y;
		originalx = x;
		originaly = y;}
	void update(int j,int k) { x = j; y = k; }
	void reset() { x = originalx; y =originaly; }
	void moveup() { y--; }
	inline int getx() { return x; }
	inline int gety() { return y; }
	};

class paddle{

private:
	int x, y, originalx, originaly;
public:
	paddle(int x, int y) {
		this->x = x;
		this->y = y;
		originalx = x;
		originaly = y;
	}
	void reset() { x = originalx; y = originaly; }
	inline int getx() { return x; }
	inline int gety() { return y; }
	void moveleft() { x--; }
	void moveright() { x++; }
};

class gameengine {

private:
	int score,h,w;
	ball* cball;
	char left;
	char right;
	paddle* player;
	bool game;
	double a;
	std::vector<int>cordx,cordx1;
	std::vector<int>cordy,cordy1;
public:

	gameengine(int h,int w,vector<int>width,vector<int>height, vector<int>width1,vector<int>height1){
		cordx = width;
		cordy = height;
		cordx1 = width1;
		cordy1 = height1;

		this->h = h;
		this->w = w;
		left = 'a';
		right = 'd';
		a = 0;
		game = false;
		score = 0;
		player = new paddle(w / 2-2, h - 2);
		cball = new ball(player->getx()+2,player->gety()-1);

	}
	~gameengine() {delete cball, player;}

	void draw() {

		clearscreen();
	
		for (int  i = 0; i < w+1; i++)
		{
			cout << "-";
		}
		cout << " \n";

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++) {
			
			
				if (j == 0 || j == w - 1) { cout << "|"; }
			    if (cball->getx() == j && cball->gety() == i) { cout << "|"; }
				else if(player->getx() + 0 == j && player->gety() == i) { cout << "/"; } 
				else if(player->getx() + 1 == j && player->gety() == i) { cout << "-"; }
				else if(player->getx() + 2 == j && player->gety() == i) { cout << "|"; }
				else if(player->getx() + 3 == j && player->gety() == i) { cout << "-"; }
				else if (player->getx()+ 4 == j && player->gety() == i) { cout << "\\"; }
				
				else {
					bool f = true;

					for (int q = 0; q <6 ; q++)
					{
						if (cordx[q] == j && cordy[q] == i || cordx1[q]==j && cordy1[q]==i) { cout << "\xFE"; f = false; }
					
					}

					if (f) { cout << " "; }
				}

			}
			cout << "\n";
		}

		for (int i = 0; i < w+1; i++)
		{
			cout << "-";
		}
		cout << "\n" << "THE SCORE IS " << score;
}

	void input() {
	
		cball->moveup();

		if (_kbhit()) {
		
			char current = _getch();
		
			if (current == left) {
				if (player->getx() > 1) {
					player->moveleft();
				}
			}

			if (current == right) {
				if (player->getx() + 6 < w) {
					player->moveright(); }
			}

			if (current == 'q') { game = true; }
		
		
		
		}
		

	}

	void logic() {
	
	    if (cball->gety() == -1) {
			cball->update(player->getx()+2, player->gety()-1);
		}

		for (int i = 0; i < cordx.size(); i++)
		{
			if (cball->getx() == cordx[i] && cball->gety() == cordy[i]) {
				score++;
				
				cball->update(player->getx() + 2, player->gety()-1);
			    cordx[i] = 100;
				cordy[i] = 100;
			}
			if (cball->getx() == cordx1[i] && cball->gety() == cordy1[i]) {
				score++;

				cball->update(player->getx() + 2, player->gety() - 1);
				cordx1[i] = 100;
				cordy1[i] = 100;
			}
		}

		
		
		if (score > 11) {
			game = true;
		}
		
		for (int i = 0; i < cordy.size(); i++)
		{

			if (cordy[i] == h + 0 || cordy1[i] == h + 0) {
				for (int i = 0; i < cordx.size(); i++)
				{
					if (cordx[i] > 0 || cordx1[i] > 0) {
						game = true;
						break;
					}
				}
			}
		}

		
	}

	void update() {
		
		 a=a+0.0625;
		 
		 if ((abs(a - int(a)) == 0)) {
		 
			 for (int i = 0; i < cordy.size(); i++)
			 {

				 if (cball->getx() == cordx[i] && cball->gety() == cordy[i]) {
					 
					 score++;
					 cordx[i] = 100;
					 cball->update(player->getx() + 2, player->gety() - 1);
				 }
				 else if (cball->getx() == cordx1[i] && cball->gety() == cordy1[i]) {
					 score++;
					 cordx1[i] = 100;
					 cball->update(player->getx() + 2, player->gety() - 1);
				 
				 
				 }else {
					   cordy[i] = cordy[i] + 1;
					 cordy1[i] = cordy1[i] + 1;

				 }
			 }

		 
		 }
		
	}

	void run() {
	
		while (!game) {
			draw();
			input();
			update();
			logic();
			
			
		
		
		}
	
	
	}



};


int main() {
	vector<int>a1(6);
	vector<int>b1(6);
	vector<int>a{5,11,18,22,29,36};
	vector<int>b{1,5,3,6,4,1};

	transform(a.begin(), a.end(), a1.begin(), myfun<int>());
	transform(b.begin(), b.end(), b1.begin(), myfun1<int>());
	gameengine c(45, 40,a,b,a1,b1);
	c.run();
}
