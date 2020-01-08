#ifndef	__MOONROVER_H
#define	__MOONROVER_H

#define PT_USE_TIMER
#include "pt.h"

extern volatile  int __camFlag;//拍照忙标志
extern volatile int __autoFlag;
extern unsigned long __timeFlag;
extern unsigned long __timeFlagTele;
extern int __motorFlag;

extern int __changeModeFlag;

void __MoonRoverInit(void);
void __MoonRoverGetConmmunication(void);
void __MoonRoverGetTelecomm(void);
//运动控制
void __MoonRoverRun(int dir,int spd);
void __MoonRoverTurn(int dir,int spd);
void __MoonRoverDricTurn(int dir,int Lspd,int Rspd);
void __MoonRoverLeadTurn(int dir,int ang,int spd);

//遥控指令
void __MoonRoverTakePhoto(void);

//遥测指令
int __MoonRoverGetAngle(int add);
float __MoonRoverGetMotion(int motion);
float __MoonRoverGetTemp(void);
float __MoonRoverGetSpd(void);
float __MoonRoverGetSolarVolt(void);
float __MoonRoverGetBattaryVolt(void);

float __MoonRoverGetDistance(void);


void __MoonRoverGetData(void);
void __MoonRoverOrderData(void);

void __MoonRoverReturnMotorData(void);



void __MoonRoverCreateTask(void);
#endif