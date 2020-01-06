#ifndef	__MOONROVER_H
#define	__MOONROVER_H


#include "MoonRoverInc.h"

//运动控制
void __MoonRoverInit(void);
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

long __MoonRoverGetDistance(void);




#endif