#include<GL\freeglut.h>
#include<iostream>
#include<cmath>

using namespace std;

static GLdouble viewer[] = { 0,0,10};  // initial viewer location
GLfloat vertices[8][3] = {
	{ 0.45,-0.55,-1.55 },{ 0.55,-0.55,-1.55 },
	{ 0.55,-0.45,-1.55 },{ 0.45,-0.45,-1.55 },
	{ 0.45,-0.55,-1.45 },{ 0.55,-0.55,-1.45},
	{ 0.55,-0.45,-1.45 },{ 0.45,-0.45,-1.45}
};


GLfloat color[6][3] = { { 1.0,0.0,0.0 },{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,0.0},{0.0,1.0,1.0},{1.0,0.0,1.0} };

void init(void) {

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -5, 5);  //正交投影范围
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-8, 8, -8, 8, -8,8);
	gluPerspective(10, 1, -8,8);
	glMatrixMode(GL_MODELVIEW);
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
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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

	cube();

	glFlush();
	glutSwapBuffers();
}
//Timer for animation in 0.33 second
void TimeFunc(int value) {
	display();
	glutTimerFunc(330, TimeFunc, 1);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //
	glutInitWindowSize(800, 600);
	glutCreateWindow("HW4");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(&display);
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(330, TimeFunc, 1);
	//glDisable(GL_DEPTH_TEST);
	//glutKeyboardFunc(&KeyBoard);
	glutMainLoop();
	return 0;
}