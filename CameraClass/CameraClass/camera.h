#pragma once
#include<GL\freeglut.h>
#include<iostream>
#include<cmath>
#include"Vector.h"
using namespace std;


const GLfloat PI = 3.1415926;
class Camera {
private:
	Vector u, v, n;
	Vector cam_pos, target_pos, cam_up;
public:
	Camera();
	Camera(const Vector& pos, const Vector& target, const Vector& up);

	// void setCamera(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat lookX, GLfloat lookY, GLfloat lookZ, GLfloat upX, GLfloat upY, GLfloat upZ);
	void pitch(GLfloat angle);
	void yaw(GLfloat angle);
	void roll(GLfloat angle);

	void walk(GLfloat steps);
	void strafe(GLfloat steps);
	void fly(GLfloat steps);
	void translate(GLfloat du, GLfloat dv, GLfloat dn);

	void RotateX(GLfloat x_move);
	void RotateY(GLfloat y_move);
	void RotateRoll(GLfloat x_move);

	void setModelViewMatrix();
	void setShape(GLfloat viewAngle, GLfloat aspect, GLfloat Near, GLfloat Far);
};