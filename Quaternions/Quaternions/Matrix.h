#pragma once
class Matrix
{
	//Temporary matrix for the conversion from quat to mat3
private:
	double mMatrix[3][3];

public:
	Matrix();
	~Matrix();

	friend class Quaternion;
};

