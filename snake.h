#ifndef SNAKE_H
#define SNAKE_H

#include "node.h"

enum Direction{
		UP,DOWN,LEFT,RIGHT
};
enum Status {
	WIN, LOSE, FINE
};

class Snake {
public:
	Snake(int = 1, int = 1, Direction = RIGHT);
	~Snake();

	void setDir(Direction new_dir);
	Direction getDir();
	void setStatus(Status new_status);
	Status getStatus();
	void setLength(int);
	int getLength();
	void move(bool);	// Move the snake one step further toward the dir

	int curX() { return head->x; }
	int curY() { return head->y; }
	Node *getHead() { return head; }
	void printSnake();
private:
	void removeAtTail();
	void insertAtHead(Node* newHead);
	int length;

	Node* head = new Node;
	Node* tail = new Node;
	Direction dir;// Direction of the snake
	Status stat;
};
#endif
