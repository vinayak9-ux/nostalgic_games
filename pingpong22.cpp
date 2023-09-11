#include<iostream>
#include<limits>
#include<conio.h>
#include<windows.h>
#include<time.h>
#undef max
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN




using namespace std;
enum direction { STOP = 0, LEFT = 1, UPPERLEFT = 2, BOTTOMLEFT = 3, RIGHT = 4, UPPERRIGHT = 5, BOTTOMRIGHT = 6 };


void ClearScreen()
{
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

class ball {

private:

    int x, y;
    int originalx, originaly;
    direction dir;

public:
    ball(int posx, int posy) {

        originalx = posx;
        originaly = posy;
        x = posx;
        y = posy;
        dir = STOP;
    }

    void reset() {
        x = originalx;
        y = originaly;
        dir = STOP;

    }

    inline int getx() { return x; }
    inline int gety() { return y; }
    inline direction getdirection() { return dir; }
    void chanceDirection(direction p) {
        dir = p;
    }
    void randomdirection() {

        dir = (direction)((rand() % 6) + 1);

    }

    void move() {


        switch (dir) {


            case LEFT:
                x--;
                break;
            case UPPERLEFT:
                y--;
                x--;
                break;
            case BOTTOMLEFT:
                y++;
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UPPERRIGHT:
                y--;
                x++;
                break;
            case BOTTOMRIGHT:
                x++;
                y++;
                break;

            case STOP:

                break;

        }

    }
};


class paddle {

private:
    int x, y;
    int originalx, originaly;
public:
    paddle(int posx, int posy) {
        originalx = posx;
        originaly = posy;
        x = posx;
        y = posy;

    }
    void reset() {
        x = originalx;
        y = originaly;

    }

    inline int getx() { return x; }
    inline int gety() { return y; }
    inline void MOVEUP() { y--; }
    inline void MOVEDOWN() { y++; }

};

class GameEngine {

private:
    ball* cball;
    paddle* player1;
    paddle* player2;
    int score1, score2;
    int height;
    int width;
    char UP1, UP2, DOWN1, DOWN2;
    bool game;

public:
    GameEngine(int w, int h) {
        srand(time(NULL));

        height = h;
        width = w;
        score1 = score2 = 0;
        UP1 = 'w';
        UP2 = 'i';
        DOWN1 = 's';
        DOWN2 = 'k';
        cball = new ball(width / 2, height / 2);
        player1 = new paddle(1, height / 2);
        player2 = new paddle(width - 3, (h / 2) - 1);
        game = false;


    }

    ~GameEngine() {
        delete cball, player1, player2;

    }

    void SCOREUP(paddle* p) {

        if (p == player1) {
            score1++;

        }
        else if (p == player2) {
            score2++;
        }

        cball->reset();
        player1->reset();
        player2->reset();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    void draw() {
        ClearScreen();

        cout << "{              VINAYAK PINddsdkG PONG GAME                 }" << "\n" << "\n" << "\n";
        for (int i = 0; i < width + 1; i++) {
            cout << "\xB2";;

        }
        cout << "\n";

        for (int i = 0; i < height; i++) {

            for (int j = 0; j < width; j++) {

                if (j == 0 || j == width - 1) {

                    cout << "\xB2";
                }
                if (cball->getx() == j && cball->gety() == i) {

                    cout << "O";

                }
                else if (player1->getx() == j && player1->gety() == i) {
                    cout << "\xDB";
                }
                else if (player1->getx() == j && player1->gety() + 1 == i) {
                    cout << "\xDB";
                }
                else if (player1->getx() == j && player1->gety() + 2 == i) {
                    cout << "\xDB";
                }
                else if (player1->getx() == j && player1->gety() + 3 == i) {
                    cout << "\xDB";
                }

                else if (player2->getx() == j && player2->gety() == i) {
                    cout << "\xDB";
                }
                else if (player2->getx() == j && player2->gety() + 1 == i) {
                    cout << "\xDB";
                }
                else if (player2->getx() == j && player2->gety() + 2 == i) {
                    cout << "\xDB";
                }
                else if (player2->getx() == j && player2->gety() + 3 == i) {
                    cout << "\xDB";
                }
                else {
                    cout << " ";
                }






            }
            cout << "\n";
        }

        for (int i = 0; i < width + 1; i++) {
            cout << "\xB2";

        }
        cout << "\n";


        cout << "CURRENT SCORE OF PLAYER 1: " << score1 << "    CURRENT SCORE OF PLAYER 2:  " << score2 << "\n";

    }

    void input() {

        cball->move();

        int ballx = cball->getx();
        int bally = cball->gety();
        int player1x = player1->getx();
        int player2x = player2->getx();
        int player1y = player1->gety();
        int player2y = player2->gety();

        if (_kbhit())
        {
            char current = _getch();
            if (current == UP1)
                if (player1y > 0)
                    player1->MOVEUP();
            if (current == UP2)
                if (player2y > 0)
                    player2->MOVEUP();
            if (current == DOWN1)
                if (player1y + 4 < height)
                    player1->MOVEDOWN();
            if (current == DOWN2)
                if (player2y + 4 < height)
                    player2->MOVEDOWN();

            if (cball->getdirection() == STOP)
                cball->randomdirection();

            if (current == 'q')
                game = true;
        }
    }


    void logic() {
        /*-----------------------------------------------------------------------------*/


        for (int i = 0; i < 4; i++) {

            if (cball->getx() == player1->getx() + 1) {

                if (cball->gety() == player1->gety()) {


                    cball->chanceDirection(UPPERRIGHT);
                }
                if (cball->gety() == player1->gety() + 1 || cball->gety() == player1->gety() + 2) {


                    cball->chanceDirection((direction)((rand() % 3) + 4));
                }
                if (cball->gety() == player1->gety() + 3) {


                    cball->chanceDirection(BOTTOMRIGHT);
                }
            }
        }


        for (int i = 0; i < 4; i++) {

            if (cball->getx() == player2->getx() - 1) {

                if (cball->gety() == player2->gety()) {


                    cball->chanceDirection(UPPERLEFT);
                }
                if (cball->gety() == player2->gety() + 1 || cball->gety() == player2->gety() + 2) {


                    cball->chanceDirection((direction)((rand() % 2) + 1));
                }
                if (cball->gety() == player2->gety() + 3) {


                    cball->chanceDirection(BOTTOMLEFT);
                }
            }
        }

















        /*
        for (int i = 0; i < 4; i++) {

            if (cball->getx() == player1->getx() + 1 && cball->gety() == player1->gety() + i) {

                cball->chanceDirection((direction)((rand() % 3) + 4));

            }


        }

        for (int i = 0; i < 4; i++) {

            if (cball->getx() == player2->getx() - 1 && cball->gety() == player2->gety() + i) {

                cball->chanceDirection((direction)((rand() % 2) + 1));

            }


        }
-----------------------------------------------------------------------------*/
        if (cball->gety() == height - 1) {

            if (cball->getdirection() == BOTTOMRIGHT) {
                cball->chanceDirection(UPPERRIGHT);
            }
            else if (cball->getdirection() == BOTTOMLEFT) {

                cball->chanceDirection(UPPERLEFT);
            }


        }
        if (cball->gety() == 0) {

            if (cball->getdirection() == UPPERRIGHT) {
                cball->chanceDirection(BOTTOMRIGHT);
            }
            else if (cball->getdirection() == UPPERLEFT) {

                cball->chanceDirection(BOTTOMLEFT);
            }


        }

        if (cball->getx() == 0) {

            SCOREUP(player2);
        }
        else if (cball->getx() == width - 1) {

            SCOREUP(player1);
        }


        if (score1 == 5 || score2 == 5) {

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
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    GameEngine c(40, 20);
    c.run();

    return 0;

}
