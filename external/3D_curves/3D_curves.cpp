#include "3D_curves.h"
#include <cmath>

double pi_v = 3.1415926535;
double DegToRad(double deg) {
	return deg * pi_v / 180;
};

point3D Circle::get_point3D(double t) const {
	point3D point;
	point.z = 0;
	point.x = r * cos(DegToRad(t));
	point.y = r * sin(DegToRad(t));
	return point;
};

point3D Circle::get_first_derivative(double t) const {
	point3D point;
	point.z = 0;
	point.x = r * (-sin(DegToRad(t)));
	point.y = r * cos(DegToRad(t));
	return point;
};

const double Circle::get_R() const {
	return r;
};

point3D Ellipse::get_point3D(double t) const {
	point3D point;
	point.z = 0;
	point.x = rx * cos(DegToRad(t));
	point.y = ry * sin(DegToRad(t));
	return point;
};

point3D Ellipse::get_first_derivative(double t) const {
	point3D point;
	point.z = 0;
	point.x = rx * (-sin(DegToRad(t)));
	point.y = ry * cos(DegToRad(t));
	return point;
};

const double Ellipse::get_Rx() const {
	return rx;
};

const double Ellipse::get_Ry() const {
	return ry;
};

point3D Helix::get_point3D(double t) const {
	point3D point;
	point.z = step * t;
	point.x = r * cos(DegToRad(t));
	point.y = r * sin(DegToRad(t));
	return point;
};

point3D Helix::get_first_derivative(double t) const {
	point3D point;
	point.z = t;
	point.x = r * (-sin(DegToRad(t)));
	point.y = r * cos(DegToRad(t));
	return point;
};

const double Helix::get_R() const {
	return r;
};

const double Helix::get_step() const {
	return step;
};