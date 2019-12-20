#ifndef	__MOONROVERMOTOR_H
#define	__MOONROVERMOTOR_H


void cmdMotor(void);
void printMotorDataHex(void);//备注：测试中使用串口0
float getSpeed(void);
int getLfAngle();
int getLbAngle();
int getRfAngle();
int getRbAngle();

#endif