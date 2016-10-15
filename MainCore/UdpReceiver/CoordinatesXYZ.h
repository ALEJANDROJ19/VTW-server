#pragma once
class CoordinatesXYZ
{
public:
	//Atributes
	float x;
	float y;
	float z;

	//Default operations
	CoordinatesXYZ();
	CoordinatesXYZ(const float, const float, const float);
	CoordinatesXYZ(const CoordinatesXYZ&);
	CoordinatesXYZ&	operator=(const CoordinatesXYZ&);

	~CoordinatesXYZ();

	//Setters
	void setValues(const float&, const float&, const float&);

	//Getters
	bool operator==(const CoordinatesXYZ&);
	bool operator!=(const CoordinatesXYZ&);
};

