#ifndef LINK_H
#define LINK_H

class Point;

class Link {
	Point tail; //Closer to body
	Point head; //Further from body
	float angle[2]; // vector containing (theta, phi)
	float distance;
public:
	Link() {}
	Link(Point t, Point h);
	
	Point getTail();
	Point getHead();

	Link& operator=(const Link& rhs);
};

#endif