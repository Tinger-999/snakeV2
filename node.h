#ifndef NODE_H
#define NODE_H

#include "snake.h"

class Node {
	friend class Snake;
public:
	Node(int x = 0, int y = 0, Node* prevNode = nullptr) : prevNode(prevNode) {}
	Node* getPrevNode() { return prevNode; }
	int getX() { return x; }
	int getY() { return y; }
private:
	int x;
	int y;
	Node* prevNode;
};

#endif
