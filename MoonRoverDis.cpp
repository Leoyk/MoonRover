#include"MoonRoverDis.h"
#include "Arduino.h"
#include "MoonRoverComm.h"

extern long disVal;

long getDistant(void){
	  return disVal;
}