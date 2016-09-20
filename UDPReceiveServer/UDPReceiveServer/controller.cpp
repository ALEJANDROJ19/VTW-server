#include "stdafx.h"
#include "controller.h"

//Constructors
controller::controller(int type,CoordinatesXY cord){
	
	this->type=type;
	this->_last_pos = CoordinatesXY(cord.x,cord.y);
	this->_is_last = false;
	
	
	}
	
controller::controller(const controller& ctr){

	type=ctr.type;
	this->_last_pos = ctr._last_pos;
	this->_is_last = ctr._is_last;
	
	}
	
controller& controller::operator =(const controller& ctr){
	
	if(this!=&ctr){
		
		controller aux(ctr);
		type=aux.type;
		this->_last_pos = aux._last_pos;
		this->_is_last = aux._is_last;

		}
	
	return *this;
}

//Destructor

controller::~controller(){
}

//Operations
void controller::move(const CoordinatesXY &coordXY){
	//Move the mouse
	printf("1\t\tex: %f ey: %f\n", coordXY.x, coordXY.y);
	printf("1.1\t\tnx: %f ny: %f\n", this->_last_pos.x, this->_last_pos.y);


	SetCursorPos(this->_last_pos.x + coordXY.x*5, this->_last_pos.y + coordXY.y*5);
	printf("1.2\t\tnx: %f ny: %f\n", _last_pos.x, _last_pos.y);

	_last_pos.x += coordXY.x*-5;
	_last_pos.y += coordXY.y*5;
	printf("2\t\tnx: %f ny: %f\n", _last_pos.x, _last_pos.y);
}

void controller::moveAbs(const CoordinatesXY &coordXY) {
	//Move the mouse
	SetCursorPos(coordXY.x, coordXY.y);
	printf("\t\tex: %f ey: %f\n", coordXY.x, coordXY.y);

	this->_last_pos.x = (float) coordXY.x;
	this->_last_pos.y = (float) coordXY.y;
	printf("2\t\tnx: %f ny: %f\n", this->_last_pos.x, this->_last_pos.y);





}
//private methods
