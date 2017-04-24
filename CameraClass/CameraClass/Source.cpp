#include<GL\freeglut.h>
#include<iostream>
#include<cmath>
#include"camera.h"
using namespace std;
Vector pos(0.0, 0.0, -1.0);
Vector target(0.0, 0.0, 0.0);
Vector up(0.0, 1.0, 0.0);

Camera camera(pos, target, up);

GLfloat vertices[8][3] = {
	{ -0.5,-0.5,-0.5},{ 0.5,-0.5,-0.5 },
	{ 0.5,0.5,-0.5 },{ -0.5,0.5,-0.5 },
	{ -0.5,-0.5,0.5 },{ 0.5,-0.5,0.5 },
	{ 0.5,0.5,0.5 },{ -0.5,0.5,0.5 }
};


GLfloat color[6][3] = { { 1.0,0.0,0.0 },{ 0.0,1.0,0.0 },{ 0.0,0.0,1.0 },{ 1.0,1.0,0.0 },{ 0.0,1.0,1.0 },{ 1.0,0.0,1.0 } };

GLfloat camera_speed = 0.5f;

bool LeftMouseOn = false;
bool RightMouseOn = false;
bool MiddleMouseOn = false;

int lastMouseX = 0;
int lastMouseY = 0;


void reshape(int width, int height) {
	camera.setShape(45.0, 1, 0.1, 20);
}

//Draw the first cube's quad
void quad(int a, int b, int c, int d) {

	glBegin(GL_QUADS);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();

}


void cube() {
	glColor3fv(color[0]);
	quad(0, 3, 2, 1);
	glColor3fv(color[1]);
	quad(2, 3, 7, 6);
	glColor3fv(color[2]);
	quad(0, 4, 7, 3);
	glColor3fv(color[3]);
	quad(1, 2, 6, 5);
	glColor3fv(color[4]);
	quad(4, 5, 6, 7);
	glColor3fv(color[5]);
	quad(0, 1, 5, 4);
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera.setModelViewMatrix();
	
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(10000, 0, 0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10000, 0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 10000);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	cube();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
void onMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		LeftMouseOn = true;
		lastMouseX = x;
		lastMouseY = y;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		RightMouseOn = true;
		lastMouseX = x;
		lastMouseY = y;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		MiddleMouseOn = true;
		lastMouseX = x;
		lastMouseY = y;
	}
	else {
		LeftMouseOn = false;
		RightMouseOn = false;
		MiddleMouseOn = false;
	}
}
void onMouseMove(int x, int y) {
	int dx = x - lastMouseX;
	int dy = y - lastMouseY;

	if (LeftMouseOn) {
		camera.RotateX(dx);
		camera.RotateY(dy);
	}
	else if (RightMouseOn) {
		camera.RotateRoll(dx);
	}
	else if (MiddleMouseOn) {
		camera.translate(-dx, dy, 0);
	}
	lastMouseX = x;
	lastMouseY = y;
}
void KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': {
		camera.walk(camera_speed);
		glutPostRedisplay();
		break;
	}
	case 's': {
		camera.walk(-camera_speed);
		glutPostRedisplay();
		break;
	}
	case 'a': {
		camera.strafe(-camera_speed);
		glutPostRedisplay();
		break;
	}
	case 'd': {
		camera.strafe(camera_speed);
		glutPostRedisplay();
		break;
	}
	case 'q': {
		camera.fly(camera_speed);
		glutPostRedisplay();
		break;
	}
	case 'e': {
		camera.fly(-camera_speed);
		glutPostRedisplay();
		break;
	}
	}
}

int main(int argc, char* argv[]) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("HW4");
	glutReshapeFunc(&reshape);
	glutDisplayFunc(&display);
	glEnable(GL_DEPTH_TEST);
	glutMouseFunc(&onMouse);
	glutMotionFunc(&onMouseMove);
	glutKeyboardFunc(&KeyBoard);
	glutMainLoop();
	return 0;
}