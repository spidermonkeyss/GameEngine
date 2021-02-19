#include "Vector3.h"

#include "Math.h"

void Vector3::CalculateMagnitude()
{
	magnitude = pow(x * x + y * y + z * z, 0.5);
}

Vector3::Vector3()
	:x(0), y(0), z(0)
{
	CalculateMagnitude();
}

Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z)
{
	CalculateMagnitude();
}

Vector3::~Vector3()
{
}

void Vector3::SetVector3(float x_i, float y_i, float z_i)
{
	x = x_i;
	y = y_i;
	z = z_i;
	CalculateMagnitude();
}

void Vector3::SetVector3(Vector3 vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	CalculateMagnitude();
}

std::string Vector3::Display()
{
	std::string str = "{ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " }";
	return str;
}

Vector3 Vector3::Normalized()
{
	float normalizedX;
	float normalizedY;
	float normalizedZ;

	if (magnitude > 0)
	{
		normalizedX = x / magnitude;
		normalizedY = y / magnitude;
		normalizedZ = z / magnitude;
	}
	return Vector3(normalizedX, normalizedY, normalizedZ);
}

float Vector3::Magnitude()
{
	CalculateMagnitude();
	return 	magnitude;
}

Vector3 Vector3::Up()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::Forward()
{
	return Vector3(0, 0, 1);
}

Vector3 Vector3::Right()
{
	return Vector3(1, 0, 0);
}

#include <iostream>

Vector3 Vector3::operator* (float num)
{
	Vector3 newVec;
	newVec.x = this->x * num;
	newVec.y = this->y * num;
	newVec.z = this->z * num;
	newVec.CalculateMagnitude();
	return newVec;
}

Vector3 Vector3::operator*(Vector3 vec)
{
	Vector3 newVec;
	newVec.x = this->x * vec.x;
	newVec.y = this->y * vec.y;
	newVec.z = this->z * vec.z;
	newVec.CalculateMagnitude();
	return newVec;
}

Vector3 Vector3::operator/(Vector3 vec)
{
	Vector3 newVec;
	newVec.x = this->x / vec.x;
	newVec.y = this->y / vec.y;
	newVec.z = this->z / vec.z;
	newVec.CalculateMagnitude();
	return newVec;
}

Vector3 Vector3::operator/(float num)
{
	Vector3 newVec;
	newVec.x = this->x / num;
	newVec.y = this->y / num;
	newVec.z = this->z / num;
	newVec.CalculateMagnitude();
	return newVec;
}

Vector3 Vector3::operator+(Vector3 vec)
{
	Vector3 newVec;
	newVec.x = this->x + vec.x;
	newVec.y = this->y + vec.y;
	newVec.z = this->z + vec.z;
	newVec.CalculateMagnitude();
	return newVec;
}

Vector3 Vector3::operator-(const Vector3 & vec)
{
	Vector3 newVec;
	newVec.x = this->x - vec.x;
	newVec.y = this->y - vec.y;
	newVec.z = this->z - vec.z;
	newVec.CalculateMagnitude();
	return newVec;
}
