#pragma once
class CoordinatesXY
{
public:
	//Atributes
	float x;
	float y;

	//Default operations
	CoordinatesXY();
	CoordinatesXY(const float, const float);
	CoordinatesXY(const CoordinatesXY&);
	CoordinatesXY&	operator=(const CoordinatesXY&);

	~CoordinatesXY();

	//Setters
	void setValues(const float&, const float&);

	//Getters
	bool operator==(const CoordinatesXY&);
	bool operator!=(const CoordinatesXY&);
};

