#include"MoonRoverCam.h"
#include "Arduino.h"
#include "MoonRoverComm.h"

extern int comm3buff[200];
/*

协议：


测距：
		FB  10  dis  dis  ck BF   6
拍照：
		FB  30  sta  length  length ck BF   7
图像数据：
		FB  31	address	 address	128数据	ck BF  134
*/	

void takePhoto(void){
	int takePic[5] = {0xfa,0x03,0x0,0x03,0xaf};
	
		for(int i = 0;i < 5;i ++){
			Serial3.write(takePic[i]);
		}
}
