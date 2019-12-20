#include"MoonRoverVolt.h"
#include "Arduino.h"


float solarVolt(void){
	return 60*analogRead(A6)/2048.0;
}

float batVolt(void){
	return 60*analogRead(A7)/2048.0;
}

void getVolt(void){
	int buf[6] = {0xFB,0X00,0,0,0,0XBF};
	buf[2] = (int)(solarVolt() * 10);
	buf[3] = (int)(batVolt() * 10);
	buf[4] = (buf[1] + buf[2] +buf[3]) & 0xFF;

  for(int i = 0; i < 6;i ++){
	Serial2.write(buf[i]);
  }
}