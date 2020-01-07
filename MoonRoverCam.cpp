#include"MoonRoverCam.h"
#include "Arduino.h"
#include "MoonRoverComm.h"

extern int comm3buff[200];
extern int takePicOkFlag;
extern int camFlag;
extern long camLen;
extern int camDataCnt;
/*

协议：


测距：
		FB  10  dis  dis  ck BF   6
拍照：
		FB  30  sta  length  length ck BF   7
图像数据：
		FB  31	address	 address	128数据	ck BF  134
*/	
/*

返回帧数

*/
int takePhoto(void){
	long buf;
	const int takePic[5] = {0xfa,0x03,0x00,0x03,0xaf};
	camFlag = 1;

	Serial.print("take photo...\n");

	for(int i = 0;i < 5;i ++){
		Serial3.write(takePic[i]);
	}



	// while(takePicOkFlag == 0){//未拍照成功则持续发送
	// 	for(int i = 0;i < 5;i ++){
	// 		Serial3.write(takePic[i]);
	// 	}
	// delay(2000);//等待拍照完成
	// 	getTeleComm3();
	// 	getData();

	// Serial.print("Retry...\n");
	// }

	// buf = camLen/128;
	
	// if(buf * 128 < camLen){
	// 	buf ++;
	// }

	return (int)buf;

}

int orderPicData(int num){
	int takePic[5] = {0xfa,0x04,0x01,0x05,0xaf};
	takePic[2] = num;
	takePic[3] = checkSum(takePic[1] + takePic[2]);
	for(int i = 0;i < 5;i ++){
		Serial3.write(takePic[i]);
	}
	getTeleComm3();
	getData();
	return camDataCnt;
}
