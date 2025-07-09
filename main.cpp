// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "curses.h"

using namespace std;

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct SingleNodeSnake {
    int x;
    int y;
    Direction dir;
    SingleNodeSnake* next;
};



void insertAtHead(SingleNodeSnake*& snake) { //讓蛇移動，一次只需插入一個節點，並刪除尾巴節點
    SingleNodeSnake* nextHead = new SingleNodeSnake;
    switch (snake->dir) {
    case UP:
        nextHead->x = snake->x;
        nextHead->y = snake->y - 1;
        break;
    case DOWN:
        nextHead->x = snake->x;
        nextHead->y = snake->y + 1;
        break;
    case LEFT:
        nextHead->x = snake->x - 1;
        nextHead->y = snake->y;
        break;
    case RIGHT:
        nextHead->x = snake->x + 1;
        nextHead->y = snake->y;
    }
    nextHead->next = snake;
    nextHead->dir = snake->dir;
    snake = nextHead;
    mvaddch(snake->y, snake->x, '*');
}

void removeAtTail(SingleNodeSnake*& snake) {
    SingleNodeSnake* tail = snake;
    while (tail->next->next != NULL) {
        tail = tail->next;
    }
    mvaddch(tail->next->y, tail->next->x, ' ');
    delete tail->next;
    tail->next = NULL;
}
void move(SingleNodeSnake*& snake) {
    // Clear '*' at the previous position

        // Update snake's position
    /*SingleNodeSnake* body = snake;
    while (body != NULL) {
        mvaddch(body->y, body->x, ' ');
        body = body->next;
    }*/
    insertAtHead(snake);
    removeAtTail(snake); //先將舊的位置刪除，再更新並畫上新的位置
    //switch (body->dir) {
    /*case UP:
        body->y--;
        break;
    case DOWN:
        body->y++;
        break;
    case LEFT:
        body->x--;
        break;
    case RIGHT:
        body->x++;
        break;
    }*/

    // Draw '*' at the new position
    /*body = snake;
    while (body != NULL) {
        mvaddch(body->y, body->x, '*');
        body = body->next; //moving from head to tail
    }*/
}
void printMedicine(SingleNodeSnake& medicine, SingleNodeSnake* checkMedicine, int a, int b) {
    medicine.x = rand() % (a - 5) + 2;
    medicine.y = rand() % (b - 5) + 2;
    SingleNodeSnake* head = checkMedicine;//將現在頭的位置暫存
    while (checkMedicine != NULL) { // 確認藥物不會出現在蛇身
        if (medicine.x == checkMedicine->x && medicine.y == checkMedicine->y) {
            medicine.x = rand() % (a - 5) + 2;
            medicine.y = rand() % (b - 5) + 2;
            checkMedicine = head;
        }
        else
            checkMedicine = checkMedicine->next;
    }
    mvaddch(medicine.y, medicine.x, '$');

}

bool bodyCheck(SingleNodeSnake* head) { //不改變原本的頭，所以只用single pointer
    SingleNodeSnake* body = head->next;
    while (body != NULL) {
        if (head->x == body->x && head->y == body->y) {
            return false;
            break;
        }
        else
            body = body->next;


    }
    return true;

}
void deleteLinkedList(SingleNodeSnake*& head) {
    while (head != NULL) {
        SingleNodeSnake* temp = head;
        head = head->next;
        delete temp;
    }

}
void printBorder(int x, int y) {
	for (int i = 0; i < x; i++) {
		mvaddch(0, i, '.');
		mvaddch(y-1, i, '.');
	}
	for (int i = 0; i < y; i++) {
		mvaddch(i, 0, '.');
		mvaddch(i, x-1, '.');
	}
}

int main() {
    srand(time(0));
    int c, maxX, maxY, length = 1;
	int interval = 1000; //ms
    bool terminated = false;
    SingleNodeSnake* snake = new SingleNodeSnake;
    SingleNodeSnake* snakeTail = new SingleNodeSnake;
    SingleNodeSnake medicine;
    snake->next = NULL;

    // Set the initial position and moving direction


    initscr();
    cbreak();						// Disable buffering, making input available to the program immediately
    timeout(interval);					// Wait user's input for at most 1s
    keypad(stdscr, TRUE);			// Enable input from arrow keys
    curs_set(0); 					// Hide cursor
    getmaxyx(stdscr, maxY, maxX);	// Get max X and Y of the terminal
    printw("%d %d", maxX, maxY);

    snake->x = (rand() % maxX + 1) / 2 + 1;//v
    snake->y = rand() % (maxY - 3) + 2;//v
    medicine.x = rand() % (maxX - 5) + 2;//v
    medicine.y = rand() % (maxY - 5) + 2;//v
    snake->dir = RIGHT;//v
    mvaddch(snake->y, snake->x, '*');
    while (length < 20) {
        insertAtHead(snake);
        length++;
    }
    // Draw the single headed snake
    printBorder(maxX, maxY);
    printMedicine(medicine, snake, maxX, maxY); //畫減肥藥


    while (!terminated) {
        c = getch();

        switch (c) {
        case KEY_UP:
            snake->dir = UP;
            break;
        case KEY_DOWN:
            snake->dir = DOWN;
            break;
        case KEY_LEFT:
            snake->dir = LEFT;
            break;
        case KEY_RIGHT:
            snake->dir = RIGHT;
            break;
        case 27: // ESC
        case 'q':
            terminated = true;
            deleteLinkedList(snake);
            cout << "You quit lol" << endl;
            break;
        default:
            break;
        }
        move(snake);
        /*body = snake;
        while (body != NULL) {
            mvaddch(body->y, body->x, '*');
            body = body->next;
        }*/
        if (snake->x == medicine.x && snake->y == medicine.y) {
            removeAtTail(snake);
            length--;
			interval /= 2; //每吃一顆藥速度就加倍
			timeout(interval); //更新timeout才能改變速度
            printMedicine(medicine, snake, maxX, maxY);
        }
        if (length == 1) {
            terminated = true;
            deleteLinkedList(snake);
            cout << "You win!" << endl;
        }
        else if (!bodyCheck(snake)) {
            terminated = true;
            deleteLinkedList(snake);
            cout << "You Lose!" << endl;
        }
        else if (snake->x == maxX - 1 || snake->x == 1 || snake->y == maxY - 1 || snake->y == 1) {
            terminated = true;
            deleteLinkedList(snake);
            cout << "You lose!" << endl;
        }
    }
    endwin();	// Restores the terminal after Curses activity
    return 0;
}
