#include "Arduino.h"
#include "MoonRoverMotor.h"
#include "MoonRoverComm.h"

extern float spdVal;
extern int angLF,angLB,angRF,angRB;
extern int _Xval,_Yval;

//--------------------系统变量定义区-----------------------
//4个电机的角度，角度 
 int wheelAngel_1, wheelAngel_2, wheelAngel_3, wheelAngel_4; 

//6个电机速度，
 int wheelSpeed_1, wheelSpeed_2, wheelSpeed_3, wheelSpeed_4, wheelSpeed_5, wheelSpeed_6;

 int spd,ang,dirS,dirA;

void ctrCar(void){

float arr = 0.8;//比例


        if(abs(_Yval) < 20){
            spd = 0;
        }
        else{
            spd = (_Yval / abs(_Yval)) * map(abs(_Yval),0,126,0,100);            
        }

      
        if(abs(_Xval) > 80){//原地转向
            ang = 45;
            spd = (_Xval/abs(_Xval)) * map(abs(_Xval),80,126,0,80);
           
            wheelAngel_1 = ang;
            wheelAngel_2 = -ang;
            wheelAngel_3 = -ang;
            wheelAngel_4 = ang; 
        
            wheelSpeed_1 = spd;
            wheelSpeed_2 = -spd;
            wheelSpeed_3 = spd;
            wheelSpeed_4 = -spd;
            wheelSpeed_5 = spd;
            wheelSpeed_6 = -spd;   
      
         }
        else if(abs(_Xval) > 10){
            ang = (_Xval/abs(_Xval)) * map(abs(_Xval),10,80,0,45);


            if(_Yval > 20){
            wheelAngel_1 = ang;
            wheelAngel_2 = ang;
            wheelAngel_3 = 0;
            wheelAngel_4 = 0; 

                if(ang > 0){//右转
                    wheelSpeed_1 = spd;
                    wheelSpeed_2 = spd * arr;
                    wheelSpeed_3 = spd;
                    wheelSpeed_4 = spd * arr;
                    wheelSpeed_5 = spd;
                    wheelSpeed_6 = spd * arr;
                }
                else{//左转
                    wheelSpeed_1 = spd * arr;
                    wheelSpeed_2 = spd;
                    wheelSpeed_3 = spd * arr;
                    wheelSpeed_4 = spd;
                    wheelSpeed_5 = spd * arr;
                    wheelSpeed_6 = spd;
                }
            }
        else if(_Yval < -20){
            wheelAngel_1 = 0;
            wheelAngel_2 = 0;
            wheelAngel_3 = ang;
            wheelAngel_4 = ang; 

                if(ang < 0){//左转
                    wheelSpeed_1 = spd;
                    wheelSpeed_2 = spd * arr;
                    wheelSpeed_3 = spd;
                    wheelSpeed_4 = spd * arr;
                    wheelSpeed_5 = spd;
                    wheelSpeed_6 = spd * arr;
                }
                else{//右转
                    wheelSpeed_1 = spd * arr;
                    wheelSpeed_2 = spd;
                    wheelSpeed_3 = spd * arr;
                    wheelSpeed_4 = spd;
                    wheelSpeed_5 = spd * arr;
                    wheelSpeed_6 = spd;
                }
            }
            
          }else{
            ang = 0; 
 //           spd = 0;
            wheelAngel_1 = ang;
            wheelAngel_2 = ang;
            wheelAngel_3 = ang;
            wheelAngel_4 = ang;   
            
            wheelSpeed_1 = spd;
            wheelSpeed_2 = spd;
            wheelSpeed_3 = spd;
            wheelSpeed_4 = spd;
            wheelSpeed_5 = spd;
            wheelSpeed_6 = spd;  
          } 
}


