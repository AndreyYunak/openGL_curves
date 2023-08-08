#ifndef CURVES
#define CURVES

#include <iostream>

struct point3D {
	double x;
	double y;
	double z;
};

enum class Curves {
	circle,
	ellipse,
	helix
};

class Geometric_curves_3D {
private:
	
	Curves curves;

public:
	Geometric_curves_3D(const Curves n) : curves(n) {}; 
	Curves get_type() const{
		return curves;
	};
	virtual ~Geometric_curves_3D()  {};
	virtual point3D get_point3D(double t) const =0;
	virtual point3D get_first_derivative(double t) const =0;
};

class Circle : public Geometric_curves_3D {
private:
	double r;
public:
	Circle(double R) : Geometric_curves_3D(Curves::circle) {
		if (R <= 0) throw "Input ERROR!";
		r = R;
	};
	point3D get_point3D(double t) const override;
	point3D get_first_derivative(double t) const override;
	const double get_R() const;
	~Circle() {};
};

	
class Ellipse : public Geometric_curves_3D {
private:
	double rx;
	double ry;
public:
	Ellipse(double Rx, double Ry) : Geometric_curves_3D(Curves::ellipse) {
		if (Rx <= 0 || Ry <= 0) throw "Input ERROR!";
		rx = Rx;
		ry = Ry;
	};
	~Ellipse() {};
	point3D get_point3D(double t) const override;
	point3D get_first_derivative(double t) const override;
	const double get_Rx() const;
	const double get_Ry() const;
};

class Helix : public Geometric_curves_3D {
private:
	double r;
	double step;
public:
	Helix(double R, double Step) : Geometric_curves_3D(Curves::helix) {
		if(R <= 0 || Step <= 0) throw "Input ERROR!";
		r = R;
		step = Step;
	};
	~Helix() {};
	point3D get_point3D(double t) const override;
	point3D get_first_derivative(double t) const override;
	const double get_R() const;
	const double get_step() const;
};


#endif // CURVES