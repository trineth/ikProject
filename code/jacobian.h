#ifndef JACOBIAN_H
#define JACOBIAN_H

class Point;
class Link;

class Jacobian {
	Point goal;
	Link links[4];
public:
	Jacobian() {}
	Jacobian(Link one, Link two, Link three, Link four);

	void setGoal(float x, float y, float z); //Sets the goal to a particular point
	bool atGoal(); //Checks if the end effector (the last link) has reached the goal
	void updateGoal(); //Moves the goal in a particular direction

	void useJacobian(); //Uses the Jacobian to move the links toward the goal

};

#endif