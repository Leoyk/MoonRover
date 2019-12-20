#ifndef	__MOONROVERCOMM_H
#define	__MOONROVERCOMM_H

//---------------------宏定义区---------------------------

//参见月球车-PC协议   
  //姿测遥测-1
  #define MOTION_TYPE (0x10) 
  //电源管理遥测-1
  #define POWER_TYPE (0x00)
  //环境遥测-1
  #define ENV_TYPE (0x20)
  //彩色摄像遥测-1
  #define CAM_TYPE_1 (0x30)
  //彩色摄像遥测-2
  #define CAM_TYPE_2 (0x31)
  //激光测距遥测-1
  #define DIS_TYPE (0x50)
  //电机运行状态遥测-1
  #define MOTOR_TYPE (0x60)



//参见月球主-协协议 

  //控制拍照
  #define CTR_CAM_TYPE_1 (0x03)
  //控制磁场校准
  #define CTR_MAG_TYPE_1 (0x04)
  //整车运动遥控
  #define CTR_MOTOR_TYPE (0x60)







//-------------------函数声明区----------------------------


void MoonRoverInit(void);//备注：暂无模拟读取，调试中使用串口0发数据
int checkSum(int sum);
void writeHEX(int num,int com);

void getTeleComm2(void);
void getTeleComm3(void);

void orderData(void);
u8 getData(void);

#endif