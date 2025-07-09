#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include <vector>
#include <iostream>

using namespace std;

class Game {

public:
    Game(int = 80, int = 25);
    ~Game();
    void play();
    void printResult();

private:
	void generateTarget();
    void printBorder();
    bool eatTarget(Snake*);
    bool borderCollision(Snake*);
    bool selfCollision(Node*);
    bool bodyHeadCollision(Snake*, vector<Snake*>&);
    bool checkLength(Snake*);
    
    unsigned long long getMilliseconds();

    const int maxX;
    const int maxY;
    int targetX;
	int targetY;
    bool terminated;
    vector<Snake*> snakes;
    bool checkTarget();
};

#endif