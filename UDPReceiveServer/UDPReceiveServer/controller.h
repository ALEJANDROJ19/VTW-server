#pragma once
class controller
{
	private:
		int type;
		CoordinatesXY _last_pos;
		bool _is_last;
	
	public:

		explicit controller(int, CoordinatesXY);	
		controller(const controller&);
		controller& operator=(const controller&);
		~controller();
		
		//class methods 
		void moveAbs(const CoordinatesXY &);
		void move(const CoordinatesXY &);
		
};

