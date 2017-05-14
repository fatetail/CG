#include"Bezier.h"


const int max_cpts = 4;  // Fixed maximim number of control points
GLfloat cpts[max_cpts][3];	
int cpt_index = 0;		// Record current control point index
int cur_index = 0;		// Record control point's count
bool can_draw = false;  // Record whether curves can draw or not
GLfloat curve_r = 0.0;
GLfloat curve_g = 1.0;
GLfloat curve_b = 0.0;

static int window_width = 500, window_height = 500;

void DrawControlPoint(int _cptindex) {
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex3f(cpts[_cptindex][0], cpts[_cptindex][1], cpts[_cptindex][2]);
	glEnd();
	glFlush();
}

void DrawLine(Point start_point, Point end_point) {
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(start_point.x, start_point.y, 0);
	glVertex3f(end_point.x, end_point.y, 0);
	glEnd();
	glFlush();
}
void MyMouse(int button, int state, int x, int y) {
	float window_x, window_y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (cur_index == 4 && cpt_index == 4) {
			cur_index = 0;
			cpt_index = 0;
		}
		window_x = (2.0*x) / (GLfloat)(window_width - 1) - 1.0;
		window_y = (2.0*(window_height - 1 - y)) / (GLfloat)(window_height - 1) - 1.0;
		cpts[cpt_index][0] = window_x;
		cpts[cpt_index][1] = window_y;
		cpts[cpt_index][2] = 0.0;

		if (cur_index < 4) {
			cur_index++;
		}
		glFlush();
		cpt_index++;

		if (cpt_index >= max_cpts) {
			cur_index = 4;
			cpt_index = 4;
			can_draw = true;
		}

		/*Draw the control point*/
	}
	else if (cur_index == 4) {
		can_draw = true;
	}
}
void KeyBoard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q': {
		exit(0);
		break;
	}
	case 'd': {
		cur_index--;
		cpt_index--;
		if (cur_index < 0) cur_index = 0;
		if (cpt_index < 0) cpt_index = 0;

		can_draw = false;
		glutPostRedisplay();
		break;
	}

	default:
		break;
	}
}
void myReshape(int w, int h) {
	window_width = w;
	window_height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1,1);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (cur_index == 0) glFlush();
	for (int i = 0; i < cur_index; i++) {
		DrawControlPoint(i);
	}

	if (can_draw) {
		for (int i = 0; i < max_cpts - 1; i++) {
			Point start_point(cpts[i][0], cpts[i][1]);
			Point end_point(cpts[i + 1][0], cpts[i + 1][1]);
			DrawLine(start_point, end_point);
		}
		Point a(cpts[0][0], cpts[0][1]);
		Point b(cpts[1][0], cpts[1][1]);
		Point c(cpts[2][0], cpts[2][1]);
		Point d(cpts[3][0], cpts[3][1]);

		for (GLfloat t = 0.0; t <= 1; t += 0.001) {   //GLfloat type t
			Point tempPoint = drawBezier(a, b, c, d, t);
			glColor3f(curve_r, curve_g, curve_b);
			glPointSize(5);
			glBegin(GL_POINTS);
			glVertex2f(tempPoint.x, tempPoint.y);
			glEnd();
			glFlush();
		}
	}
}

void input_parm() {
	cout << "--------------Please Input RGB value between 0 and 1 for Bezier Curve----------------" << endl;
	cin >> curve_r >> curve_g >> curve_b;
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB); //
	glutInitWindowSize(window_width, window_height);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0f);
	glutCreateWindow("HW6");
	glutReshapeFunc(&myReshape);
	glutDisplayFunc(&display);
	glutMouseFunc(&MyMouse);
	glutKeyboardFunc(&KeyBoard);
	input_parm();
	glutMainLoop();
	return 0;
}