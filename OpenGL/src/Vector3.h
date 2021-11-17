#pragma once

#include <string>

class Vector3
{
private:
	float magnitude;
	void CalculateMagnitude();
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();
	
	float x, y, z;

	void SetVector3(float x, float y, float z);
	void SetVector3(Vector3 vec);

	std::string Display();

	Vector3 Normalized();
	float Magnitude();

	static Vector3 Up();
	static Vector3 Forward();
	static Vector3 Right();
	
	Vector3 operator* (Vector3 vec);
	Vector3 operator* (float num);
	Vector3 operator/ (Vector3 vec);
	Vector3 operator/ (float num);
	Vector3 operator+ (Vector3 vec);
	Vector3 operator- (const Vector3& vec);
	
};