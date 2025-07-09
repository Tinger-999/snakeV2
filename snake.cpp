#include "snake.h"
#include "curses.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

// Constructor for the Snake class. 
Snake::Snake(int x, int y, Direction direction):length(20), stat(FINE) {
	// Initializes the snake with a head at the specified
	// position (x, y) and sets its initial direction.
	head->x = x;
	head->y = y;
	setDir(direction);
	printSnake();
	
}

// Destructor for the Snake class. 
Snake::~Snake() {
	// Cleans up all dynamically allocated nodes the snake's body.
	Node* body = head;
	while (body->prevNode != NULL) {
		Node* temp = body->prevNode;
		delete body;
		body = temp;
	}

}


void Snake::removeAtTail() {
	// Removes the node at the tail of the snake. Used when the snake moves
	// without growing (i.e., when it doesn't eat a target).
	Node* body = head;

	// Ensure the snake has at least two nodes before proceeding
	if (!body || !body->prevNode) {
		return; // Nothing to remove
	}

	// Traverse the list to find the second-to-last node
	while (body!= nullptr && body->prevNode != nullptr && body->prevNode->prevNode != nullptr) {
		body = body->prevNode;
	}

	// Clear the tail position on the screen
	mvaddch(body->prevNode->y, body->prevNode->x, ' ');

	// Delete the tail node
	delete body->prevNode;

	// Update the new tail's previous node to null
	body->prevNode = nullptr;
}


void Snake::insertAtHead(Node* newHead) {
	// Inserts a new node at the head of the snake. Used to grow the snake
	// or move its head to a new position.//之所以將計算xy座標的過程放在函式，是因為蛇長必須初始化為20
	
	newHead->prevNode = head; // Set the new head's previous node to the current head
	head = newHead; // Update the head pointer
	mvaddch(head->y, head->x, '*'); // Draw the new head on the screen
}

void Snake::printSnake() {
	mvaddch(head->y, head->x, '*');
	for (int i = 1; i < length; i++) {
		Node* newHead = new Node;
		newHead->x = head->x + 1;
		newHead->y = head->y;
		newHead->prevNode = head;
		head = newHead;
		mvaddch(head->y, head->x, '*');
	}
}


void Snake::setDir(Direction new_dir) {
	// Sets the direction of the snake. Ensures the snake cannot reverse
	// directly into itself (e.g., from UP to DOWN).
	dir = new_dir;
}

// Returns the current direction of the snake.
Direction Snake::getDir() {
	return dir;
}

void Snake::setStatus(Status new_status) {
	stat = new_status;
}

Status Snake::getStatus() {
	return stat;
}

void Snake::setLength(int l) {
	length = l;
}

int Snake::getLength() {
	return length;
}

// Moves the snake in its current direction. If `keepTail` is true, the snake
// grows by keeping its tail; otherwise, the tail is removed to maintain the same length.
void Snake::move(bool removeTail) {
	Node* new_head = new Node;
	
	*new_head = *head; // copy the current head

	// 1. Compute position of the new head
	switch (dir) {
	case UP:
		new_head->y -= 1;
		break;
	case DOWN:
		new_head->y += 1;
		break;
	case LEFT:
		new_head->x -= 1;
		break;
	case RIGHT:
		new_head->x += 1;
		break;
	}
	
	// 2. Insert a new node at the snake head and draw the new head at the computed position
	insertAtHead(new_head);
	removeAtTail();
	
	// 3. Clear the tail and remvoe it from the node list if we didn't hit the target
	if (removeTail)
		removeAtTail();
}