/*
 * 程序功能：发出电机遥控指令到协处理器
 * 参数：无
 * 返回值：无
*/
void cmdMotor(void){
//帧头 主-协
//帧头
  Serial3.write(0xFC);
  //帧类型
    Serial3.write(CTR_MOTOR_TYPE);
   //数据 
    //车轮1角度
    writeHEX(wheelAngel_1,3);
    //车轮2角度
    writeHEX(wheelAngel_2,3);
    //车轮3角度
    writeHEX(wheelAngel_3,3);
    //车轮4角度
    writeHEX(wheelAngel_4,3);
    
    //车轮1速度
    writeHEX(wheelSpeed_1,3);
    //车轮2速度
    writeHEX(wheelSpeed_2,3);
    //车轮3速度
    writeHEX(wheelSpeed_3,3);
    //车轮4速度
    writeHEX(wheelSpeed_4,3);
    //车轮5速度
    writeHEX(wheelSpeed_5,3);
    //车轮6速度
    writeHEX(wheelSpeed_6,3);
    
//校验和
  Serial3.write(checkSum(CTR_MOTOR_TYPE + (wheelAngel_1 & 0xFF) +  (wheelAngel_1 >> 8) + (wheelAngel_2 & 0xFF) +  (wheelAngel_2 >> 8) + (wheelAngel_3 & 0xFF) +  (wheelAngel_3 >> 8) + (wheelAngel_4 & 0xFF) +  (wheelAngel_4 >> 8)
   + (wheelSpeed_1 & 0xFF) +  (wheelSpeed_1 >> 8) + (wheelSpeed_2 & 0xFF) +  (wheelSpeed_2 >> 8) + (wheelSpeed_3 & 0xFF) +  (wheelSpeed_3 >> 8) + (wheelSpeed_4 & 0xFF) +  (wheelSpeed_4 >> 8) + (wheelSpeed_5 & 0xFF) +  (wheelSpeed_5 >> 8) + (wheelSpeed_6 & 0xFF) +  (wheelSpeed_6 >> 8)));

//帧尾
  Serial3.write(0xCF);
  }


/*
 * 程序功能：发出电机遥测数据
 * 参数：无
 * 返回值：无
 * 备注：测试中使用串口0
*/
static void printMotorDataHex(void){
  Serial2.write(0xFB);
  //帧类型
    Serial2.write(MOTOR_TYPE);    
  //数据 
    //车轮1角度
    writeHEX(angLF,2);
    //车轮2角度
    writeHEX(angRF,2);
    //车轮3角度
    writeHEX(angLB,2);
    //车轮4角度
    writeHEX(angRB,2);
    
    //车轮1速度
    writeHEX(wheelSpeed_1,2);
    //车轮2速度
    writeHEX(wheelSpeed_2,2);
    //车轮3速度
    writeHEX(wheelSpeed_3,2);
    //车轮4速度
    writeHEX(wheelSpeed_4,2);
    //车轮5速度
    writeHEX(wheelSpeed_5,2);
    //车轮6速度
    writeHEX(wheelSpeed_6,2);
    
//校验和
  Serial2.write(checkSum(MOTOR_TYPE + (wheelAngel_1 & 0xFF) +  (wheelAngel_1 >> 8) + (wheelAngel_2 & 0xFF) +  (wheelAngel_2 >> 8) + (wheelAngel_3 & 0xFF) +  (wheelAngel_3 >> 8) + (wheelAngel_4 & 0xFF) +  (wheelAngel_4 >> 8)
   + (wheelSpeed_1 & 0xFF) +  (wheelSpeed_1 >> 8) + (wheelSpeed_2 & 0xFF) +  (wheelSpeed_2 >> 8) + (wheelSpeed_3 & 0xFF) +  (wheelSpeed_3 >> 8) + (wheelSpeed_4 & 0xFF) +  (wheelSpeed_4 >> 8) + (wheelSpeed_5 & 0xFF) +  (wheelSpeed_5 >> 8) + (wheelSpeed_6 & 0xFF) +  (wheelSpeed_6 >> 8)));

//帧尾
  Serial2.write(0xBF);
  
  sendSpd();
  }



void sendSpd(void){
	int buf[6] = {0xFB,0X61,0,0,0,0XBF};
	buf[2] = (int)(spdVal * 100) & 0xff;
	buf[3] = (int)(spdVal * 100) >> 8;
	buf[4] = (buf[1] + buf[2] +buf[3]) & 0xFF;

  for(int i = 0; i < 6;i ++){
	Serial2.write(buf[i]);
  }
}




float getSpeed(void){
	return spdVal;
}

int getLfAngle(){
	return angLF;
}
int getLbAngle(){
	return angLB;
}
int getRfAngle(){
	return angRF;
}
int getRbAngle(){
	return angRB;
}









