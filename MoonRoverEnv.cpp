#include"MoonRoverEnv.h"
#include "Arduino.h"
#include "MoonRoverComm.h"

extern float tempVal;

float getTemp(void){
	  return tempVal;
}
