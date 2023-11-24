#include <iostream>
#include <ncurses.h>
#include <time.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x,y, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int tailX[width*height], tailY[width*height];
int nTail = 0;

void Setup() {
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;
	fruitX = rand()%width+1;
	fruitY = rand()%height+1;
}

void Draw() {
    clear();
    for (int i=0; i<width+2; i++)
        mvprintw(0,i,"#");
	for (int i=0; i<height+2; i++) {
		for (int j=0; j<width+2; j++) {
			if (i==0 || i==height+1)
				mvprintw(i,j,"+");
			else if (j==0 || j==width+1)
				mvprintw(i,j,"|");
			else if (i==y && j==x)
				mvprintw(i,j,"O");
			else if (i==fruitY && j == fruitX)
				mvprintw(i,j,"@");
            else {
                for (int k=0; k<nTail; k++) {
                    if (tailX[k]==j && tailY[k]==i)
                        mvprintw(i,j,"O");
                }
            }

		}
	}
	mvprintw(height+3,0,"Score: %d",nTail);

	refresh();
    getch();
    endwin();
}

void Input() {
	keypad(stdscr, TRUE);
	halfdelay(1);
	int c = getch();
	switch(c) {
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
		case 113:
			gameOver = true;
			break;
	}
}

void Logic() {
    for (int i=nTail-1; i>0; i--) {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    tailX[0]=x;
    tailY[0]=y;
	switch(dir) {
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
    if (x < 1)
        x = width;
    if (x > width+1)
        x = 0;
    if (y < 1)
        y = height;
    if (y > height+1)
        y = 0;
	if (x==fruitX && y==fruitY) {
		fruitX = rand()%width+1;
		fruitY = rand()%height+1;
        if (nTail<width*height)
            nTail++;
	}
    for (int i=0; i<nTail; i++) {
        if (tailX[i]==x && tailX[i]==y)
            gameOver = true;
    }
}

int main() {
    srand(time(0));
	Setup();
	while (!gameOver) {
		Draw();
        Input();
		Logic();
	}
	return 0;
}

