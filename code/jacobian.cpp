#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include "point.h"
#include "link.h"
#include "Eigen/Dense"

// class Jacobian {
// 	Point goal;
// 	Link links[4];
// public:
	Jacobian(Link one, Link two, Link three, Link four) {
		links[0] = one;
		links[1] = two;
		links[2] = three;
		links[3] = four;
	}

	//Sets the goal to a particular point
	void setGoal(float x, float y, float z) {
		Point temp(x, y, z);
		goal = temp;
	}

	//Checks if the end effector (the last link) has reached the goal
	bool atGoal() {
		Point end = link[3];
		return (end == goal);
	}

	//Moves the goal in a particular direction
	void updateGoal();

	//Uses the Jacobian to move the links toward the goal
	void useJacobian() {
		if (atGoal()) {
			return;
		}


	}

	Eigen::Matrx?F buildJacobian() {
		
	}
// };