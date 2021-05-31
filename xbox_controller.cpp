#include "xbox_controller.h"

using namespace std;

const int XboxController::buttonMask[14] = {
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y
};


 //*************************
 //	Constructor functions
 //*************************
 XboxController::XboxController(){
	 XInputEnable(true);
	 SetDeadZone(DEFAULT_DEADZONE, DEFAULT_DEADZONE);
 }

 XboxController::XboxController(DWORD controller_num){
	 if (controller_num >= 0 && controller_num <= 3){
		 index = controller_num;
	 }
	 else {
		 cout << "CONSTRUCTION_ERROR: Invalid Index." << endl;
		 Sleep(10000);
	 }
	 XInputEnable(true);
	 SetDeadZone(DEFAULT_DEADZONE, DEFAULT_DEADZONE);
 }


 //**************************************
 //	Functions for Battery Information
 //**************************************
 void XboxController::PrintBatteryInform(){
	 XInputGetBatteryInformation(index, BATTERY_DEVTYPE_GAMEPAD, &BatteryInformation);
	 switch (BatteryInformation.BatteryLevel)
	 {
	 case BATTERY_LEVEL_EMPTY: cout << "Battery level empty " << endl;
		 break;
	 case BATTERY_LEVEL_LOW: cout << "Battery level low " << endl;
		 break;
	 case BATTERY_LEVEL_MEDIUM: cout << "Battery level medium " << endl;
		 break;
	 case BATTERY_LEVEL_FULL: cout << "Battery level full" << endl;
	 }
	 Sleep(3000);
 }
 //**************************************
 int XboxController::GetBatteryInform(){
	 XInputGetBatteryInformation(index, BATTERY_DEVTYPE_GAMEPAD, &BatteryInformation);
	 return BatteryInformation.BatteryLevel;
 }


 //******************************
 //	Set gamepad's status
 //******************************
 void XboxController::SetPushButtons(){
	 
	 if (XInputGetState(index, &State) == ERROR_SUCCESS){
		 for (int i = 0; i < BUTTON_SIZE; i++){
			 pushButtons[i] = State.Gamepad.wButtons & buttonMask[i];
		 }
	 }
	 else  {
		 cout << "SetPushButtons_ERROR: Controller_" << index + 1 << " is not connected." << endl;
	 }
 }


 //****************************************************
 //	Get Packet Number, use for check any in input
 //****************************************************
 DWORD XboxController::GetPacketNumber(){
	 return State.dwPacketNumber;
 }


 //*************************************************
 //	Functions for getting status of push buttons
 //*************************************************
 void XboxController::PrintPushButtons(){
	 for (int i = 0; i < BUTTON_SIZE; i++){
		 cout << pushButtons[i] << " ";
	 }
	 cout << endl;
 }

 //*************************************************
 bool XboxController::GetPushButton(int buttonName){
	 return pushButtons[buttonName];
 }
 
 
 //********************************************
 //	Functions for getting position of thumbs
 //********************************************
 COORDINATE XboxController::GetStick(int side){
	 COORDINATE stick;
	 if (side == LEFT_SIDE){
		stick.axisX = State.Gamepad.sThumbLX;
		stick.axisY = State.Gamepad.sThumbLY;
	 }
	 else if (side == RIGHT_SIDE){
		stick.axisX = State.Gamepad.sThumbRX;
		stick.axisY = State.Gamepad.sThumbRY;
	 }
	 else {
		 cout << "GetThumb_ERROR: Invalid Parameter." << endl;
	 }

	 if (stick.axisX >= -deadZone.axisX && stick.axisX <= deadZone.axisX)
		 stick.axisX = 0;
	 if (stick.axisY >= -deadZone.axisY && stick.axisY <= deadZone.axisY)
		 stick.axisY = 0;

	 return stick;
 }

 //****************************************************************
 void  XboxController::SetDeadZone(int x, int y) {
	 if (x >= 0)
		deadZone.axisX = x;
	 else
		deadZone.axisX = -x;

	 if ( y >= 0 )
		deadZone.axisY = y;
	 else
		deadZone.axisY = -y;
 }



 //*************************************
 //	Function for get value of a Trigger
 //*************************************
int XboxController::GetTrigger(int side){

	if (side == LEFT_SIDE){
		return State.Gamepad.bLeftTrigger;
	}
	else if (side == RIGHT_SIDE){
		return State.Gamepad.bRightTrigger;
	}
	else {
		cout << "GetTrigger_ERROR: Invalid parameter." << endl;
		return 0;
	}
}


//******************
//	Set vibrations
//******************
void XboxController::SetVibration(WORD leftMotor, WORD rightMotor){
	if ((leftMotor >= 0 && leftMotor <= MAX_MOTOR_SPEED) && 
		(rightMotor >= 0 && rightMotor <= MAX_MOTOR_SPEED)){
		Vibration.wLeftMotorSpeed = leftMotor;
		Vibration.wRightMotorSpeed = rightMotor;
	}
	else {
		cout << "SetVibration_ERROR: Invalid parameter." << endl;
	}
	
	if (XInputSetState(index, &Vibration) != ERROR_SUCCESS){
		cout << "SetVibration_ERROR: Controller_" << index+1 <<" is not connected." << endl;
	}
	/*
	Vibration.wLeftMotorSpeed = leftMotor;
	Vibration.wRightMotorSpeed = rightMotor;
	XInputSetState(index, &Vibration);
	*/
}


//*********************************************
//	Function to get Gamepad index
//*********************************************
int XboxController::GetIndex(){
	return index;
}





