#include "Color.h"

Color::Color()
	:r(1), g(1), b(1), a(1)
{

}

Color::Color(float r, float g, float b, float a)
	:r(r), g(g), b(b), a(a)
{
}

Color::~Color()
{
}

void Color::SetColor(float r_i, float g_i, float b_i, float a_i)
{
	r = r_i;
	g = g_i;
	b = b_i;
	a = a_i;
}
