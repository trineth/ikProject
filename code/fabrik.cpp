#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include "point.h"
#include "fabrik.h"
#include "Eigen/Dense"

// class Fabrik {
// 	Point goal;
// Point joints[5];
// float d[4];
// float tol;
// public:
	Fabrik::Fabrik(float tolerance) {
		tol = tolerance;
	}

	void Fabrik::setGoal(Point x) {
		goal = x;
	}

	void Fabrik::setGoal(float x, float y, float z) {
		Point temp(x, y, z);
		goal = temp;
	}

	void Fabrik::setJoints(Point one, Point two, Point three, Point four, Point five) {
		joints[0] = one;
		joints[1] = two;
		joints[2] = three;
		joints[3] = four;
		joints[4] = five;

		float d0 = (two - one).getDistance();
		float d1 = (three - two).getDistance();
		float d2 = (four - three).getDistance();
		float d3 = (five - four).getDistance();
		d[0] = d0;
		d[1] = d1;
		d[2] = d2;
		d[3] = d3;
	}

	Point* Fabrik::getJoints() {
		return joints;
	}

	void Fabrik::shrinkEnd() {
		float dCalc = (joints[4] - joints[3]).getDistance();
		float dExact = d[3];

		if (abs(dCalc - dExact) > 0.01) {
			Point vector = joints[4] - joints[3];
			vector.normalize();
			double factor = dExact / vector.getDistance();
			joints[4] = joints[3] + (vector * factor);
			goal = joints[4];
		}
	}

	// Uses the FABRIK algorithm to compute IK
	void Fabrik::compute(bool norm) {
		int n = 4; //number of joints
		Point p0 = joints[0];
		Point p1 = joints[1];
		Point p2 = joints[2];
		Point p3 = joints[3];
		Point p4 = joints[4];
		Point t = goal;

		float d0 = (p1 - p0).getDistance();
		float d1 = (p2 - p1).getDistance();
		float d2 = (p3 - p2).getDistance();
		float d3 = (p4 - p3).getDistance();
		std::cout << d0 << " " << d1 << " " << d2 << " " << d3 << "\n";

		float dist = (p0 - goal).getDistance();

		if (dist > d[0] + d[1] + d[2] + d[3]) { //Target unreachable
			float r, lambda;
			for (int i = 0; i < n-1; i++) {
				r = (goal - joints[i]).getDistance();
				lambda = d[i] / r;
				joints[i+1] = (1-lambda) * joints[i] + lambda * goal;
			}
		}
		else { //Target reachable
			Point b = p0;
			float difA = (p4 - t).getDistance();
			while (difA > tol) {
				//STAGE ONE: Forward Reaching
				joints[n] = t;
				for (int i = n-1; i >= 0; i--) {
					float r = (joints[i+1] - joints[i]).getDistance();
					float lambda = d[i] / r;
					joints[i] = ((1-lambda) * joints[i+1]) + (lambda * joints[i]);
				}

				//STAGE 2: Backward Reaching
				joints[0] = b;
				for (int i = 0; i < n-1; i++) {
					float r = (joints[i+1] - joints[i]).getDistance();
					float lambda = d[i] / r;
					joints[i+1] = ((1-lambda) * joints[i]) + (lambda * joints[i+1]);
				}
				difA = (joints[n] - t).getDistance();
			}
		}

		if (norm) {
			shrinkEnd();
		}
	}