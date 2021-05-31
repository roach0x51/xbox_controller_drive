//#include <iostream>
//#include <windows.h>
//#include <Xinput.h>
//#include <string>
//#include <iomanip>
#include "xbox_controller.h"

using namespace std;

int main(){
	XboxController one(0);
	bool QUIT = false;

	while (!QUIT){
		one.SetPushButtons();
		cout << one.GetStick(LEFT_SIDE).axisX << " " << one.GetStick(LEFT_SIDE).axisY << endl;
		
		one.PrintPushButtons();
	
	
	
	}
	return 0;

}