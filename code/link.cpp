#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include "point.h"
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

	// float calculateDistance() {
	// 	return sqrt(pow(head.getX() - tail.getX(), 2)
	// 		+ pow(head.getY() - tail.getY(), 2)
	// 		+ pow(head.getZ() - tail.getZ(), 2));
	// }

	// float getDistance() {
	// 	return distance;
	// }

	Link& Link::operator=(const Link& rhs) {
 		this->tail = rhs.tail;
  		this->head = rhs.head;
  		this->distance = rhs.distance;
  		return *this;
 	}