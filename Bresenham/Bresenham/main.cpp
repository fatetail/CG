#include<GL\freeglut.h>
#include<iostream>
#include<cmath>
#include<algorithm>

#define ROUND(a) ((int)(a+0.5))   // 四舍五入
#define PI 3.1415926535898
#define N 200
int m_x1, m_y1, m_x2, m_y2;
int m_x0, m_y0, m_r;

using namespace std;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);  //正交投影范围
}
void DDA_Line(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1, dy = y2 - y1; //计算端点x的差值,计算端点y的差值
	int steps;    //用于计算增量

	float xIncrement, yIncrement, x = x1, y = y1;
	if (abs(dx) > abs(dy)) {
		steps = abs(dx);
	}
	else {
		steps = abs(dy);
	}
	xIncrement = dx / (float)steps;  //计算x方向每一步增量
	yIncrement = dy / (float)steps;  //计算y方向每一步增量

									 //绘制开始点
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glVertex2i(ROUND(x), ROUND(y));
	glEnd();
	glFlush();
	//绘制每一步的点
	for (int k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		glBegin(GL_POINTS);
		glVertex2i(ROUND(x), ROUND(y));
		glEnd();
		glFlush();
	}

}

void input_parm() {
	cout << "1.Draw a line" << endl;
	cout << "2.Draw a circle" << endl;
	int choose;
	cin >> choose;
	if (choose == 1) {
		cout << endl << endl << endl << endl << endl;
		cout << "Please input start point(x0,y0) and end point(x1,y1)" << endl;
		int x0, y0, x1, y1;
		cin >> x0 >> y0 >> x1 >> y1;
		m_x1 = x0;
		m_y1 = y0;
		m_x2 = x1;
		m_y2 = y1;
	}
	else {
		cout << endl << endl << endl << endl << endl;
		cout << "Please input center of the circle (x0,y0) and radius r" << endl;
		int x1, y1, radius;
		cin >> x1 >> y1 >> radius;
		m_x0 = x1;
		m_y0 = y1;
		m_r = radius;
	}
}

void Bresenham_Line(int x1, int y1, int x2, int y2) {

	glPointSize(4.0f);
	glColor3f(0.0f, 1.0f, 0.0f);

	int dx = abs(x2 - x1), dy = abs(y2 - y1);  //确定Delta(x)和Delta(y)的绝对值大小
	int StepX = x2 - x1 > 0 ? 1 : -1;  //确定X方向上的增量
	int StepY = y2 - y1 > 0 ? 1 : -1;  //确定y方向上的增量
	int x = x1, y = y1;

	if (dx > dy) {  //斜率的绝对值小于1
		int two_y = 2 * dy;   //计算2*Delta(y)
		int two_diffence = 2 * (dy - dx);  //计算2*Delta(y)-2*Delta(x)
		int p = 2 * dy - dx;  //计算p的初始值

		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		glFlush();
		while (x != x2) {//切记用不等于
			if (p <= 0) {  //如果p<=0,y保持不变;
				p += two_y;   //更新p
			}
			else {
				y += StepY;  //y加一个方向的增量
				p += two_diffence;   //更新p
			}
			x += StepX;
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			glFlush();
		}
		glFlush();
	}
	else {//斜率的绝对值大于1
		int two_x = 2 * dx;   //计算2*Delta(x)
		int two_diffence = 2 * (dx - dy);  //计算2*Delta(x)-2*Delta(y)
		int p = 2 * dx - dy;

		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		glFlush();
		while (y != y2) {
			if (p <= 0) {  //如果p<=0,x保持不变;
				p += two_x;   //更新p
			}
			else {
				x += StepX;
				p += two_diffence;   //更新p
			}
			y += StepY;
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			glFlush();
		}
		glFlush();
	}

}

void Bresenham_Circle(int x0, int y0, int radius) {
	int x = 0, y = radius;
	int d = (5 >> 2) - radius;  // d = 1.25-radius
	glPointSize(4.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	while (y >= x) {
		glBegin(GL_POINTS);
		glVertex2i(x0 + x, y0 + y);   //八个小圆弧,x0、y0为平移量
		glVertex2i(x0 + y, y0 + x);
		glVertex2i(x0 + x, y0 - y);
		glVertex2i(x0 + y, y0 - x);

		glVertex2i(x0 -x, y0 + y);   //八个小圆弧
		glVertex2i(x0 -y, y0 +x);
		glVertex2i(x0 -x, y0 - y);
		glVertex2i(x0 -y, y0 - x);
		glEnd();
		glFlush();
		
		if (d < 0) {
			d += (x<<1) + 3;    // 当取较上面点时，递推公式
		}
		else {
			d += ((x - y)<<1) + 5;  //当取下面点时，递推公式
			y--;
		}
		x++;

	}
}

void polar_circle(int x0, int y0, int radius) {
	glPointSize(4.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < N; i++) {
		glBegin(GL_POINTS);
		glVertex2i(ROUND(x0 + radius*cos((((GLfloat)(PI))*2)*i / N)), ROUND(y0 + radius*sin(((GLfloat(PI))*2)*i / N)));  // 使用极坐标画圆
	}
	glEnd();
	glFlush();
}


void display() {

	//Bresenham_Line(-10, -10, 20, 30);
	//Bresenham_Line(-10, -10, -20, 30);
	//Bresenham_Line(-10, -10, 20, -30);
	//Bresenham_Line(-10, -10, -20, -30);
	//Bresenham_Line(10, 0, 10, -10);
	//Bresenham_Line(30, 0, 20, 0);
	//Bresenham_Circle(40, 40, 10);
	//polar_circle(40, 40, 10);
}

void KeyBoard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q':
		//按键1, DDA画直线
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DDA_Line(m_x1, m_y1, m_x2, m_y2);
		break;
	}
	case 'w':
		// 按键2,Bresenham画直线
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Bresenham_Line(m_x1, m_y1, m_x2, m_y2);
		break;
	}
	case 'e':
		//按键3，Bresenham画圆
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Bresenham_Circle(m_x0, m_y0, m_r);
		break;
	}
	case 'r':
		//按键4，多边形画圆
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		polar_circle(m_x0, m_y0, m_r);
		break;
	}
	default:
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("HW3");
	init();
	glutDisplayFunc(&display);
	glutKeyboardFunc(&KeyBoard);
	input_parm();
	glutMainLoop();
	return 0;
}