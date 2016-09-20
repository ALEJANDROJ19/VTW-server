#include "stdafx.h"
#include "translate.h"

//Constructors

translate::translate(){}
translate::translate(const translate& tra){}
translate& translate::operator=(const translate& tra){
	if(this != &tra){}
	
	return *this;
}

//Destructor

translate::~translate(){}

//Operations
CoordinatesXY translate::trans(const CoordinatesXYZ &vec){
	CoordinatesXY ret;
	ret.x=vec.x;
	ret.y=vec.y;
						printf("x: %f y: %f \n",ret.x,ret.y);//DEBUG
	return CoordinatesXY(ret);
}

void translate::dummy() {}

//private methods