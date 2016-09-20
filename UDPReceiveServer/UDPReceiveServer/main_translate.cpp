#include "stdafx.h"
#include "translate.h"

#include <math.h>

using namespace std;
/*/
int main(){

	CoordinatesXYZ vecthree;
	translate tra;
	controller crt(1);

	crt.moveAbs(CoordinatesXY((GetSystemMetrics(SM_CXSCREEN) - 1) / 2, (GetSystemMetrics(SM_CYSCREEN) - 1) / 2));

	for (int i = 0; i < 100; i++) {
		vecthree.setValues((rand() % 6) / 1.5, (rand() % 6) / 1.5, (rand() % 6) / 1.5);
		CoordinatesXY vectwo = tra.trans(vecthree);
		//move
		crt.move(vectwo);
		Sleep(500);
		printf("Moved cursor: x= %f, y= %f\n", vectwo.x, vectwo.y);
	}
	//

	
	tra.dummy();
	
	cin.get();
	return 0;
}*/

int d_main() {

	CoordinatesXY a(8.0, 10.0);
	
	CoordinatesXYZ a1(2.0, 3.0, 5.0);
	/*controller ctr(1, a);
	translate tra;

	ctr.moveAbs(tra.trans(a1));

	ctr.move(tra.trans(a1));
	//ctr.move

	*/
	controlmodule ctr1(a);
	ctr1.input(a1);

	printf("///x: %f y: %f z: %f", a1.x, a1.y, a1.z);

	cin.get();
	return 0;
}
