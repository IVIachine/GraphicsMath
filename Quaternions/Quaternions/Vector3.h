#pragma once
class Vector3
{
private:
	float mX, mY, mZ;
public:
	Vector3() { mX = 0.0f; mY = 0.0f; mZ = 0.0f; };
	Vector3(float x, float y, float z) { mX = x; mY = y; mZ = z; };
	Vector3(const Vector3& copy);
	float GetX() { return mX; };
	float GetY() { return mY; };
	float GetZ() { return mZ; };

	float Length();
	float LengthSquared();
	static Vector3 Lerp(Vector3 original, Vector3 goal, float t);
	static Vector3 Cross(Vector3 lhs, Vector3 rhs);
	static float Dot(const Vector3& lhs, const Vector3& rhs);
	void Print();
	~Vector3() {};

	friend Vector3 operator*(Vector3 lhs, float scalar);
	friend Vector3 operator+(Vector3 lhs, Vector3 rhs);
	friend Vector3 operator-(Vector3 lhs, Vector3 rhs);
	friend void operator*=(Vector3& lhs, float scalar);
	friend void operator+=(Vector3& lhs, Vector3 rhs);
	friend void operator-=(Vector3& lhs, Vector3 rhs);
};
