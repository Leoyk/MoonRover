#include "Arduino.h"
#include "MoonRoverComm.h"
#include "MoonRoverVolt.h"
#include "MoonRoverMotor.h"

int comm3buff[200];
int comm2buff[200];



int takePicOkFlag = 0;
volatile int camFlag = 0;
long camLen = 0;
int camDataCnt = 0;
int _Xval,_Yval;

float tempVal;
long disVal;
float spdVal;
int angLF,angLB,angRF,angRB;
float _yaw,_pit,_rol;

void MoonRoverInit(void){
  Serial2.begin(115200);
  Serial3.begin(115200);
}


void clearBuf(int a){
  if(a == 2){
    for(int i = 0;i < 200; i ++)
      comm2buff[i] = 0; 
  }
  if(a == 3){
    for(int i = 0;i < 200; i ++)
      comm3buff[i] = 0; 
  }
}


void getTeleComm2(void){  
  int buf;
  long ck;
  int rx2cnt = 0;


  while(Serial2.available()){
    buf = Serial2.read();
    Serial3.write(buf);

    if(camFlag != 1){
      Serial.print(buf,HEX);/////////不知道为什么不加运行不对
      Serial.print("\t");  
    }

    
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
            Serial.print(_Xval);
            Serial.print("\t");
            Serial.println(_Yval);   
////////////////////////////////////////////////////////////手动模式下开启下列功能          
            ctrCar();
            cmdMotor(); 
////////////////////////////////////////////////////////////
          }
          else if(comm2buff[1] == 0x03){//photo ctr
            camFlag = 1;
            Serial.println("Take photo...");
            }
        }
      else{    
        Serial.println("ck wrong...");
        for(int j = 0; j < rx2cnt + 1; j ++){
         Serial.print(comm2buff[j],HEX);
         Serial.print("|\t");
        }
      }
      }else{
        comm2buff[rx2cnt] = buf;
        }
    rx2cnt ++;
  }
}


void getTeleComm3(void){  
  int buf,rx3cnt = 0;
  static int flag = 0;
//  clearBuf(3);
  
  while(Serial3.available()){
    buf = Serial3.read();
    Serial2.write(buf); 
    if(camFlag != 1){
      Serial.print(buf,HEX);/////////不知道为什么不加运行不对
      Serial.print("\t");  
    }
    


    comm3buff[rx3cnt] = buf;
    rx3cnt ++;

    if(camFlag){
      if(buf == 0xfb){
        flag = 1;
      }
      else if((flag == 1) && (buf == 0xFF)){
        flag = 2;
      }
      else if((flag == 2) && (buf == 0xBF)){
        flag = 0;
        camFlag = 0;
      }
      else{
        flag = 0;
      }
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



int getData(void){

  long ck;
 
  if((comm3buff[0] == 0xFB) && (comm3buff[1] == 0xFF)){
    
    ck = 0; 
    for(int i = 1;i < 22;i ++){
      ck += comm3buff[i];
    }

    ck &= 0xff;
    if(ck == comm3buff[22]){
      spdVal = ((comm3buff[3] << 8) + comm3buff[2]) * 0.0175924;
      tempVal = (float)((comm3buff[5] << 8) + comm3buff[4])/10;
      disVal = (comm3buff[7] << 8) + comm3buff[6];
	  
      _yaw = ((comm3buff[9] << 8) + comm3buff[8]) / 10.0;
      _pit = ((comm3buff[11] << 8) + comm3buff[10]) / 10.0;
      _rol = ((comm3buff[13] << 8) + comm3buff[12]) / 10.0;
	  
	  
	  
      angLF = (comm3buff[15] << 8) + comm3buff[14];
      angLB = (comm3buff[17] << 8) + comm3buff[16];
      angRF = (comm3buff[19] << 8) + comm3buff[18];
      angRB = (comm3buff[21] << 8) + comm3buff[20];
    clearBuf(3);  
    return 1; 
    }
  }
  
  else if((comm3buff[0] == 0xFB) && (comm3buff[1] == 0x30)){
    ck = 0; 
    for(int ick = 1;ick < 7;ick ++){
      ck += comm3buff[ick];
    }

    ck &= 0xff;
    if(ck == comm3buff[7]){
      if(comm3buff[2] == 0x02){
        takePicOkFlag = 1;  
        
      Serial.print(comm3buff[3],HEX);
      Serial.print("\t");
      Serial.print(comm3buff[4],HEX);
      Serial.println("\t");
      
      camLen = ((comm3buff[4] << 8) + comm3buff[3]);
      
      //clearBuf(2);
      return 2;   
      }
    }
    else{
      takePicOkFlag = 0;
      for(int idata = 0;idata < 12;idata ++){
        Serial.print(comm3buff[idata],HEX);
        Serial.print("\t");
      }
      Serial.print("\n");
      }
    
  }
    return 0; 
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