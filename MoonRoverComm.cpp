#include "Arduino.h"
#include "MoonRoverComm.h"
#include "MoonRoverVolt.h"


int comm3buff[200];
int comm2buff[200];

volatile int camFlag = 0;
float tempVal;
long disVal;
float spdVal;
int angLF,angLB,angRF,angRB;



void clearBuff(int a){
	
	for(int i = 0; i < 200;i ++){
		if(a == 2)
		comm2buff[i] = 0;
		else if(a == 3)
		comm3buff[i] = 0;
	}
	
}








/*
 * 程序功能：初始化通信及模拟读取接口
 * 参数：无
 * 返回值:无
 * 备注：暂无模拟读取
*/
void MoonRoverInit(void){
  //init serial port 2，3;
    Serial2.begin(115200);
    Serial3.begin(115200);
  }







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
 * 程序功能：保存下位遥测回传数据
 * 参数：无
 * 返回值:获取到数据的类型   4 距离   6拍照状态  132照片数据
 * 影响：comm3buff[];
*/
void getTeleComm(void){	

	int i = 0;
	int buf,buf3;

	i = 0;
	while(Serial3.available()){
		
		buf3 = Serial3.read();
		Serial2.write(buf3);
//		Serial.write(buf3);	
		
		comm3buff[i] = buf3;
		i ++;	
	}

	i = 0;
	while(Serial2.available()){
		buf = Serial2.read();
		comm2buff[i] = buf;

		Serial3.write(buf);	
		i ++;
	}
}

u8 getData(void){	
	long ck;
	const u8 buf[5] = {0xFA,0X03,0X00,0X03,0XAF};
	
 	if((comm2buff[0] == 0xFA) && (comm2buff[1] == 0x03) && (comm2buff[2] == 0x00) && (comm2buff[3] == 0x03) && (comm2buff[4] == 0xAF)){
			camFlag = 1;
			
/* 			for(int i = 0;i < 5;i ++){
				Serial3.write(buf[i]);	
			} */
			delay(200);
			clearBuff(2);
	}

	if((comm3buff[0] == 0xFB) && (comm3buff[1] == 0xFF)){
		
		if(comm3buff[2] == 0xBF){
			camFlag = 0;//拍照结束
		}
		
		ck = 0;	
		for(int i = 1;i < 22;i ++){
			ck += comm3buff[i];
		}

		ck &= 0xff;
		if(ck == comm3buff[22]){
			spdVal = ((comm3buff[3] << 8) + comm3buff[2]) * 0.0175924;
			tempVal = (float)((comm3buff[5] << 8) + comm3buff[4])/10;
			disVal = (comm3buff[7] << 8) + comm3buff[6];
			
			angLF = (comm3buff[15] << 8) + comm3buff[14];
			angLB = (comm3buff[17] << 8) + comm3buff[16];
			angRF = (comm3buff[19] << 8) + comm3buff[18];
			angRB = (comm3buff[21] << 8) + comm3buff[20];
		return 1; 
		}else{

		}
	}
		return 0; 
}





u8 getCamData(void){
	static u8 capFlag = 1;
	if(camFlag){
		if(capFlag){
			

		}
	}
	
}



void orderData(void){
	int orderData[5] = {0xfa,0x01,0x2,0x03,0xaf};
	getVolt();
		for(int i = 0;i < 5;i ++){
			Serial3.write(orderData[i]);
		}
}





/*
 * 程序功能：取数据低八位
 * 参数：数据
 * 返回值:数据低八位
*/
int checkSum(int sum){
  return (sum & 0xFF);
  }

/*
 * 函数功能：小端模式输出
 * 参数：int数据
 * 返回值：无
*/
void writeHEX(int num,int com){
  
    if(com == 2){
      //输出低八位
      Serial2.write((num & 0xFF));
      //输出高八位
      Serial2.write((num >> 8));
    }  
    else if(com == 3){
      //输出低八位
      Serial3.write((num & 0xFF));
      //输出高八位
      Serial3.write((num >> 8));
    }
  }