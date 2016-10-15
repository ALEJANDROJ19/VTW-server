#pragma once

class controlmodule
{
private:
	translate _trans;
	controller* _contr;
	CoordinatesXYZ _lastXYZ;
	CoordinatesXY _lastXY;
	

public:
	//default methods
	controlmodule(CoordinatesXY);
	~controlmodule();

	//operations
	bool input(const CoordinatesXYZ&);
	bool rawmove(const CoordinatesXY & in);
};

