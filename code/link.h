#ifndef POINT_H
#define POINT_H
#include "point.h"

class Link {
	Point tail; //Closer to body
	Point head; //Further from body
	float[2] angle; // vector containing (theta, phi)
public:
	Link(Point t, Point h);
	
	Point getTail();
	Point getHead();

#endif