#include "HL_Vector2D.h"
#include <iostream>

HL_Vector2D::HL_Vector2D()
{
	this->X = 0;
	this->Y = 0;
}

HL_Vector2D::HL_Vector2D(int x, int y)
{
	this->X = x;
	this->Y = y;
}

float HL_Vector2D::magnitude()
{
	float mag = 0;

	mag = ((X * X) + (Y * Y));
	mag = std::sqrt(mag);


	return mag;
}
