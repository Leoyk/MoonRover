#include "MoonRover.h"
#include "Arduino.h"


/*
函数功能：初始化整车
参数：无
返回值：无
影响值：无

作者：刘要坤
时间：2020年1月6日10:18:38

修改记录：

*/
void __MoonRoverInit(void){

  MoonRoverInit();
  Serial.begin(115200);
  Serial.println("MoonRover begin...");

}


/*
函数功能：控制车体整体前进或后退
参数：dir：0 停止; 1 前进，2 后退;  spd： 0~100 速度;
返回值：无
影响值：

作者：刘要坤
时间：2020年1月4日16:36:21

修改记录：

*/
void __MoonRoverRun(int dir,int spd){
//如果方向为2 则后退
	if(dir == 2){//后退
	 spd = -spd;
	}
	else if(dir == 0){//停止
	 spd = 0;
	}

//前进或后退时控制舵机角度均为0
	wheelAngel_1 = 0;
	wheelAngel_2 = 0;
	wheelAngel_3 = 0;
	wheelAngel_4 = 0;
	wheelSpeed_1 = spd;
	wheelSpeed_2 = spd;
	wheelSpeed_3 = spd;
	wheelSpeed_4 = spd;
	wheelSpeed_5 = spd;
	wheelSpeed_6 = spd;

//输出控制指令到协处理器
	cmdMotor();
}



/*
函数功能：控制车体原地转向
参数：dir：0 停止; 1 顺时针，2 逆时针;  spd： 0~100 速度;
返回值：无
影响值：

作者：刘要坤
时间：2020年1月6日10:42:45

修改记录：

*/
void __MoonRoverTurn(int dir,int spd){
//原地转向的角度默认设置为45度
	int ang = 45;


//如果方向为2 则逆时针
	if(dir == 2){//逆时针
	 spd = -spd;
	}
	else if(dir == 0){//停止
	 spd = 0;
	}	

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
//输出控制指令到协处理器
	cmdMotor();
}




/*
函数功能：行进中转向
参数：dir：0 停止; 1 前进，2 后退; Lspd左轮速度,Rspd右轮速度;
返回值：无
影响值：

作者：刘要坤
时间：2020年1月6日13:45:20

修改记录：

*/
void __MoonRoverDricTurn(int dir,int Lspd,int Rspd){



//如果方向为2 则后退
	if(dir == 2){//后退
	 Lspd = -Lspd;
	 Rspd = -Rspd;
	}
	else if(dir == 0){//停止
	 Lspd = 0;
	 Rspd = 0;
	}

//前进或后退时控制舵机角度均为0
	wheelAngel_1 = 0;
	wheelAngel_2 = 0;
	wheelAngel_3 = 0;
	wheelAngel_4 = 0;
	wheelSpeed_1 = Lspd;
	wheelSpeed_2 = Rspd;
	wheelSpeed_3 = Lspd;
	wheelSpeed_4 = Rspd;
	wheelSpeed_5 = Lspd;
	wheelSpeed_6 = Rspd;

//输出控制指令到协处理器
	cmdMotor();
}



/*
函数功能：控制车体导轮转向
参数：dir：0 停止; 1 前进，2 后退;  ang： -45~45 角度;spd 速度
返回值：无
影响值：

作者：刘要坤
时间：2020年1月6日10:42:45

修改记录：

*/
void __MoonRoverLeadTurn(int dir,int ang,int spd){


//如果方向为1 则前轮导向
	if(dir == 1){

	    wheelAngel_1 = ang;
	    wheelAngel_2 = ang;
	    wheelAngel_3 = 0;
	    wheelAngel_4 = 0; 
	}
//如果方向为2 则后轮导向
	else if(dir == 2){
		spd = -spd;	
	    wheelAngel_1 = 0;
	    wheelAngel_2 = 0;
	    wheelAngel_3 = ang;
	    wheelAngel_4 = ang; 
	}
	else if(dir == 0){//停止
		 spd = 0;
	}	

    wheelSpeed_1 = spd;
    wheelSpeed_2 = spd;
    wheelSpeed_3 = spd;
    wheelSpeed_4 = spd;
    wheelSpeed_5 = spd;
    wheelSpeed_6 = spd;   
//输出控制指令到协处理器
	cmdMotor();
}

/*
函数功能：拍照
参数：无
返回值：无
影响值：照片长度、拍照标志

作者：刘要坤
时间：2020年1月6日10:42:45

修改记录：

*/
void __MoonRoverTakePhoto(void){
	takePhoto();
}


/*
函数功能：返回舵机角度
参数：add 0左前，1右前，2左后，3右后
返回值：角度值
影响值：无

作者：刘要坤
时间：2020年1月6日16:34:28

修改记录：

*/
int __MoonRoverGetAngle(int add){

	switch(add){
		case 0: return getLfAngle(); break;
		case 1: return getRfAngle(); break;
		case 2: return getLbAngle(); break;
		case 3: return getRbAngle(); break;

		default: return 0; break;
	}
}
	


/*
函数功能：返回车体姿态
参数：motion 0 yaw，1 pitch，2 roll
返回值：角度值
影响值：无

作者：刘要坤
时间：2020年1月6日16:34:28

修改记录：

*/
float __MoonRoverGetMotion(int motion){

	switch(motion){
		case 0: return getMotion('y'); break;
		case 1: return getMotion('p'); break;
		case 2: return getMotion('r'); break;

		default: return 0; break;
	}
}





/*
函数功能：返回车体核心温度
参数：无
返回值：温度值
影响值：无

作者：刘要坤
时间：2020年1月6日16:34:28

修改记录：

*/
float __MoonRoverGetTemp(void){
	return getTemp();
}




/*
函数功能：返回车体真实运行速度
参数：无
返回值：速度值
影响值：无

作者：刘要坤
时间：2020年1月6日16:34:28

修改记录：

*/
float __MoonRoverGetSpd(void){
	return getSpeed();
}




/*
函数功能：返回车体太阳能电池板电压值
参数：无
返回值：太阳能电池电压值
影响值：无

作者：刘要坤
时间：2020年1月6日16:34:28

修改记录：

*/
float __MoonRoverGetSolarVolt(void){
	return solarVolt();
}




/*
函数功能：返回车体电池电压值
参数：无
返回值：电池电压值
影响值：无

作者：刘要坤
时间：2020年1月6日16:34:28

修改记录：

*/
float __MoonRoverGetBattaryVolt(void){
	return batVolt();
}





/*
函数功能：返回激光测距值
参数：无
返回值：激光测距值 mm
影响值：无

作者：刘要坤
时间：2020年1月6日16:34:28

修改记录：

*/
long __MoonRoverGetDistance(void){
	return getDistant();
}

