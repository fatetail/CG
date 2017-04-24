#pragma once
#include<GL\freeglut.h>
#include<iostream>
#include<cmath>

using namespace std;

class Vector {
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
public:
	Vector();
	Vector(GLfloat _x, GLfloat _y, GLfloat _z);
	Vector(const Vector &another);
	Vector GetVector();

	GLfloat getX()const;
	GLfloat getY()const;
	GLfloat getZ()const;

	void setX(GLfloat _x);
	void setY(GLfloat _y);
	void setZ(GLfloat _z);

	void Normalize();
	Vector Cross(Vector another)const;
	GLfloat Dot(Vector another);
};
