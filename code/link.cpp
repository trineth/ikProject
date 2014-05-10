#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include "link.h"


// class Link {
// 	Point tail; //Closer to body
//  Point head; //Further from body
//  float[2] angle; // vector containing (theta, phi)
// public:

	Link::Link(Point t, Point h) {
		tail = t;
		head = h;
	}

	Point Link::getTail() {
		return tail;
	}

	Point Link::getHead() {
		return head;
	}