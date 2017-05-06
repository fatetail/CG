#pragma once
#include<GL\freeglut.h>
#include<iostream>
#include<cmath>
struct Point {
	GLfloat x;
	GLfloat y;
	Point(GLfloat _x, GLfloat _y):x(_x),y(_y) {}
};
using namespace std;

Point drawBezier(Point a, Point b, Point c, Point d, GLfloat t) {
	GLfloat coff[4];
	coff[0] = pow(1-t,3);
	coff[1] = 3*t*pow(1-t,2);
	coff[2] = 3 * pow(t, 2)*(1 - t);
	coff[3] = pow(t, 3);

	GLfloat result_x = coff[0] * a.x + coff[1] * b.x + coff[2] * c.x + coff[3] * d.x;
	GLfloat result_y = coff[0] * a.y + coff[1] * b.y + coff[2] * c.y + coff[3] * d.y;

	Point result(result_x, result_y);
	return result;
	
}