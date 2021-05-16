#include "HL_Vector2D.h"
#include <iostream>

HL_Vector2D::HL_Vector2D()
{
	this->X = 0;
	this->Y = 0;
}

HL_Vector2D::HL_Vector2D(double x, double y)
{
	this->X = x;
	this->Y = y;
}

double HL_Vector2D::magnitude()
{
	double mag = 0;

	mag = ((X * X) + (Y * Y));
	mag = std::sqrt(mag);


	 return mag;
}

double HL_Vector2D::distance(HL_Vector2D* otherVector)
{
	double xdist = ( otherVector->X - this->X);
	double ydist = ( otherVector->Y- this->Y);

	double value = sqrt((xdist * xdist) + (ydist * ydist));

	return value;
}

