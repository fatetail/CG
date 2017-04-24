#include"camera.h"
#include"Vector.h"

/*
Get u,v,n
n = pos-target;
u = up*n;
v = n*u;
*/
Camera::Camera(const Vector & pos, const Vector& target, const Vector &up) {
	cam_pos = pos;
	target_pos = target;
	cam_up = up;

	Vector tempn(pos.getX()-target.getX(),pos.getY()-target.getY(), pos.getZ()-target.getZ());
	tempn.Normalize();
	Vector tempu(up.Cross(tempn).getX(), up.Cross(tempn).getY(), up.Cross(tempn).getZ());
	tempu.Normalize();
	Vector tempv(tempn.Cross(tempu).getX(), tempn.Cross(tempu).getY(), tempn.Cross(tempu).getZ());
	tempv.Normalize();
	u = tempu;
	v = tempv;
	n = tempn;

	u.Normalize();
	v.Normalize();
	n.Normalize();

	setModelViewMatrix();
}


// Change a point in xyz to uvn
void Camera::setModelViewMatrix() {

	double m[16];
	
	m[0] = u.getX(); m[4] = u.getY(); m[8] = u.getZ(); m[12] = -cam_pos.Dot(u);
	m[1] = v.getX(); m[5] = v.getY(); m[9] = v.getZ(); m[13] = -cam_pos.Dot(v);
	m[2] = n.getX(); m[6] = n.getY(); m[10]= n.getZ(); m[14] = -cam_pos.Dot(n);
	m[3] = 0;		 m[7] = 0;		  m[11] = 0;	   m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m);
}

// Use Perspective Project
void Camera::setShape(GLfloat viewAngle, GLfloat aspect, GLfloat Near, GLfloat Far) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, Near, Far);
}
// Rotate around u axis(same as x axis)
void Camera::pitch(GLfloat angle) {
	GLfloat cos_theta = cos(angle*PI / 180);
	GLfloat sin_theta = sin(angle*PI / 180);

	Vector t(v);
	Vector s(n);

	v.setX(cos_theta*t.getX() - sin_theta*s.getX());
	v.setY(cos_theta*t.getY() - sin_theta*s.getY());
	v.setZ(cos_theta*t.getZ() - sin_theta*s.getZ());

	n.setX(sin_theta*t.getX() + cos_theta*s.getX());
	n.setY(sin_theta*t.getY() + cos_theta*s.getY());
	n.setZ(sin_theta*t.getZ() + cos_theta*s.getZ());

	setModelViewMatrix();
}

// Rotate around v axis(same as y axis)
void Camera::yaw(GLfloat angle) {
	GLfloat cos_theta = cos(angle*PI / 180);
	GLfloat sin_theta = sin(angle*PI / 180);

	Vector t(u);
	Vector s(n);

	u.setX(cos_theta*t.getX() + sin_theta*s.getX());
	u.setY(cos_theta*t.getY() + sin_theta*s.getY());
	u.setZ(cos_theta*t.getZ() + sin_theta*s.getZ());

	n.setX(-sin_theta*t.getX() + cos_theta*s.getX());
	n.setY(-sin_theta*t.getY() + cos_theta*s.getY());
	n.setZ(-sin_theta*t.getZ() + cos_theta*s.getZ());

	setModelViewMatrix();
}

// Rotate around n axis(same as z axis)
void Camera::roll(GLfloat angle) {
	GLfloat cos_theta = cos(angle*PI / 180);
	GLfloat sin_theta = sin(angle*PI / 180);

	Vector t(u);
	Vector s(v);

	u.setX(cos_theta*t.getX() - sin_theta*s.getX());
	u.setY(cos_theta*t.getY() - sin_theta*s.getY());
	u.setZ(cos_theta*t.getZ() - sin_theta*s.getZ());

	v.setX(sin_theta*t.getX() + cos_theta*s.getX());
	v.setY(sin_theta*t.getY() + cos_theta*s.getY());
	v.setZ(sin_theta*t.getZ() + cos_theta*s.getZ());

	setModelViewMatrix();
}




void Camera::translate(GLfloat u_offset, GLfloat v_offset, GLfloat n_offset) {
	Vector offset(u_offset, v_offset, n_offset);
	Vector uvn_x(u.getX(), v.getX(), n.getX());
	Vector uvn_y(u.getY(), v.getY(), n.getY());
	Vector uvn_z(u.getZ(), v.getZ(), n.getZ());

	cam_pos.setX(cam_pos.getX() + offset.Dot(uvn_x));
	cam_pos.setY(cam_pos.getY() + offset.Dot(uvn_y));
	cam_pos.setZ(cam_pos.getZ() + offset.Dot(uvn_z));

	target_pos.setX(target_pos.getX() + offset.Dot(uvn_x));
	target_pos.setY(target_pos.getY() + offset.Dot(uvn_y));
	target_pos.setZ(target_pos.getZ() + offset.Dot(uvn_z));

	setModelViewMatrix();
}


void Camera::walk(GLfloat steps) {
	Vector offset(steps*n.getX(), steps*n.getY(), steps*n.getZ());
	cam_pos.setX(cam_pos.getX() + offset.getX());
	cam_pos.setY(cam_pos.getY() + offset.getY());
	cam_pos.setZ(cam_pos.getZ() + offset.getZ());
	setModelViewMatrix();
}
void Camera::strafe(GLfloat steps) {
	Vector offset(steps*u.getX(), steps*u.getY(), steps*u.getZ());
	cam_pos.setX(cam_pos.getX() + offset.getX());
	cam_pos.setY(cam_pos.getY() + offset.getY());
	cam_pos.setZ(cam_pos.getZ() + offset.getZ());
	setModelViewMatrix();
}
void Camera::fly(GLfloat steps) {
	Vector offset(steps*v.getX(), steps*v.getY(), steps*v.getZ());
	cam_pos.setX(cam_pos.getX() + offset.getX());
	cam_pos.setY(cam_pos.getY() + offset.getY());
	cam_pos.setZ(cam_pos.getZ() + offset.getZ());
	setModelViewMatrix();
}
void Camera::RotateX(GLfloat x_move) {
	GLfloat delta_theta = 0.3;
	GLfloat theta = x_move*delta_theta;
	yaw(theta);
}
void Camera::RotateY(GLfloat y_move) {
	GLfloat delta_theta = 0.3;
	GLfloat theta = y_move*delta_theta;
	pitch(theta);
}
void Camera::RotateRoll(GLfloat x_move) {
	GLfloat delta_theta = 0.3;
	GLfloat theta = x_move*delta_theta;
	roll(theta);
}

