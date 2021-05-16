#pragma once
#include <iostream>
class HL_Vector2D
{
public:
	HL_Vector2D();
	HL_Vector2D(double x, double y);

	double X, Y;
	double magnitude();

	double distance(HL_Vector2D* otherVector);

};

