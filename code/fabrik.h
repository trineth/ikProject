#ifndef FABRIK_H
#define FABRIK_H

class Point;

class Fabrik {
	Point goal;
	Point joints[5];
	float d[4];
	float tol;
	float epsilon;
public:
	Fabrik() {}
	Fabrik(float tolerance, float eps);

	void setJoints(Point one, Point two, Point three, Point four, Point five);
	void setGoal(Point x);
	void setGoal(float x, float y, float z);
	Point* getJoints();
	void compute();
	void shrinkEnd();
};

#endif