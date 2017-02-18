#include "Quaternion.h"
#include <iostream>

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(double x, double y, double z, double w)
{
	mW = w;
	mX = x;
	mY = y;
	mZ = z;
}

Quaternion Quaternion::makeXRotation(double desiredRotation) //Create the x-rotation axis
{
	double rot = desiredRotation * M_PI / 180;
	double f = sin(rot / 2);
	Quaternion xAxis = Quaternion(1 * f, 0 * f, 0 * f, cos(rot / 2));
	xAxis.normalize();
	return xAxis;
}

Quaternion Quaternion::makeYRotation(double desiredRotation)
{
	double rot = desiredRotation * M_PI / 180;
	double f = sin(rot / 2);
	Quaternion yAxis = Quaternion(0 * f, 1 * f, 0 * f, cos(rot / 2));
	yAxis.normalize();
	return yAxis;
}

Quaternion Quaternion::makeZRotation(double desiredRotation)
{
	double rot = desiredRotation * M_PI / 180;
	double f = sin(rot / 2);
	Quaternion zAxis = Quaternion(0 * f, 0 * f, 1 * f, cos(rot / 2));
	zAxis.normalize();
	return zAxis;
}

Quaternion Quaternion::makeXYZRotation(double desiredRotationX, double desiredRotationY, double desiredRotationZ)
{
	Quaternion xRot = makeXRotation(desiredRotationX);
	Quaternion yRot = makeYRotation(desiredRotationY);
	Quaternion zRot = makeZRotation(desiredRotationZ);
	Quaternion xyz = concatenate(concatenate(xRot, yRot), zRot);
	return xyz;
}

Quaternion Quaternion::makeZYXRotation(double desiredRotationX, double desiredRotationY, double desiredRotationZ)
{
	Quaternion xRot = makeXRotation(desiredRotationX);
	Quaternion yRot = makeYRotation(desiredRotationY);
	Quaternion zRot = makeZRotation(desiredRotationZ);
	Quaternion zyx = concatenate(concatenate(zRot, yRot), xRot);
	return zyx;
}

void Quaternion::normalize()
{
	double f = Quaternion::magnitude(*this);
	mX /= f;
	mY /= f;
	mZ /= f;
	mW /= f;
}

Quaternion Quaternion::identity()
{
	return Quaternion(0, 0, 0, 1);
}

void Quaternion::print()
{
	std::cout << "{ " << mX << ", " << mY << ", " << mZ << ", " << mW << " }" << std::endl;
}

Quaternion Quaternion::concatenate(Quaternion a, Quaternion b) //Add multiple rotations
{
	Quaternion result;
	result.mX = a.mX * b.mW + a.mY * b.mZ - a.mZ * b.mY + a.mW * b.mX;
	result.mY = -a.mX * b.mZ + a.mY * b.mW + a.mZ * b.mX + a.mW * b.mY;
	result.mZ = a.mX * b.mY - a.mY * b.mX + a.mZ * b.mW + a.mW * b.mZ;
	result.mW = -a.mX * b.mX - a.mY * b.mY - a.mZ * b.mZ + a.mW * b.mW;
	return result;
}

Quaternion Quaternion::multVec(Quaternion target, Vector3 vec)
{
	Quaternion tmp = Quaternion((double)vec.GetX(), (double)vec.GetY(), (double)vec.GetZ(), 0);
	Quaternion concatenation = concatenate(target, tmp);
	return concatenation;
}

double Quaternion::dot(Quaternion lhs, Quaternion rhs)
{
	return lhs.mX * rhs.mX + lhs.mY * rhs.mY + lhs.mZ * rhs.mZ + lhs.mW * rhs.mW;
}

Quaternion Quaternion::slerp(Quaternion first, Quaternion second, double t)
{
	double dot = Quaternion::dot(first, second);
	double theta = std::acos(dot);
	double sTheta = std::sin(theta);

	double w1 = sin((1.0f - t)*theta) / sTheta;
	double w2 = sin(t*theta) / sTheta;

	Quaternion temp(0, 0, 0, 0);
	temp = first*w1 + second*w2;
	return temp;
}

Quaternion Quaternion::lerp(Quaternion first, Quaternion second, double t)
{
	Quaternion temp;
	double time = 1 - t;
	temp.mX = time*first.mX + t*second.mX;
	temp.mY = time*first.mY + t*second.mY;
	temp.mZ = time*first.mZ + t*second.mZ;
	temp.mW = time*first.mW + t*second.mW;
	return temp;
}

Matrix Quaternion::convertToMatrix(Quaternion quat)
{
	Matrix theResult;
	double sqw = quat.mW*quat.mW;
    double sqx = quat.mX*quat.mX;
    double sqy = quat.mY*quat.mY;
    double sqz = quat.mZ*quat.mZ;

    theResult.mMatrix[0][0] = ( sqx - sqy - sqz + sqw); //Main diagonal first
	theResult.mMatrix[1][1] = (-sqx + sqy - sqz + sqw);
	theResult.mMatrix[2][2] = (-sqx - sqy + sqz + sqw);
    
    double xy = quat.mX*quat.mY;
    double zw = quat.mZ*quat.mW;
	theResult.mMatrix[1][0] = 2.0 * (xy + zw);
	theResult.mMatrix[0][1] = 2.0 * (xy - zw);
    
    double xz = quat.mX*quat.mZ;
	double yw = quat.mY*quat.mW;
	theResult.mMatrix[2][0] = 2.0 * (xz - yw);
	theResult.mMatrix[0][2] = 2.0 * (xz + yw);

	double yz = quat.mY*quat.mZ;
	double xw = quat.mX*quat.mW;
	theResult.mMatrix[2][1] = 2.0 * (yz + xw);
	theResult.mMatrix[1][2] = 2.0 * (yz - xw);
	return theResult;
}

double Quaternion::magnitude(Quaternion quat)
{
	return sqrt((quat.mX * quat.mX) + (quat.mY * quat.mY) + (quat.mZ * quat.mZ) + (quat.mW * quat.mW));
}

Quaternion operator*(Quaternion quat, double f)
{
	quat.mX *= f;
	quat.mY *= f;
	quat.mZ *= f;
	quat.mW *= f;
	return quat;
}

Quaternion operator+(Quaternion lhs, Quaternion rhs)
{
	Quaternion result(0, 0, 0, 0);
	result.mX = lhs.mX + rhs.mX;
	result.mY = lhs.mY + rhs.mY;
	result.mZ = lhs.mZ + rhs.mZ;
	result.mW = lhs.mW + rhs.mW;
	return result;
}

Quaternion operator-(Quaternion lhs, Quaternion rhs)
{
	Quaternion result(0, 0, 0, 0);
	result.mX = lhs.mX - rhs.mX;
	result.mY = lhs.mY - rhs.mY;
	result.mZ = lhs.mZ - rhs.mZ;
	result.mW = lhs.mW - rhs.mW;
	return result;
}
