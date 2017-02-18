#pragma once
#include "Vector3.h"
#include "Matrix.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Quaternion
{
private:
	double mW, mX, mY, mZ;

public:
	Quaternion();
	Quaternion(double x, double y, double z, double w);
	~Quaternion() {};

	static Quaternion makeXRotation(double desiredRotation);

	static Quaternion makeYRotation(double desiredRotation);

	static Quaternion makeZRotation(double desiredRotation);

	static Quaternion makeXYZRotation(double desiredRotationX, double desiredRotationY, double desiredRotationZ);

	static Quaternion makeZYXRotation(double desiredRotationX, double desiredRotationY, double desiredRotationZ);

	void normalize();

	static Quaternion identity();

	void print();

	static Quaternion concatenate(Quaternion a, Quaternion b);

	static Quaternion multVec(Quaternion target, Vector3 vec);

	static double dot(Quaternion lhs, Quaternion rhs);

	static Quaternion slerp(Quaternion first, Quaternion second, double t);
	static Quaternion lerp(Quaternion first, Quaternion second, double t);

	static Matrix convertToMatrix(Quaternion quat);

	static double magnitude(Quaternion quat);

	friend Quaternion operator*(Quaternion quat, double f);
	friend Quaternion operator+(Quaternion lhs, Quaternion rhs);
	friend Quaternion operator-(Quaternion lhs, Quaternion rhs);
};

