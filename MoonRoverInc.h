#ifndef	__MOONROVERINC_H
#define	__MOONROVERINC_H


#include "MoonRoverComm.h"
#include "MoonRoverVolt.h"
#include "MoonRoverMotion.h"
#include "MoonRoverMotor.h"
#include "MoonRoverDIS.h"
#include "MoonRoverCam.h"
#include"MoonRoverEnv.h"

//4个电机的角度，角度 
extern int wheelAngel_1, wheelAngel_2, wheelAngel_3, wheelAngel_4; 

//6个电机速度，
extern int wheelSpeed_1, wheelSpeed_2, wheelSpeed_3, wheelSpeed_4, wheelSpeed_5, wheelSpeed_6;

extern int comm3buff[200];

extern volatile  int camFlag;//拍照忙标志


#endif
