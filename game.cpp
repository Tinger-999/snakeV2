#include "curses.h"
#include "game.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

// Constructor for the Game class. 
Game::Game(int max_x, int max_y): maxX(max_x), maxY(max_y), terminated(false) {
    // 1. Initializes the game with the given maximum dimensions (max_x, max_y
    // 2. Creates two snakes, and sets the initial target position.
	// 3. Push the two snakes' pointers into the snakes vector.
    Snake* snake1 = new Snake((rand() % (maxX - 2) + 1) / 2, rand() % (maxY - 2) + 1), * snake2 = new Snake((rand() % (maxX - 2) + 1) / 2, rand() % (maxY - 2) + 1);
    snakes.push_back(snake1);
    snakes.push_back(snake2);
    printBorder();
}

// Destructor for the Game class.
Game::~Game() {
	// Delete the snakes. Otherwise, it's a memory leak.
    for (int i = 0; i < snakes.size(); i++) {
        delete snakes[i];
    }
}


void Game::generateTarget() {	
    // Generates a new target position randomly within the game boundaries.   
	// Show the target at the target position using mvaddch() function
	//mvaddch(targetY, targetX, ' ');
    targetX = rand() % (maxX - 5) + 2;
    targetY = rand() % (maxY - 5) + 2;
    while (!checkTarget()) {
        targetX = rand() % (maxX - 5) + 2;
        targetY = rand() % (maxY - 5) + 2;
    }
    mvaddch(targetY, targetX, '$');
}

bool Game::checkTarget() {
    for (int i = 0; i < snakes.size(); i++) {
        Node* body = snakes[i]->getHead();
        while (body->getPrevNode() != NULL) {
            if (body->getX() == targetX && body->getY() == targetY) {
                return false;
            }
            else
                body = body->getPrevNode();
        }
    }
    return true;
}

bool Game::eatTarget(Snake* snake) {
    return(snake->curX() == targetX && snake->curY() == targetY);
}


void Game::printBorder() {
    for (int i = 0; i < maxX; i++) {
        mvaddch(0, i, '.');
        mvaddch(maxY - 1, i, '.');
    }
    for (int i = 0; i < maxY; i++) {
        mvaddch(i, 0, '.');
        mvaddch(i, maxX - 1, '.');
    }

}
bool Game::borderCollision(Snake* snake) {
    return(snake->curX() == 0 || snake->curY() == 0 || snake->curX() == maxX - 1 || snake->curY() == maxY - 1);
}

bool Game::selfCollision(Node* head) {
    Node* body = head->getPrevNode();
    while (body != NULL && body->getPrevNode() != NULL) {
        if (head->getX() == body->getX() && head->getY() == body->getY()) {
            return true;
            break;
        }
        else
            body = body->getPrevNode();
        
    }
    return false;

}

bool Game::bodyHeadCollision(Snake* snake, vector<Snake*> &otherSnakes) {
    for (int i = 0; i < otherSnakes.size(); i++) {
        if (otherSnakes.at(i) != snake) {
            Node* body = otherSnakes[i]->getHead();
            while (body->getPrevNode() != NULL) {
                if (body->getX() == snake->curX() && body->getY() == snake->curY()) {
                    return true;
                }
                else
                    body = body->getPrevNode();
            }
        }
    }
    return false;
}

bool Game::checkLength(Snake* snake) {
    return(snake->getLength() == 1);
}


// Returns the current time in milliseconds since the system started.
// Uses the Windows-specific GetTickCount64 function.
unsigned long long Game::getMilliseconds() {
    return GetTickCount64();
}

// Main game loop. Handles user input, updates the game state, and checks for collisions.
// The game continues until the user exits or a snake hits a wall.
void Game::play() {

	generateTarget(); // Generate the first target
    unsigned long long start = getMilliseconds();
    unsigned long long now = start;
    bool hitTarget;
	
    // Game loop
	while (!terminated) {
		int c = getch();

		// Set the direction of the snakes based on user input
		switch (c) {
		case KEY_UP:
			snakes[1]->setDir(UP);
			break;
		case KEY_DOWN:
			snakes[1]->setDir(DOWN);
			break;
		case KEY_LEFT:
			snakes[1]->setDir(LEFT);
			break;
		case KEY_RIGHT:
			snakes[1]->setDir(RIGHT);
			break;
        case 'w':
            snakes[0]->setDir(UP);
            break;
        case 's':
            snakes[0]->setDir(DOWN);
            break;
        case 'a':
            snakes[0]->setDir(LEFT);
            break;
        case 'd':
            snakes[0]->setDir(RIGHT);
            break;
		}
		
		// Exit the game if 'q' or 'Q' is pressed
		if (c == 'q' || c == 'Q' || c == 27) {
			break;
		}

		// Continue the loop if its less than 200ms since the last update
        now = getMilliseconds();
        if (now - start < 200) {
            Sleep(10);
            continue;
        }

        start = now;

        // Check if any snake hits the target
        for (int i = 0; i < 2; i++) {
            Snake* snake = snakes.at(i);
            

            // 1. Check if any snake hits the target
            hitTarget = eatTarget(snake);
			// If game timer times out, move the snake and let it grow if it hits the target
            snake->move(hitTarget);

            // 2. Generate a new target if it's gone
            if (hitTarget) {
                //mvaddch(targetY, targetX, ' ');
                snakes.at(i)->setLength(snakes.at(i)->getLength() - 1);
                generateTarget();
            }

            // 3. Check if a snake hits the wall or the body of the other snake. If so, end the game
            if (borderCollision(snake) || selfCollision(snake->getHead()) || bodyHeadCollision(snake, snakes)) {
                terminated = true;
                snakes.at(i)->setStatus(LOSE);
            }
            if (checkLength(snake)) {
                terminated = true;
                snakes.at(i)->setStatus(WIN);
            }
        }
	}
}

void Game::printResult() {
    if (snakes.at(0)->getStatus() == LOSE || snakes.at(1)->getStatus() == WIN)
        cout << "direction keys prevail." << endl;
    else
        cout << "wsad keys prevail." << endl;
}