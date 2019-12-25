#include "MoonRoverMotion.h"
#include "MoonRoverComm.h"
#include "Arduino.h"

extern float _yaw,_pit,_rol;

float getMotion(char a){
	if((a == 'y') || (a == 'Y'))
	  return _yaw;
	else if((a == 'p') || (a == 'P'))
	  return _pit;
	else if((a == 'r') || (a == 'R'))
	  return _rol;
}