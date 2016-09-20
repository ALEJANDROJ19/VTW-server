#include "stdafx.h"
#include "CoordinatesXY.h"


CoordinatesXY::CoordinatesXY()
{
	this->x = 0.0;
	this->y = 0.0;
}

CoordinatesXY::CoordinatesXY(const float x, const float y) {
	this->x = x;
	this->y = y;
}

CoordinatesXY::CoordinatesXY(const CoordinatesXY &c)
{
	this->x = c.x;
	this->y = c.y;
}

CoordinatesXY & CoordinatesXY::operator=(const CoordinatesXY &c)
{
	if (this != &c) {
		this->x = c.x;
		this->y = c.y;
	}
	return *this;
}

CoordinatesXY::~CoordinatesXY()
{
}
void CoordinatesXY::setValues(const float &x, const float &y)
{
	this->x = x;
	this->y = y;
}

bool CoordinatesXY::operator==(const CoordinatesXY &c)
{
	bool isequal = false;
	if (this->x == c.x)
		if (this->y == c.y)
			isequal = true;
	return isequal;
}
bool CoordinatesXY::operator!=(const CoordinatesXY &c)
{
	return !(*this == c);
}
//EoC
