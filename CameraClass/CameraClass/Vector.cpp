#include"Vector.h"
Vector::Vector() {}
Vector::Vector(GLfloat _x, GLfloat _y, GLfloat _z) {
	x = _x;
	y = _y;
	z = _z;
}
Vector::Vector(const Vector& another) {
	x = another.x;
	y = another.y;
	z = another.z;
}

Vector Vector::GetVector() {
	Vector result(x, y, z);
	return result;
}

GLfloat Vector::getX() const{ return x; }

GLfloat Vector::getY() const{ return y; }

GLfloat Vector::getZ() const{ return z; }

void Vector::setX(GLfloat _x) { x = _x; }

void Vector::setY(GLfloat _y) { y = _y; }

void Vector::setZ(GLfloat _z) { z = _z; }


void Vector::Normalize() {
	GLfloat denominator = pow(x*x + y*y + z*z, 0.5);
	x /= denominator;
	y /= denominator;
	z /= denominator;
}


Vector Vector::Cross(Vector another) const{
	GLfloat result_x = y*another.getZ() - z*another.getY();
	GLfloat result_y = z*another.getX() - x*another.getZ();
	GLfloat result_z = x*another.getY() - y*another.getX();

	Vector result(result_x, result_y, result_z);
	return result;

}

GLfloat Vector::Dot(Vector another) {
	return (x*another.getX() + y*another.getY() + z*another.getZ());
}

