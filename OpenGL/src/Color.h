#pragma once

class Color
{
public:
	float r, g, b;
	float a;
	
	Color();
	Color(float r, float g, float b, float a);
	~Color();

	void SetColor(float r, float g, float b, float a);
};