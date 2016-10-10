#include "stdafx.h"
#include "CoordinatesXYZ.h"


CoordinatesXYZ::CoordinatesXYZ()
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

CoordinatesXYZ::CoordinatesXYZ(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

CoordinatesXYZ::CoordinatesXYZ(const CoordinatesXYZ &c)
{
	this->x = c.x;
	this->y = c.y;
	this->z = c.z;
}

CoordinatesXYZ & CoordinatesXYZ::operator=(const CoordinatesXYZ &c)
{
	if (this != &c) {
		this->x = c.x;
		this->y = c.y;
		this->z = c.z;
	}
	return *this;
}

CoordinatesXYZ::~CoordinatesXYZ()
{
}
void CoordinatesXYZ::setValues(const float &x, const float &y, const float &z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
bool CoordinatesXYZ::operator==(const CoordinatesXYZ &c)
{
	bool isequal = false;
	if (this->x == c.x)
		if (this->y == c.y)
			if (this->z == c.z)
				isequal = true;
	return isequal;
}
bool CoordinatesXYZ::operator!=(const CoordinatesXYZ &c)
{
	return !(*this == c);
}
//EoC
