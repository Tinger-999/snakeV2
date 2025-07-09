#include "curses.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

int main() {
	srand(time(0));
	int c = 0;
	int maxX;
	int maxY;
	const char* FILE_NAME = "snake.txt";
	
	initscr();
	cbreak();				// Disable buffering, making input available to the program immediately
	noecho();				// Do not echo characters typed by the user
	timeout(0);
	keypad(stdscr, TRUE);	// Enable input from arrow keys
	curs_set(0); 			// Hide cursor
	getmaxyx(stdscr, maxY, maxX);	// Get max X and Y of the terminal

	Game game(maxX, maxY);
	game.play();
	game.printResult();

	endwin();				// Restores the terminal after Curses activity
}
