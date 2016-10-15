#pragma once
#include "CoordinatesXY.h"

class translate
{
	friend class CoordinatesXYZ;
	friend class CoordinatesXYZ;

	private:

	public:
	
		translate();
		
		translate(const translate&);
		translate& operator=(const translate&);
		~translate();

		void dummy();
		
		//class methods 
		CoordinatesXY trans(const CoordinatesXYZ&);
};