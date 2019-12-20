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

void MoonRoverInit(void){

  Serial2.begin(115200);
  Serial3.begin(115200);
	
}

void getTeleComm2(void){  
  int buf,_Xval,_Yval;
  long ck;
  int rx2cnt = 0;


  while(Serial2.available()){
    buf = Serial2.read();
    Serial.print(buf,HEX);/////////不知道为什么不加运行不对
    Serial.print("\t");

    
    if(buf == 0xFA){//接收到帧头 
      rx2cnt = 0;  
      comm2buff[rx2cnt] = buf;
      }
      
    else if(buf == 0xAF){//接收到帧尾
      comm2buff[rx2cnt] = buf;
      
      ck = 0;
      for(int j = 1; j < rx2cnt - 1; j ++){
       ck += comm2buff[j];
      }
      ck &= 0xFF;

      if(ck == comm2buff[rx2cnt - 1]){
        
          if(comm2buff[1] == 0x02){//motor ctr
            _Xval = (int)((char)comm2buff[2]);
            _Yval = (int)((char)comm2buff[3]);
//            Serial.print(_Xval);
//            Serial.print("\t");
//            Serial.println(_Yval);
          }
          else if(comm2buff[1] == 0x03){//photo ctr
            camFlag = 1;
            Serial.println("Take photo...");
            }
        }
      else{    
        Serial.println("ck wrong...");
        Serial.println("data:");
        for(int j = 0; j < rx2cnt + 1; j ++){
         Serial.print(comm2buff[j],HEX);
         Serial.print("\t");
        }
      }
      }else{
        comm2buff[rx2cnt] = buf;
        }
    rx2cnt ++;
  }
}

void getTeleComm3(void){  
  int buf;
  
  while(Serial3.available()){
    buf = Serial3.read();
    Serial2.write(buf);
  }
}




u8 getData(void){
	return 0;
	
}

/*	
	// long ck;
	// const u8 buf[5] = {0xFA,0X03,0X00,0X03,0XAF};
	
 	// if((comm2buff[0] == 0xFA) && (comm2buff[1] == 0x03) && (comm2buff[2] == 0x00) && (comm2buff[3] == 0x03) && (comm2buff[4] == 0xAF)){
			// camFlag = 1;
			
			// for(int i = 0;i < 5;i ++){
				// Serial3.write(buf[i]);	
			// }
			// clearBuff(2);
	// }else{
		// camFlag = 0;//不是拍照指令则清除标志位
		
	// }

	// if((comm3buff[0] == 0xFB) && (comm3buff[1] == 0xFF)){
		
		// if(comm3buff[2] == 0xBF){
			// camFlag = 0;//拍照结束
		// }
		
		// ck = 0;	
		// for(int i = 1;i < 22;i ++){
			// ck += comm3buff[i];
		// }

		// ck &= 0xff;
		// if(ck == comm3buff[22]){
			// spdVal = ((comm3buff[3] << 8) + comm3buff[2]) * 0.0175924;
			// tempVal = (float)((comm3buff[5] << 8) + comm3buff[4])/10;
			// disVal = (comm3buff[7] << 8) + comm3buff[6];
			
			// angLF = (comm3buff[15] << 8) + comm3buff[14];
			// angLB = (comm3buff[17] << 8) + comm3buff[16];
			// angRF = (comm3buff[19] << 8) + comm3buff[18];
			// angRB = (comm3buff[21] << 8) + comm3buff[20];
		// return 1; 
		// }else{

		// }
	// }
		// return 0; 
// }

*/



u8 takePhoto(void){
	int orderData[5] = {0xfa,0x03,0x0,0x03,0xaf};
	
		for(int i = 0;i < 5;i ++){
			Serial3.write(orderData[i]);
		}
	return 0;
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