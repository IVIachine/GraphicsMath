#include "Vector3.h"
#include <math.h>
#include <iostream>

Vector3::Vector3(const Vector3 & copy)
{
	mX = copy.mX;
	mY = copy.mY;
	mZ = copy.mZ;
}

float Vector3::Length()
{
	return sqrt(mX * mX + mY * mY + mZ * mZ);
}

float Vector3::LengthSquared()
{
	return mX * mX + mY * mY + mZ * mZ;
}

Vector3 Vector3::Lerp(Vector3 original, Vector3 goal, float t)
{
	return original * (1 - t) + goal * t;
}

Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs)
{
	return Vector3((lhs.mY * rhs.mZ) - (lhs.mZ * rhs.mY),
		(lhs.mZ * rhs.mX) - (lhs.mX * rhs.mZ),
		(lhs.mX * rhs.mY) - (lhs.mY * rhs.mX));
}

float Vector3::Dot(const Vector3 & lhs, const Vector3 & rhs)
{
	return lhs.mX * rhs.mX + lhs.mY * rhs.mY + lhs.mZ * rhs.mZ;
}

void Vector3::Print()
{
	std::cout << "{ " << mX << ", " << mY << ", " << mZ << " }\n";
}

Vector3 operator*(Vector3 lhs, float scalar)
{
	Vector3 newVec = Vector3();
	newVec.mX = lhs.mX * scalar;
	newVec.mY = lhs.mY * scalar;
	newVec.mZ = lhs.mZ * scalar;
	return newVec;
}

Vector3 operator+(Vector3 lhs, Vector3 rhs)
{
	Vector3 newVec = Vector3();
	newVec.mX = lhs.mX + rhs.mX;
	newVec.mY = lhs.mY + rhs.mY;
	newVec.mZ = lhs.mZ + rhs.mZ;
	return newVec;
}

Vector3 operator-(Vector3 lhs, Vector3 rhs)
{
	Vector3 newVec = Vector3();
	newVec.mX = lhs.mX - rhs.mX;
	newVec.mY = lhs.mY - rhs.mY;
	newVec.mZ = lhs.mZ - rhs.mZ;
	return newVec;
}

void operator*=(Vector3& lhs, float scalar)
{
	lhs.mX *= scalar;
	lhs.mY *= scalar;
	lhs.mZ *= scalar;;
}

void operator+=(Vector3& lhs, Vector3 rhs)
{
	lhs.mX += rhs.mX;
	lhs.mY += rhs.mY;
	lhs.mZ += rhs.mZ;
}

void operator-=(Vector3& lhs, Vector3 rhs)
{
	lhs.mX -= rhs.mX;
	lhs.mY -= rhs.mY;
	lhs.mZ -= rhs.mZ;
}
